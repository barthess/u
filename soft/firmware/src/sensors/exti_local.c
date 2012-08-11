#include <stdlib.h>

#include "ch.h"
#include "hal.h"
#include "sensors.h"
#include "exti_local.h"
#include "rtc.h"
#include "message.h"
#include "timekeeping.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 * To avloid dividing in ISR we set precalculated period of check.
 * F=N/T
 * set T to 1 second
 * Hz=N for single pulse on revolution
 * to acquare frequency in Hz for 2 blades prop. we must set timeout twise shorter:
 * 500mS instead 1S.
 */
//#define TACHO_CHECK_T (1000 / 2)  /* 2 blades in fixed wing */
#define TACHO_CHECK_T 333           /* 3 blades in ground rover */

/* строка для (пере)запуска тахометрового таймера*/
#define starttacho_vt() {chVTSetI(&tachocheck_vt, MS2ST(TACHO_CHECK_T), &vt_tachocheck_cb, NULL);}

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern uint32_t imu_update_period;
extern BinarySemaphore rtc_sem;
//extern mavlink_system_t mavlink_system_struct;
extern mavlink_vfr_hud_t mavlink_vfr_hud_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

BinarySemaphore *rtc_semp     = &rtc_sem;
BinarySemaphore *mag3110_semp = NULL;
BinarySemaphore *mma8451_semp = NULL;
BinarySemaphore *bmp085_semp  = NULL;
BinarySemaphore *itg3200_semp = NULL;

/**
 * Global turn counter for engine.
 * Incrementes on every exti pulse.
 * Zeroes in virtual timer callback.
 */
//static uint32_t pulsecnt = 0;
static uint32_t tacho_period = 0;

/* timer for RPM counting */
static VirtualTimer tachocheck_vt;

/* флаг, означающий надо ли измерять частоту получения сэмплов */
static int32_t itg3200_period_measured = -100; /* -100 означает, что надо пропустить 100 первых сэмплов */

/* для измерения периода получения сэмплов с гироскопа */
static TimeMeasurement itg3200_tmup;
static TimeMeasurement tacho_tmup;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/*
 * see comments for TACHO_CHECK_T define
 */
static void vt_tachocheck_cb(void *par){
  (void)par;
//  chSysLockFromIsr();
//  starttacho_vt();
//  raw_data.engine_rpm = pulsecnt;
//  mavlink_vfr_hud_struct.groundspeed = pulsecnt;
//  pulsecnt = 0;
//  chSysUnlockFromIsr();
}

/**
 * Сброс флага прерывания и обработка
 */
static void rtcalarm_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
//  if (RTCD1.id_rtc->ISR | RTC_ISR_ALRBF){
//    RTCD1.id_rtc->ISR &= ~RTC_ISR_ALRBF;
//  }
//  if (RTCD1.id_rtc->ISR | RTC_ISR_ALRAF){
//    RTCD1.id_rtc->ISR &= ~RTC_ISR_ALRAF;
//  }
}

/**
 * Сброс флага прерывания и обработка
 */
static void rtcwakeup_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
//  if (RTCD1.id_rtc->ISR | RTC_ISR_WUTF){
//    RTCD1.id_rtc->ISR &= ~RTC_ISR_WUTF;
//  }
}

static void tachometer_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;

  tmStopMeasurement(&tacho_tmup);
  tacho_period = RTT2US(tacho_tmup.last);
  mavlink_vfr_hud_struct.groundspeed = tacho_period;
  tmStartMeasurement(&tacho_tmup);

//  pulsecnt++;
//  raw_data.odometer++;
}

static void microsd_inset_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
}

static void gps_pps_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
  chSysLockFromIsr();
  chBSemSignalI(rtc_semp);
  chSysUnlockFromIsr();
}

static void bmp085_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
  chSysLockFromIsr();
  chBSemSignalI(bmp085_semp);
  chSysUnlockFromIsr();
}

static void mag3110_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
  chSysLockFromIsr();
  chBSemSignalI(mag3110_semp);
  chSysUnlockFromIsr();
}

static void mma8451_int1_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
//  chSysLockFromIsr();
//  chBSemSignalI(&mma8451_sem);
//  chSysUnlockFromIsr();
}

static void itg3200_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
  chSysLockFromIsr();

  if (itg3200_period_measured < 2){
    if (itg3200_period_measured == 0){
      tmStartMeasurement(&itg3200_tmup);
    }
    else if(itg3200_period_measured == 1){
      tmStopMeasurement(&itg3200_tmup);
      imu_update_period = RTT2US(itg3200_tmup.last);
    }
    itg3200_period_measured++;
  }

  chBSemSignalI(itg3200_semp);
  chSysUnlockFromIsr();
}

static void mma8451_int2_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
  chSysLockFromIsr();
  chBSemSignalI(mma8451_semp);
  chSysUnlockFromIsr();
}

static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_RISING_EDGE | EXT_MODE_GPIOE, gps_pps_cb},// секундная метка с GPS
    {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, tachometer_cb},// оптрон тахометра
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, microsd_inset_cb}, // микросдшка
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},//5
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, bmp085_cb}, // датчик давления
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, mag3110_cb}, // magnetometer
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, mma8451_int1_cb}, // первое прерывание с акселерометра
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, itg3200_cb}, // хероскоп
    {EXT_CH_MODE_DISABLED, NULL},//11
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, mma8451_int2_cb},//15
    {EXT_CH_MODE_DISABLED, NULL},//PVD
    {EXT_CH_MODE_RISING_EDGE, rtcalarm_cb},// RTC alarms
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},// timestamp
    {EXT_CH_MODE_RISING_EDGE, rtcwakeup_cb},// wakeup
  }
};



/*
EXT_MODE_GPIOE,// GPS_PPS
0,
0,
EXT_MODE_GPIOE,// microSD detect
0,
0,//5
EXT_MODE_GPIOE,// давленометр
EXT_MODE_GPIOE,// магнитометр
EXT_MODE_GPIOE,// accelerometer int1
0,
EXT_MODE_GPIOE,// gyro
0,
EXT_MODE_GPIOE,//оптрон
0,
0,//14
EXT_MODE_GPIOE)// accelerometer int2
*/


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

void ExtiInitLocal(BinarySemaphore *mag3110_sem,
                   BinarySemaphore *mma8451_sem,
                   BinarySemaphore *bmp085_sem,
                   BinarySemaphore *itg3200_sem){

  mag3110_semp = mag3110_sem;
  mma8451_semp = mma8451_sem;
  bmp085_semp  = bmp085_sem;
  itg3200_semp = itg3200_sem;

  raw_data.odometer = 0;
  chSysLock();
  starttacho_vt();
  chSysUnlock();

  tmObjectInit(&itg3200_tmup);
  tmObjectInit(&tacho_tmup);

  extStart(&EXTD1, &extcfg);
}

/**
 * Enables interrupts from PPS
 */
void ExtiEnablePps(void){
  extChannelEnable(&EXTD1, 0);
}





