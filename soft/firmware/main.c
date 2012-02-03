/*                      WARNINGS!
 *
 * ��� ���������� ��� -fomit-frame-pointer ������� ���� .
 */

// TODO: ������������� ����������� ����� � �����������, ���������� � GPS.
// TODO: ���������� ������ � �������������� ������ � ���������� �������� ��� ������������� ��������


#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "main.h"
#include "parameters.h"
#include "sanity.h"
#include "irq_storm.h"
#include "i2c_pns.h"
#include "adc_pns.h"
#include "timekeeping.h"
#include "link.h"
#include "gps.h"
#include "servo.h"
#include "message.h"
#include "autopilot.h"
#include "eeprom_file.h"
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
LogItem log_item;                     /* ���������, ���������� ������ ��� ���� */

BinarySemaphore imu_sem;              /* ������� ��� ������������� ���������� � ��� */
BinarySemaphore mag3110_sem;
BinarySemaphore mma8451_sem;
BinarySemaphore bmp085_sem;
BinarySemaphore itg3200_sem;

/* ��������� �� ���������������� ���� EEPROM */
EepromFileStream* EepromFile_p = NULL;

Mailbox autopilot_mb;                 /* ��������� ��� ���������� */
static msg_t autopilot_mb_buf[4];
Mailbox tolink_mb;                    /* ��������� ��� �������� ����� ����� */
static msg_t tolink_mb_buf[8];
Mailbox toservo_mb;                   /* ��������� ��� ������������� ���� */
static msg_t toservo_mb_buf[1];
Mailbox param_mb;                     /* ��������� � ����������� */
static msg_t param_mb_buf[3];
Mailbox manual_control_mb;
static msg_t manual_control_mb_buf[1];

/* ����������, ���������� �������� */
mavlink_system_t            mavlink_system;
mavlink_raw_pressure_t      mavlink_raw_pressure_struct;
mavlink_raw_imu_t           mavlink_raw_imu_struct;
mavlink_scaled_imu_t        mavlink_scaled_imu_struct;
mavlink_sys_status_t        mavlink_sys_status_struct;
mavlink_command_long_t      mavlink_command_long_struct;

mavlink_bart_manual_control_t mavlink_bart_manual_control_struct;

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

  // ��������� ��������������� ����
  raw_data.gyro_xI = 0;
  raw_data.gyro_yI = 0;
  raw_data.gyro_zI = 0;

  /* ���������� ������������� */
  chBSemInit(&imu_sem,      TRUE);
  chBSemInit(&mag3110_sem,  TRUE);
  chBSemInit(&mma8451_sem,  TRUE);
  chBSemInit(&bmp085_sem,   TRUE);
  chBSemInit(&itg3200_sem,  TRUE);

  /* �������� ����� */
  chMBInit(&autopilot_mb,     autopilot_mb_buf,       (sizeof(autopilot_mb_buf)/sizeof(msg_t)));
  chMBInit(&tolink_mb,        tolink_mb_buf,          (sizeof(tolink_mb_buf)/sizeof(msg_t)));
  chMBInit(&toservo_mb,       toservo_mb_buf,         (sizeof(toservo_mb_buf)/sizeof(msg_t)));
  chMBInit(&param_mb,         param_mb_buf,           (sizeof(param_mb_buf)/sizeof(msg_t)));
  chMBInit(&manual_control_mb,manual_control_mb_buf,  (sizeof(manual_control_mb_buf)/sizeof(msg_t)));

  /* �������������� ��������� �������� */
  mavlink_system.sysid  = 20;                   ///< ID 20 for this airplane
  mavlink_system.compid = MAV_COMP_ID_ALL;     ///< The component sending the message, it could be also a Linux process
  mavlink_system.type   = MAV_TYPE_GROUND_ROVER;
  mavlink_system.state  = MAV_STATE_UNINIT;
  mavlink_system.mode   = MAV_MODE_PREFLIGHT;

  /* ������� �������� ����������� */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();
  chThdSleepMilliseconds(50);

  LinkInit();
  SanityControlInit();
  ExtiInit(); /* I2C � RTC ���������� ��� */
  TimekeepingInit();
  I2CInit_pns();
  ParametersInit(); /* ������ ��������� �� EEPROM, ������� ������ ���� ����� I2C*/
  ServoInit();
//  CliInit();
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
  }

  return 0;
}

