#include <stdlib.h>

#include "ch.h"
#include "hal.h"
#include "message.h"
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
extern LogItem log_item;

extern BinarySemaphore mag3110_sem;
extern BinarySemaphore mma8451_sem;
extern BinarySemaphore bmp085_sem;
extern BinarySemaphore itg3200_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
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

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

void vt_tachocheck_cb(void *par){
  (void)par;
  chVTSetI(&tachocheck_vt, MS2ST(TACHO_CHECK_T), &vt_tachocheck_cb, NULL);
  /* ���� ������ ����� ������ 0.5 ������ � 2-���������� �����, �� ���������� ��� ��� ����� */
  //log_item.engine_rpm = (rpmcnt * 1000) / (TACHO_CHECK_T * TACHO_BLADES);
  log_item.engine_rpm = rpmcnt;
  rpmcnt = 0;

  raw_data.engine_rpm = log_item.engine_rpm;
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
  chBSemSignalI(&bmp085_sem);
  chSysUnlockFromIsr();
}

static void mag3110_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
  chSysLockFromIsr();
  chBSemSignalI(&mag3110_sem);
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
  chBSemSignalI(&itg3200_sem);
  chSysUnlockFromIsr();
}

static void mma8451_int2_cb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;
  chSysLockFromIsr();
  chBSemSignalI(&mma8451_sem);
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




inline void ExtiInit(void){
  chSysLock();
  chVTSetI(&tachocheck_vt, MS2ST(TACHO_CHECK_T), &vt_tachocheck_cb, NULL);
  chSysUnlock();

  extStart(&EXTD1, &extcfg);
}







