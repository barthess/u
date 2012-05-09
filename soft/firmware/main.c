/*                      WARNINGS!
 *
 * ��� ���������� ��� -fomit-frame-pointer ������� ���� .
 */

// TODO: �������� ���� ������������ � ������
// TODO: ������ ������� GPS
// TODO: ���������� ����� ���� ������ � �������-��������� ���������
// TODO: ��������� �������� I2C �������, ����������� ������ ��� ��������
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


#include "ch.h"
#include "hal.h"

#include "main.h"
#include "param.h"
#include "sanity.h"
#include "irq_storm.h"
#include "i2c_pns.h"
#include "timekeeping.h"
#include "linkmgr.h"
#include "gps.h"
#include "servo.h"
#include "message.h"
#include "sensors.h"
#include "autopilot.h"
#include "eeprom.h"
#include "exti_pns.h"
#include "storage.h"


/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
uint64_t TimeUsec;                    /* Timestamp (microseconds since UNIX epoch) */
uint32_t GlobalFlags = 0;             /* ����� �� ��� ������ ���������� ����� */

/* ���������������� ���� EEPROM */
EepromFileStream EepromFile;

Mailbox autopilot_mb;                 /* ��������� ��� ���������� */
static msg_t autopilot_mb_buf[4];
Mailbox tolink_mb;                    /* ��������� ��� �������� ����� ����� */
static msg_t tolink_mb_buf[10];
Mailbox toservo_mb;                   /* ��������� ��� ������������� ���� */
static msg_t toservo_mb_buf[1];
Mailbox mavlink_param_set_mb;                     /* ��������� � ����������� */
static msg_t param_mb_buf[2];
Mailbox mavlink_command_long_mb;                /* ��������� � ��������� */
static msg_t mavlinkcmd_mb_buf[2];
Mailbox logwriter_mb;                 /* ��������� ��� ������� ����� */
static msg_t logwriter_mb_buf[4];

/* ����������, ���������� �������� */
mavlink_system_t            mavlink_system_struct;
mavlink_raw_pressure_t      mavlink_raw_pressure_struct;
mavlink_raw_imu_t           mavlink_raw_imu_struct;
mavlink_scaled_imu_t        mavlink_scaled_imu_struct;
mavlink_sys_status_t        mavlink_sys_status_struct;
mavlink_command_long_t      mavlink_command_long_struct;
mavlink_vfr_hud_t           mavlink_vfr_hud_struct; /* ��������� � �������� �������� */
mavlink_set_mode_t          mavlink_set_mode_struct;

/* heap for (link threads) OR (shell thread)*/
MemoryHeap LinkThdHeap;
static uint8_t link_thd_buf[LINK_THD_HEAP_SIZE + sizeof(stkalign_t)];

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

  /* ������������� �������� ������ */
  chMBInit(&autopilot_mb,     autopilot_mb_buf,       (sizeof(autopilot_mb_buf)/sizeof(msg_t)));
  chMBInit(&tolink_mb,        tolink_mb_buf,          (sizeof(tolink_mb_buf)/sizeof(msg_t)));
  chMBInit(&toservo_mb,       toservo_mb_buf,         (sizeof(toservo_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlink_param_set_mb,         param_mb_buf,           (sizeof(param_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlink_command_long_mb,    mavlinkcmd_mb_buf,      (sizeof(mavlinkcmd_mb_buf)/sizeof(msg_t)));
  chMBInit(&logwriter_mb,     logwriter_mb_buf,       (sizeof(logwriter_mb_buf)/sizeof(msg_t)));

  /* ������������� ���� ��� ������ ����� */
  chHeapInit(&LinkThdHeap, (uint8_t *)MEM_ALIGN_NEXT(link_thd_buf), LINK_THD_HEAP_SIZE);

  /* �������������� ��������� �������� */
  mavlink_system_struct.sysid  = 20;                   ///< ID 20 for this airplane
  mavlink_system_struct.compid = MAV_COMP_ID_ALL;     ///< The component sending the message, it could be also a Linux process
  mavlink_system_struct.type   = MAV_TYPE_FIXED_WING;
  mavlink_system_struct.state  = MAV_STATE_BOOT;
  mavlink_system_struct.mode   = MAV_MODE_PREFLIGHT;

  EepromOpen(&EepromFile);

  LinkMgrInit();
  SanityControlInit();
  TimekeepingInit();

  I2CInit_pns(); /* also starts EEPROM and load global parameters from it */
  SensorsInit(); /* uses I2C */

  ServoInit();

  GPSInit();
  AutopilotInit();  /* ��������� ������ ���������� ������ ����� ��������� ����� */
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

