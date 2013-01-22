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
extern GlobalFlags_t GlobalFlags;

/* variable for storing system state */
mavlink_system_t                mavlink_system_struct;

/**
 * @brief   Event sources.
 */
EventSource event_gps_time_got;

EventSource event_mavlink_out_heartbeat;
EventSource event_mavlink_out_gps_raw_int;
EventSource event_mavlink_out_global_position_int;
EventSource event_mavlink_out_system_time;
EventSource event_mavlink_out_sys_status;
EventSource event_mavlink_out_statustext;
EventSource event_mavlink_out_command_ack;
EventSource event_mavlink_out_rc_channels_raw;
EventSource event_mavlink_out_param_value;
EventSource event_mavlink_out_mission_ack;
EventSource event_mavlink_out_mission_current;
EventSource event_mavlink_out_mission_item_reached;

EventSource event_mavlink_in_command_long;
EventSource event_mavlink_in_param_set;
EventSource event_mavlink_in_param_request_list;
EventSource event_mavlink_in_param_request_read;
EventSource event_mavlink_in_manual_control;
EventSource event_mavlink_in_set_mode;
EventSource event_mavlink_in_mission_set_current;
EventSource event_mavlink_in_mission_request_list;
EventSource event_mavlink_in_mission_count;
EventSource event_mavlink_in_mission_clear_all;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

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
 *
 */
void MsgInit(void){
  chEvtInit(&event_gps_time_got);

  chEvtInit(&event_mavlink_out_heartbeat);
  chEvtInit(&event_mavlink_out_gps_raw_int);
  chEvtInit(&event_mavlink_out_global_position_int);
  chEvtInit(&event_mavlink_out_system_time);
  chEvtInit(&event_mavlink_out_sys_status);
  chEvtInit(&event_mavlink_out_statustext);
  chEvtInit(&event_mavlink_out_param_value);
  chEvtInit(&event_mavlink_out_command_ack);
  chEvtInit(&event_mavlink_out_rc_channels_raw);
  chEvtInit(&event_mavlink_out_mission_ack);
  chEvtInit(&event_mavlink_out_mission_current);
  chEvtInit(&event_mavlink_out_mission_item_reached);

  chEvtInit(&event_mavlink_in_command_long);
  chEvtInit(&event_mavlink_in_param_set);
  chEvtInit(&event_mavlink_in_param_request_list);
  chEvtInit(&event_mavlink_in_param_request_read);
  chEvtInit(&event_mavlink_in_manual_control);
  chEvtInit(&event_mavlink_in_set_mode);
  chEvtInit(&event_mavlink_in_mission_set_current);
  chEvtInit(&event_mavlink_in_mission_request_list);
  chEvtInit(&event_mavlink_in_mission_count);
  chEvtInit(&event_mavlink_in_mission_clear_all);

  setGlobalFlag(GlobalFlags.messaging_ready);
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
