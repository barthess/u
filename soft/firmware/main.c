/*                      WARNINGS!
 *
 * ��� ���������� ��� -fomit-frame-pointer ������� ���� .
 */

// TODO: �������� ���������� ���������� ��� ���������� ��������� I2C (������ HALT)
// TODO: ��������� ������� ���������� � BKP
// TODO: ���������� ���������� �� �������� ������� (�������� ���������, �������� ����� PwrHypervisor)
// TODO: ������� ������� �� ���� ������ ��������� (gyro_failed, gps_failed, etc.)

// TODO: ����� ��� ���� ����� ��� ������� �������� �� 60 �������� ������� � ������� ��������� ������� ����������������
// TODO: ������ � ��� ������ �� LinkOutThread ����� � 2 ���� ����, ��� �������� ����������
// TODO: ���������� �������� ����� �� DMA
// TODO: ��������� ������ ������ �� ���������� ���������� �� RTC
// TODO: ������������� ����������� ����� � �����������, ���������� � GPS.
// TODO: ���������� ������ � �������������� ������ � ���������� �������� ��� ������������� ��������

// Hardware
// TODO: ���� �� �������� ������������ ��� ������������ ���������
// TODO: ����� ��������� ������� �� ���� �� ��������

#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "main.h"
#include "param.h"
#include "sanity.h"
#include "irq_storm.h"
#include "i2c_pns.h"
#include "adc_pns.h"
#include "timekeeping.h"
#include "linkmgr.h"
#include "gps.h"
#include "servo.h"
#include "message.h"
#include "autopilot.h"
#include "eeprom.h"
#include "eeprom_testsuit.h"
#include "exti_pns.h"
#include "storage.h"
#include "cli.h"
#include "imu.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
uint64_t TimeUsec;                    /* Timestamp (microseconds since UNIX epoch) */

uint32_t GlobalFlags = 0;             /* ����� �� ��� ������ ���������� ����� */

RawData raw_data;                     /* ��������� � ������ ������� � �������� */
CompensatedData comp_data;            /* ������������ ������ */

uint32_t itg3200_period = 0;          /* ����� ��������� ������� � ��������� (uS)*/
uint32_t imu_step = 0;                /* incremented on each call to imu_update */
float dcmEst[3][3] = {{1,0,0},{0,1,0},{0,0,1}};   /* estimated DCM matrix */

BinarySemaphore imu_sem;              /* ������� ��� ������������� ���������� � �������� */
BinarySemaphore mag3110_sem;          /* ������������� ������ � ����������� �� ������� */
BinarySemaphore mma8451_sem;          /* ������������� ������ � ����������� �� ������� */
BinarySemaphore bmp085_sem;           /* ������������� ������ � ����������� �� ������� */
BinarySemaphore itg3200_sem;          /* ������������� ������ � ����������� �� ������� */

/* ���������������� ���� EEPROM */
EepromFileStream EepromFile;

Mailbox autopilot_mb;                 /* ��������� ��� ���������� */
static msg_t autopilot_mb_buf[4];
Mailbox tolink_mb;                    /* ��������� ��� �������� ����� ����� */
static msg_t tolink_mb_buf[8];
Mailbox toservo_mb;                   /* ��������� ��� ������������� ���� */
static msg_t toservo_mb_buf[1];
Mailbox param_mb;                     /* ��������� � ����������� */
static msg_t param_mb_buf[2];
Mailbox mavlinkcmd_mb;                /* ��������� � ��������� */
static msg_t mavlinkcmd_mb_buf[1];
Mailbox logwriter_mb;                 /* ��������� ��� ������� ����� */
static msg_t logwriter_mb_buf[4];

/* ����������, ���������� �������� */
mavlink_system_t            mavlink_system;
mavlink_raw_pressure_t      mavlink_raw_pressure_struct;
mavlink_raw_imu_t           mavlink_raw_imu_struct;
mavlink_scaled_imu_t        mavlink_scaled_imu_struct;
mavlink_sys_status_t        mavlink_sys_status_struct;
mavlink_command_long_t      mavlink_command_long_struct;

/* heap for (link threads) OR (shell thread)*/
MemoryHeap LinkThdHeap;
static uint8_t link_thd_buf[LINK_THD_HEAP_SIZE];

/* �������� ������� ��������� � ����������� �������� */
EventSource pwrmgmt_event;

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


int main(void) {
  halInit();
  chSysInit();
  chEvtInit(&pwrmgmt_event);

  chThdSleepMilliseconds(1);

  /* ������� �������� ����������� */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();

  // ��������� ��������������� ����
  comp_data.xgyro_angle = 0;
  comp_data.ygyro_angle = 0;
  comp_data.zgyro_angle = 0;

  /* ���������� ������������� */
  chBSemInit(&imu_sem,      TRUE);
  chBSemInit(&mag3110_sem,  TRUE);
  chBSemInit(&mma8451_sem,  TRUE);
  chBSemInit(&bmp085_sem,   TRUE);
  chBSemInit(&itg3200_sem,  TRUE);

  /* ������������� �������� ������ */
  chMBInit(&autopilot_mb,     autopilot_mb_buf,       (sizeof(autopilot_mb_buf)/sizeof(msg_t)));
  chMBInit(&tolink_mb,        tolink_mb_buf,          (sizeof(tolink_mb_buf)/sizeof(msg_t)));
  chMBInit(&toservo_mb,       toservo_mb_buf,         (sizeof(toservo_mb_buf)/sizeof(msg_t)));
  chMBInit(&param_mb,         param_mb_buf,           (sizeof(param_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlinkcmd_mb,    mavlinkcmd_mb_buf,      (sizeof(mavlinkcmd_mb_buf)/sizeof(msg_t)));
  chMBInit(&logwriter_mb,     logwriter_mb_buf,       (sizeof(logwriter_mb_buf)/sizeof(msg_t)));

  /* ������������� ���� ��� ������ ����� */
  chHeapInit(&LinkThdHeap, link_thd_buf, LINK_THD_HEAP_SIZE);

  /* �������������� ��������� �������� */
  mavlink_system.sysid  = 20;                   ///< ID 20 for this airplane
  mavlink_system.compid = MAV_COMP_ID_ALL;     ///< The component sending the message, it could be also a Linux process
  mavlink_system.type   = MAV_TYPE_GROUND_ROVER;
  mavlink_system.state  = MAV_STATE_UNINIT;
  mavlink_system.mode   = MAV_MODE_PREFLIGHT;

  EepromOpen(&EepromFile);

  LinkMgrInit();
  SanityControlInit();
  ExtiInit(); /* I2C � RTC ���������� ��� */
  TimekeepingInit();
  I2CInit_pns();
//  eeprom_testsuit_run();
  ParametersInit(); /* ������ ��������� �� EEPROM, ������� ������ ���� ����� I2C*/
  ServoInit();
  ADCInit_pns();
  ImuInit();
  GPSInit();
//  AutopilotInit();  /* ��������� ������ ���������� ������ ����� ��������� ����� */
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

