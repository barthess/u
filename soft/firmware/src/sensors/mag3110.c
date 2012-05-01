#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "utils.h"
#include "mag3110.h"
#include "message.h"
#include "param.h"
#include "main.h"
#include "link.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define mag3110addr 0b0001110
#define mag3110sens 0.1F /* uT/LSB */
#define OVERDOSE    ((uint16_t)25000) // предел, после которого надо ресетить датчик

#define XOFFSET     (global_data[xoffset_index].value)
#define YOFFSET     (global_data[yoffset_index].value)
#define ZOFFSET     (global_data[zoffset_index].value)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern BinarySemaphore mag3110_sem;
extern GlobalParam_t global_data[];
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern RawData raw_data;
extern EventSource pwrmgmt_event;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// буфера под данные магнитометра
static uint8_t rxbuf[MAG_RX_DEPTH];
static uint8_t txbuf[MAG_TX_DEPTH];

/* индексы в структуре с параметрами */
static uint32_t xoffset_index, yoffset_index, zoffset_index;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/* Поток для запроса акселерометра */
static WORKING_AREA(PollMagThreadWA, 512);
static msg_t PollMagThread(void *arg){
  chRegSetThreadName("PollMag");
  (void)arg;
  msg_t sem_status = RDY_OK;

  struct EventListener self_el;
  chEvtRegister(&pwrmgmt_event, &self_el, PWRMGMT_SIGHALT_EVID);

  while (TRUE) {
    /* Первый раз этот семафор скорее всего сбросится по таймауту, поскольку
     * прерываение прилетит на лапку раньше, чем подхватится EXTI. Для того,
     * чтобы прерывание нормально работало, надо обязательно читать данные
     * из как минимум первого регистра. */
    sem_status = chBSemWaitTimeout(&mag3110_sem, MS2ST(200));

    /* посмотрим, чё там померялось */
    txbuf[0] = MAG_OUT_DATA;
    if ((i2c_transmit(mag3110addr, txbuf, 1, rxbuf, 6) == RDY_OK) && (sem_status == RDY_OK)){
      raw_data.xmag = complement2signed(rxbuf[0], rxbuf[1]);
      raw_data.ymag = complement2signed(rxbuf[2], rxbuf[3]);
      raw_data.zmag = complement2signed(rxbuf[4], rxbuf[5]);

      /* fill raw */
      mavlink_raw_imu_struct.xmag = raw_data.xmag;
      mavlink_raw_imu_struct.ymag = raw_data.ymag;
      mavlink_raw_imu_struct.zmag = raw_data.zmag;

      /* fill scaled. Sensitivity is 0.1uT/LSB = 10^-1 */
//      mavlink_scaled_imu_struct.xmag = (raw_data.xmag - XOFFSET) / 10;
//      mavlink_scaled_imu_struct.ymag = (raw_data.ymag - YOFFSET) / 10;
//      mavlink_scaled_imu_struct.zmag = (raw_data.zmag - ZOFFSET) / 10;
      mavlink_scaled_imu_struct.xmag = (raw_data.xmag - XOFFSET);
      mavlink_scaled_imu_struct.ymag = (raw_data.ymag - YOFFSET);
      mavlink_scaled_imu_struct.zmag = (raw_data.zmag - ZOFFSET);
    }
    else{
      /* выставляем знамение ошибки */
      raw_data.xmag = -32768;
      raw_data.ymag = -32768;
      raw_data.zmag = -32768;
      mavlink_raw_imu_struct.xmag = raw_data.xmag;
      mavlink_raw_imu_struct.ymag = raw_data.ymag;
      mavlink_raw_imu_struct.zmag = raw_data.zmag;
      mavlink_scaled_imu_struct.xmag = raw_data.xmag;
      mavlink_scaled_imu_struct.ymag = raw_data.ymag;
      mavlink_scaled_imu_struct.zmag = raw_data.zmag;
    }

    /* если датчик передознулся - надо произвести сброс. В принципе,
          можно в датчике настроить авторесет на каждое измерение, но это
          как-то не элегантно. */
    if (abs(raw_data.xmag) > OVERDOSE ||
        abs(raw_data.ymag) > OVERDOSE ||
        abs(raw_data.zmag) > OVERDOSE){
      txbuf[0] = MAG_CTRL_REG2;
      txbuf[1] = MAG_RST;
      i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0);
    }

    if (chThdSelf()->p_epending & EVENT_MASK(PWRMGMT_SIGHALT_EVID))
      chThdExit(RDY_OK);
  }

  return 0;
}

/**
 * Поиск индексов в массиве настроек
 */
void search_indexes(void){
  int32_t i = -1;

  i = KeyValueSearch("MAG_xoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    xoffset_index = i;

  i = KeyValueSearch("MAG_yoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    yoffset_index = i;

  i = KeyValueSearch("MAG_zoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    zoffset_index = i;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void init_mag3110(void){
  int32_t i = -1;

  search_indexes();

  // TODO: сначала вообще убедиться, что девайс отвечает путем запроса его WHOAMI
  // TODO: запустить в нем самодиагностику

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    i = 0;
    for (i = 0; i < MAG_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < MAG_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  /* Except for STANDBY mode selection, the device must be in STANDBY mode
   to change any of the fields within CTRL_REG1 (0x10). */
  txbuf[0] = MAG_CTRL_REG1; // register address
  txbuf[1] = 0b11001;       // выводим из спящего режима, настраиваем чувствительность
  while(i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  /* произведём сервисный сброс датчика */
  chThdSleepMilliseconds(2);
  txbuf[0] = MAG_CTRL_REG2;
  txbuf[1] = MAG_RST;
  while(i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  chThdCreateStatic(PollMagThreadWA,
          sizeof(PollMagThreadWA),
          I2C_THREADS_PRIO,
          PollMagThread,
          NULL);
  chThdSleepMilliseconds(1);
}


