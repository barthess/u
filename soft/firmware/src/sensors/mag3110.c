#include <stdlib.h>
#include <math.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define mag3110addr 0b0001110
#define mag3110sens 0.1F /* uT/LSB */
#define OVERDOSE    ((uint16_t)25000) // предел, после которого надо ресетить датчик
#define ERR_VAL     -32700  /* это значение является символом ошибки чтения */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern RawData raw_data;
extern CompensatedData comp_data;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// буфера под данные магнитометра
static uint8_t rxbuf[MAG_RX_DEPTH];
static uint8_t txbuf[MAG_TX_DEPTH];

/* указатели в структуре с параметрами */
static float          *xsens,   *ysens,   *zsens;
static int32_t        *xoffset, *yoffset, *zoffset;
static int32_t const  *xpol,    *ypol,    *zpol;
static uint32_t const *swapmtrx;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */
//static void raise_error_flags(void);
static void check_and_clean_overdose(void);
static void process_magentometer_data(uint8_t *rxbuf);

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Поток для опроса магнитометра
 */
static WORKING_AREA(PollMagThreadWA, 256);
static msg_t PollMagThread(void *semp){
  chRegSetThreadName("PollMag");

  msg_t sem_status = RDY_OK;
  int32_t retry = 10;
  Thread *cal_tp = NULL;

  while (TRUE) {
    /* Первый раз этот семафор скорее всего сбросится по таймауту, поскольку
     * прерываение прилетит на лапку раньше, чем подхватится EXTI.
     * Кроме того, для того,
     * чтобы прерывание работало, надо обязательно читать данные
     * из как минимум первого регистра. */
    sem_status = chBSemWaitTimeout((BinarySemaphore*)semp, MS2ST(200));
    if (sem_status != RDY_OK){
      retry--;
      chDbgAssert(retry > 0, "PollMagThread(), #1",
          "probably no interrupts from magnetometer");
    }

    txbuf[0] = MAG_OUT_DATA;
    i2c_transmit(mag3110addr, txbuf, 1, rxbuf, 6);
    process_magentometer_data(rxbuf);
    setGlobalFlag(GlobalFlags.mag_data_ready);

    /* decide to fork or collect terminated calibration thread */
    if (GlobalFlags.mag_cal){
      if (cal_tp == NULL)
        cal_tp = MagCalStart();
      mag_stat_update();
    }
    else{ /* thread collected all needed data and termintaed itself */
      if (cal_tp != NULL && cal_tp->p_state == THD_STATE_FINAL){
        chThdWait(cal_tp);
        cal_tp = NULL;
      }
    }

    /* overdose? */
    check_and_clean_overdose();
  }
  return 0;
}

/**
 * Раскладывает полученные данные по структурам, при необходимости масштабирует.
 */
static void process_magentometer_data(uint8_t *rxbuf){

  /**/
  raw_data.xmag = complement2signed(rxbuf[0], rxbuf[1]);
  raw_data.ymag = complement2signed(rxbuf[2], rxbuf[3]);
  raw_data.zmag = complement2signed(rxbuf[4], rxbuf[5]);

  /* fill debug structs */
  mavlink_raw_imu_struct.xmag = raw_data.xmag;
  mavlink_raw_imu_struct.ymag = raw_data.ymag;
  mavlink_raw_imu_struct.zmag = raw_data.zmag;

  mavlink_scaled_imu_struct.xmag = (raw_data.xmag - *xoffset) * *xpol * roundf(*xsens * 100.0f);
  mavlink_scaled_imu_struct.ymag = (raw_data.ymag - *yoffset) * *ypol * roundf(*ysens * 100.0f);
  mavlink_scaled_imu_struct.zmag = (raw_data.zmag - *zoffset) * *zpol * roundf(*zsens * 100.0f);

  /* Sensitivity is 0.1uT/LSB */
  comp_data.xmag = (float)(mavlink_scaled_imu_struct.xmag);
  comp_data.ymag = (float)(mavlink_scaled_imu_struct.ymag);
  comp_data.zmag = (float)(mavlink_scaled_imu_struct.zmag);
}

/**
 * если датчик передознулся - надо произвести сброс. В принципе, можно
 * в датчике настроить авторесет на каждое измерение, но
 * это как-то не элегантно.
 */
static void check_and_clean_overdose(void){
  if (abs(raw_data.xmag) > OVERDOSE ||
      abs(raw_data.ymag) > OVERDOSE ||
      abs(raw_data.zmag) > OVERDOSE){
    txbuf[0] = MAG_CTRL_REG2;
    txbuf[1] = MAG_RST;
    i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0);
  }
}

/**
 *
 */
static void __search_indexes(void){
  xoffset   = ValueSearch("MAG_xoffset");
  yoffset   = ValueSearch("MAG_yoffset");
  zoffset   = ValueSearch("MAG_zoffset");
  xpol      = ValueSearch("MAG_xpol");
  ypol      = ValueSearch("MAG_ypol");
  zpol      = ValueSearch("MAG_zpol");
  xsens     = ValueSearch("MAG_xsens");
  ysens     = ValueSearch("MAG_ysens");
  zsens     = ValueSearch("MAG_zsens");
  swapmtrx  = ValueSearch("MAG_sortmtrx");
}

/**
 *
 */
static void __hard_init_short(void){
}

/**
 *
 */
static void __hard_init_full(void){

  // TODO: self diagnostic

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint32_t i = 0;
    for (i = 0; i < MAG_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < MAG_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  txbuf[0] = MAG_WHOAMI;
  i2c_transmit(mag3110addr, txbuf, 1, rxbuf, 2);
  chDbgCheck(rxbuf[0] == MAG_WHOAMI_VAL, "Wrong whoami respose");

  /* Except for STANDBY mode selection, the device must be in STANDBY mode
   to change any of the fields within CTRL_REG1 (0x10). */
  txbuf[0] = MAG_CTRL_REG1; // register address
  /* выводим из спящего режима, настраиваем чувствительность */
  //txbuf[1] = 0b11001;    // 10 Hz, 8 samples
  txbuf[1] = 0b1001;       // 40 Hz, 2 samples
  i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(2);

  /* произведём сервисный сброс датчика */
  txbuf[0] = MAG_CTRL_REG2;
  txbuf[1] = MAG_RST;
  i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
void init_mag3110(BinarySemaphore *mag3110_semp){

  __search_indexes();

  if (need_full_init())
    __hard_init_full();
  else
    __hard_init_short();

  chThdCreateStatic(PollMagThreadWA,
          sizeof(PollMagThreadWA),
          I2C_THREADS_PRIO,
          PollMagThread,
          mag3110_semp);
}


