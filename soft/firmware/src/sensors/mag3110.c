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
#define OVERDOSE    ((uint16_t)25000) // предел, после которого надо ресетить датчик

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern BinarySemaphore mag3110_sem;
//extern GlobalParam_t global_data[];
extern mavlink_raw_imu_t mavlink_raw_imu_struct;

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

  while (TRUE) {
    /* Первый раз этот семафор скорее всего сбросится по таймауту, поскольку
     * прерываение прилетит на лапку раньше, чем подхватится EXTI. Для того,
     * чтобы прерывание нормально работало, надо обязательно читать данные
     * из как минимум первого регистра. */
    sem_status = chBSemWaitTimeout(&mag3110_sem, MS2ST(200));

    /* посмотрим, чё там померялось */
    txbuf[0] = MAG_OUT_DATA;
    if (i2c_transmit(mag3110addr, txbuf, 1, rxbuf, 6) == RDY_OK &&
                                           sem_status == RDY_OK){
      mavlink_raw_imu_struct.xmag = complement2signed(rxbuf[0], rxbuf[1]);
      mavlink_raw_imu_struct.ymag = complement2signed(rxbuf[2], rxbuf[3]);
      mavlink_raw_imu_struct.zmag = complement2signed(rxbuf[4], rxbuf[5]);
    }
    else{
      /* выставляем знамение ошибки */
      mavlink_raw_imu_struct.xmag = -32768;
      mavlink_raw_imu_struct.ymag = -32768;
      mavlink_raw_imu_struct.zmag = -32768;
    }

    /* если датчик передознулся - надо произвести сброс. В принципе,
    можно в датчике настроить авторесет на каждое измерение, но это
    как-то не элегантно. */
    if (abs(mavlink_raw_imu_struct.xmag) > OVERDOSE ||
        abs(mavlink_raw_imu_struct.ymag) > OVERDOSE ||
        abs(mavlink_raw_imu_struct.zmag) > OVERDOSE){
      txbuf[0] = MAG_CTRL_REG2;
      txbuf[1] = MAG_RST;
      i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0);
    }
  }

  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void init_mag3110(void){
  int32_t i = -1;

  i = key_value_search("MAG_xoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    xoffset_index = i;

  i = key_value_search("MAG_yoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    yoffset_index = i;

  i = key_value_search("MAG_zoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    zoffset_index = i;

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
}


