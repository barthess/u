#include <stdlib.h>

#include "ch.h"
#include "hal.h"
#include "sensors.h"
#include "exti_pns.h"
#include "rtc.h"


/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/**
 * ������������� �������� ��������.
 */
#define TACHO_CHECK_T 500
/**
 * ���������� ������� � ������� ��������
 */
#define TACHO_BLADES  2

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern uint32_t imu_update_period;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

BinarySemaphore *mag3110_semp = NULL;
BinarySemaphore *mma8451_semp = NULL;
BinarySemaphore *bmp085_semp = NULL;
BinarySemaphore *itg3200_semp = NULL;

/**
 * ���������� ������� ��������.
 * ���������������� �� �������� ����������.
 * ������������ �� ������������ �������.
 */
static uint32_t rpmcnt = 0;

/**
 * ������ ��� ���������� �������� RPM
 */
static VirtualTimer tachocheck_vt;

/* ����, ���������� ���� �� �������� ������� ��������� ������� */
static int32_t itg3200_period_measured = -100; /* -100 ��������, ��� ���� ���������� 100 ������ ������� */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

void vt_tachocheck_cb(void *par){
  (void)par;
  chSysLockFromIsr();
  chVTSetI(&tachocheck_vt, MS2ST(TACHO_CHECK_T), &vt_tachocheck_cb, NULL);
  /* ���� ������ ����� ������ 0.5 ������ � 2-���������� �����, �� ���������� ��� ��� ����� */
  //log_item.engine_rpm = (rpmcnt * 1000) / (TACHO_CHECK_T * TACHO_BLADES);
  raw_data.engine_rpm = rpmcnt;
  rpmcnt = 0;
  chSysUnlockFromIsr();
}

/**
 * ����� ����� ���������� � ���������
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
 * ����� ����� ���������� � ���������
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
  rpmcnt++;
}

static void microsd_inset_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
}

static void gps_pps_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
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

static TimeMeasurement itg3200_tmup;

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
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, gps_pps_cb},// ��������� ����� � GPS
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART, microsd_inset_cb}, // ����������
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},//5
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, bmp085_cb}, // ������ ��������
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, mag3110_cb}, // magnetometer
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, mma8451_int1_cb}, // ������ ���������� � �������������
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, itg3200_cb}, // ��������
    {EXT_CH_MODE_DISABLED, NULL},//11
    {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART, tachometer_cb}, // ������ ���������
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, mma8451_int2_cb},//15
    {EXT_CH_MODE_DISABLED, NULL},//PVD
    {EXT_CH_MODE_RISING_EDGE, rtcalarm_cb},// RTC alarms
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},// timestamp
    {EXT_CH_MODE_RISING_EDGE, rtcwakeup_cb},// wakeup
  },
  EXT_MODE_EXTI(
      EXT_MODE_GPIOE,// GPS_PPS
      0,
      0,
      EXT_MODE_GPIOE,// microSD detect
      0,
      0,//5
      EXT_MODE_GPIOE,// �����������
      EXT_MODE_GPIOE,// �����������
      EXT_MODE_GPIOE,// accelerometer int1
      0,
      EXT_MODE_GPIOE,// gyro
      0,
      EXT_MODE_GPIOE,//������
      0,
      0,//14
      EXT_MODE_GPIOE)// accelerometer int2
};


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

void ExtiInit(BinarySemaphore *mag3110_sem,
              BinarySemaphore *mma8451_sem,
              BinarySemaphore *bmp085_sem,
              BinarySemaphore *itg3200_sem){

  mag3110_semp = mag3110_sem;
  mma8451_semp = mma8451_sem;
  bmp085_semp = bmp085_sem;
  itg3200_semp = itg3200_sem;

  chSysLock();
  chVTSetI(&tachocheck_vt, MS2ST(TACHO_CHECK_T), &vt_tachocheck_cb, NULL);
  chSysUnlock();

  tmObjectInit(&itg3200_tmup);

  extStart(&EXTD1, &extcfg);
}







