#include "uav.h"

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
Mailbox tolink_mb;                /* for messages to the ground station */
Mailbox mavlink_param_set_mb;
Mailbox mavlink_command_long_mb;
Mailbox controller_mb;
Mailbox logwriter_mb;
Mailbox speedometer_mb;           /* measured time intervals from spedometer */
Mailbox mission_mb;               /* messages for mission planner */

/* variable for storing system state */
mavlink_system_t                mavlink_system_struct;

/* mavlink messages */
mavlink_status_t                mavlink_status_struct;
mavlink_raw_imu_t               mavlink_raw_imu_struct;
mavlink_scaled_imu_t            mavlink_scaled_imu_struct;
mavlink_raw_pressure_t          mavlink_raw_pressure_struct;
mavlink_scaled_pressure_t       mavlink_scaled_pressure_struct;
mavlink_sys_status_t            mavlink_sys_status_struct;
mavlink_vfr_hud_t               mavlink_vfr_hud_struct;
mavlink_global_position_int_t   mavlink_global_position_int_struct;
mavlink_attitude_t              mavlink_attitude_struct;
mavlink_heartbeat_t             mavlink_heartbeat_struct;
mavlink_param_value_t           mavlink_param_value_struct;
mavlink_gps_raw_int_t           mavlink_gps_raw_int_struct;
mavlink_local_position_ned_t    mavlink_local_position_ned_struct;
mavlink_nav_controller_output_t mavlink_nav_controller_output_struct;
mavlink_statustext_t            mavlink_statustext_struct;

mavlink_mission_count_t         mavlink_mission_count_struct;
mavlink_mission_item_t          mavlink_mission_item_struct;
mavlink_mission_request_t       mavlink_mission_request_struct;
mavlink_mission_ack_t           mavlink_mission_ack_struct;
mavlink_mission_clear_all_t     mavlink_mission_clear_all_struct;
mavlink_mission_set_current_t   mavlink_mission_set_current_struct;
mavlink_mission_current_t       mavlink_mission_current_struct;
mavlink_mission_item_reached_t  mavlink_mission_item_reached_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* mailbox buffers */
static msg_t tolink_mb_buf[8];
static msg_t mavlink_param_set_mb_buf[2];
static msg_t controller_mb_buf[4];
static msg_t mavlink_command_long_mb_buf[4];
static msg_t logwriter_mb_buf[10];
static msg_t speedometer_mb_buf[1];
static msg_t mission_mb_buf[1];

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

/**
 * Signal processing thread about end of data processing
 */
void ReleaseMail(Mail* mailp){
  mailp->payload = NULL;
  if (mailp->semp != NULL)
    chBSemSignal(mailp->semp);
}

/**
 *
 */
void MsgInit(void){
  chMBInit(&tolink_mb,
      tolink_mb_buf,
      (sizeof(tolink_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlink_param_set_mb,
      mavlink_param_set_mb_buf,
      (sizeof(mavlink_param_set_mb_buf)/sizeof(msg_t)));
  chMBInit(&mavlink_command_long_mb,
      mavlink_command_long_mb_buf,
      (sizeof(mavlink_command_long_mb_buf)/sizeof(msg_t)));
  chMBInit(&controller_mb,
      controller_mb_buf,
      (sizeof(controller_mb_buf)/sizeof(msg_t)));
  chMBInit(&logwriter_mb,
      logwriter_mb_buf,
      (sizeof(logwriter_mb_buf)/sizeof(msg_t)));
  chMBInit(&speedometer_mb,
      speedometer_mb_buf,
      (sizeof(speedometer_mb_buf)/sizeof(msg_t)));
  chMBInit(&mission_mb,
      mission_mb_buf,
      (sizeof(mission_mb_buf)/sizeof(msg_t)));
}

/**
 *
 */
void MavInit(void){
  /* initial mavlink values */
  mavlink_system_struct.sysid  = 20;                   ///< ID 20 for this airplane
  mavlink_system_struct.compid = MAV_COMP_ID_ALL;     ///< The component sending the message, it could be also a Linux process
  mavlink_system_struct.state  = MAV_STATE_BOOT;
  mavlink_system_struct.mode   = MAV_MODE_PREFLIGHT;

  //mavlink_system_struct.type   = MAV_TYPE_FIXED_WING;
  mavlink_system_struct.type = *(uint8_t *)ValueSearch("SYS_mavtype");
}

