/*                      WARNINGS!
 *
 * ��� ���������� ��� -fomit-frame-pointer ������� ���� .
 */

// TODO: ���������������� ������������ �� � ������� � ����� DCM
// TODO: �������� ���� ������������ � ������
// TODO: ���������� ����� ���� ������ � �������-��������� ���������
// TODO: ���������� ���������� �� �������� ������� (�������� ���������, �������� ����� PwrHypervisor)
// TODO: ������� ������� �� ���� ������ ��������� (gyro_failed, gps_failed, etc.)

// TODO: ����� ��� ���� ����� ��� ������� �������� �� 60 �������� ������� � ������� ��������� ������� ����������������
// TODO: ������ � ��� ������ �� LinkOutThread ����� � 2 ���� ����, ��� �������� ����������
// TODO: ���������� �������� ����� �� DMA
// TODO: ���������� ������ � �������������� ������ � ���������� �������� ��� ������������� ��������

#include "ch.h"
#include "hal.h"

#include "main.h"
#include "param.h"
#include "sanity.h"
#include "irq_storm.h"
#include "i2c_local.h"
#include "timekeeping.h"
#include "linkmgr.h"
#include "gps.h"
#include "servo.h"
#include "message.h"
#include "sensors.h"
#include "autopilot.h"
#include "eeprom.h"
#include "exti_local.h"
#include "microsd.h"

#include "arm_math.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
BinarySemaphore rtc_sem;  /* ��� ������������� ����� �� PPS */
struct tm gps_timp;       /* ��������� ��� �������� �������, ����������� �� GPS */

uint32_t GlobalFlags = 0;             /* ����� �� ��� ������ ���������� ����� */

/* ���������������� ���� EEPROM */
EepromFileStream EepromFile;

/* heap for (link threads) OR (shell thread)*/
MemoryHeap LinkThdHeap;
static uint8_t link_thd_buf[LINK_THD_HEAP_SIZE + sizeof(stkalign_t)];

/* �������� ������� ��������� � ����������� �������� */
EventSource pwrmgmt_event;
EventSource modem_event;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
//static TimeMeasurement tmup;
//static volatile float x = 0;
//static volatile uint32_t y = 0;
//static volatile uint32_t n = 1000000;
//static volatile uint32_t imu_update_period = 0;

int main(void) {
  halInit();
  chSysInit();

//  tmObjectInit(&tmup);
//  tmStartMeasurement(&tmup);
//  x = arm_cos_f32(PI/3.0);
//  tmStopMeasurement(&tmup);
//  imu_update_period = tmup.last;
//
//  imu_update_period = 0;
//  tmStartMeasurement(&tmup);
//  for (;n >0; n--)
//    y = arm_cos_q31(n);
//  tmStopMeasurement(&tmup);
//  imu_update_period = tmup.last;

  chBSemInit(&rtc_sem, TRUE);

  chEvtInit(&pwrmgmt_event);
  chEvtInit(&modem_event);

  chThdSleepMilliseconds(100);

  /* ������� �������� ����������� */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();

  /* ������������� ���� ��� ������ ����� */
  chHeapInit(&LinkThdHeap, (uint8_t *)MEM_ALIGN_NEXT(link_thd_buf), LINK_THD_HEAP_SIZE);

  EepromOpen(&EepromFile);

  LinkMgrInit();
  MsgInit();
  SanityControlInit();
  TimekeepingInit();
  I2CInitLocal(); /* also starts EEPROM and load global parameters from it */

  /** ������������� ����������� ��������, � �.�. ����� ����� ��������� � �������
   * ������ ���� ����� I2C, �.�. ������ ������ ��������� */
  MavInit();
  SensorsInit(); /* uses I2C */
  ServoInit();
  AutopilotInit();  /* ��������� ������ ���������� ������ ����� ������� ���� */
  StorageInit();

  #if ENABLE_IRQ_STORM
    chThdSleepMilliseconds(5000);
    IRQStormInit();
  #endif /* ENABLE_IRQ_STORM */

  while (TRUE){
    chThdSleepMilliseconds(666);
    //chEvtBroadcastFlags(&pwrmgmt_event, EVENT_MASK(PWRMGMT_SIGHALT_EVID));
  }

  return 0;
}

