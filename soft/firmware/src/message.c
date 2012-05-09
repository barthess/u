#include "ch.h"
#include "hal.h"

#include "message.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/* ������ �������� ����� */
Mailbox autopilot_mb;             /* ��������� ��� ���������� */
Mailbox tolink_mb;                /* ��������� ��� �������� ����� ����� */
Mailbox toservo_mb;               /* ��������� ��� ������������� ���� */
Mailbox mavlink_param_set_mb;     /* ��������� � ����������� */
Mailbox mavlink_command_long_mb;  /* ��������� � ��������� */
Mailbox logwriter_mb;             /* ��������� ��� ������� ����� */

/* ����������, ���������� �������� */
mavlink_system_t            mavlink_system_struct;
mavlink_raw_pressure_t      mavlink_raw_pressure_struct;
mavlink_raw_imu_t           mavlink_raw_imu_struct;
mavlink_scaled_imu_t        mavlink_scaled_imu_struct;
mavlink_sys_status_t        mavlink_sys_status_struct;
mavlink_command_long_t      mavlink_command_long_struct;
mavlink_vfr_hud_t           mavlink_vfr_hud_struct; /* ��������� � �������� �������� */
mavlink_set_mode_t          mavlink_set_mode_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* ������ ��� �������� ������ */
static msg_t autopilot_mb_buf[4];
static msg_t tolink_mb_buf[10];
static msg_t toservo_mb_buf[1];
static msg_t param_mb_buf[2];
static msg_t mavlinkcmd_mb_buf[2];
static msg_t logwriter_mb_buf[4];

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

void MsgInit(void){
  /* ������������� �������� ������ */
  chMBInit(&autopilot_mb,             autopilot_mb_buf,       (sizeof(autopilot_mb_buf)/sizeof(msg_t)));
  chMBInit(&tolink_mb,                tolink_mb_buf,          (sizeof(tolink_mb_buf)/sizeof(msg_t)));
  chMBInit(&toservo_mb,               toservo_mb_buf,         (sizeof(toservo_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlink_param_set_mb,     param_mb_buf,           (sizeof(param_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlink_command_long_mb,  mavlinkcmd_mb_buf,      (sizeof(mavlinkcmd_mb_buf)/sizeof(msg_t)));
  chMBInit(&logwriter_mb,             logwriter_mb_buf,       (sizeof(logwriter_mb_buf)/sizeof(msg_t)));

  /* �������������� ��������� �������� */
  mavlink_system_struct.sysid  = 20;                   ///< ID 20 for this airplane
  mavlink_system_struct.compid = MAV_COMP_ID_ALL;     ///< The component sending the message, it could be also a Linux process
  mavlink_system_struct.type   = MAV_TYPE_FIXED_WING;
  mavlink_system_struct.state  = MAV_STATE_BOOT;
  mavlink_system_struct.mode   = MAV_MODE_PREFLIGHT;
}



