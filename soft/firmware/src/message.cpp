#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "param_registry.hpp"

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
extern ParamRegistry param_registry;

/* */
chibios_rt::MailboxBuffer<1> speedometer_mb;
chibios_rt::MailboxBuffer<4> logwriter_mb;

/* variable for storing system state */
mavlink_system_t                mavlink_system_struct;

/* mavlink messages */
mavlink_raw_imu_t               mavlink_out_raw_imu_struct;
mavlink_scaled_imu_t            mavlink_out_scaled_imu_struct;
mavlink_raw_pressure_t          mavlink_out_raw_pressure_struct;
mavlink_scaled_pressure_t       mavlink_out_scaled_pressure_struct;
mavlink_sys_status_t            mavlink_out_sys_status_struct;
mavlink_vfr_hud_t               mavlink_out_vfr_hud_struct;
mavlink_global_position_int_t   mavlink_out_global_position_int_struct;
mavlink_attitude_t              mavlink_out_attitude_struct;
mavlink_heartbeat_t             mavlink_out_heartbeat_struct;
mavlink_param_value_t           mavlink_out_param_value_struct;
mavlink_gps_raw_int_t           mavlink_out_gps_raw_int_struct;
mavlink_local_position_ned_t    mavlink_out_local_position_ned_struct;
mavlink_nav_controller_output_t mavlink_out_nav_controller_output_struct;
mavlink_statustext_t            mavlink_out_statustext_struct;
mavlink_manual_control_t        mavlink_in_manual_control_struct;
mavlink_set_mode_t              mavlink_in_set_mode_struct;
mavlink_param_set_t             mavlink_in_param_set_struct;
mavlink_param_request_read_t    mavlink_in_param_request_read_struct;
mavlink_command_long_t          mavlink_in_command_long_struct;
mavlink_param_request_list_t    mavlink_in_param_request_list_struct;
mavlink_command_ack_t           mavlink_out_command_ack_struct;

mavlink_mission_count_t         mavlink_out_mission_count_struct;
mavlink_mission_item_t          mavlink_out_mission_item_struct;
mavlink_mission_request_t       mavlink_out_mission_request_struct;
mavlink_mission_request_list_t  mavlink_out_mission_request_list_struct;
mavlink_mission_ack_t           mavlink_out_mission_ack_struct;
mavlink_mission_clear_all_t     mavlink_out_mission_clear_all_struct;
mavlink_mission_set_current_t   mavlink_out_mission_set_current_struct;
mavlink_mission_current_t       mavlink_out_mission_current_struct;
mavlink_mission_item_reached_t  mavlink_out_mission_item_reached_struct;

mavlink_mission_count_t         mavlink_in_mission_count_struct;
mavlink_mission_item_t          mavlink_in_mission_item_struct;
mavlink_mission_request_t       mavlink_in_mission_request_struct;
mavlink_mission_request_list_t  mavlink_in_mission_request_list_struct;
mavlink_mission_ack_t           mavlink_in_mission_ack_struct;
mavlink_mission_clear_all_t     mavlink_in_mission_clear_all_struct;
mavlink_mission_set_current_t   mavlink_in_mission_set_current_struct;
mavlink_mission_current_t       mavlink_in_mission_current_struct;
mavlink_mission_item_reached_t  mavlink_in_mission_item_reached_struct;

/**
 * @brief   Event sources.
 */
EventSource event_gps_time_got;
EventSource event_gps_updated;

EventSource event_mavlink_out_heartbeat;
EventSource event_mavlink_out_gps_raw_int;
EventSource event_mavlink_out_system_time;
EventSource event_mavlink_out_statustext;
EventSource event_mavlink_out_command_ack;
EventSource event_mavlink_out_rc_channels_raw;
EventSource event_mavlink_out_param_value;
EventSource event_mavlink_out_raw_imu;
EventSource event_mavlink_out_scaled_imu;
EventSource event_mavlink_out_raw_pressure;
EventSource event_mavlink_out_scaled_pressure;
EventSource event_mavlink_out_sys_status;
EventSource event_mavlink_out_vfr_hud;
EventSource event_mavlink_out_global_position_int;
EventSource event_mavlink_out_attitude;
EventSource event_mavlink_out_mission_current;
EventSource event_mavlink_out_mission_item_reached;
EventSource event_mavlink_out_mission_count;  // it has input counterpart
EventSource event_mavlink_out_mission_item; // it has input counterpart
EventSource event_mavlink_out_mission_request;// it has input counterpart
EventSource event_mavlink_out_mission_ack;// it has input counterpart

EventSource event_mavlink_in_command_long;
EventSource event_mavlink_in_param_set;
EventSource event_mavlink_in_param_request_list;
EventSource event_mavlink_in_param_request_read;
EventSource event_mavlink_in_manual_control;
EventSource event_mavlink_in_set_mode;
EventSource event_mavlink_in_mission_set_current;
EventSource event_mavlink_in_mission_request_list;
EventSource event_mavlink_in_mission_clear_all;
EventSource event_mavlink_in_mission_count;   // it has output counterpart
EventSource event_mavlink_in_mission_item; // it has output counterpart
EventSource event_mavlink_in_mission_request;// it has output counterpart
EventSource event_mavlink_in_mission_ack;// it has output counterpart

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
  chEvtInit(&event_gps_updated);

  chEvtInit(&event_mavlink_out_heartbeat);
  chEvtInit(&event_mavlink_out_gps_raw_int);
  chEvtInit(&event_mavlink_out_global_position_int);
  chEvtInit(&event_mavlink_out_system_time);
  chEvtInit(&event_mavlink_out_sys_status);
  chEvtInit(&event_mavlink_out_statustext);
  chEvtInit(&event_mavlink_out_param_value);
  chEvtInit(&event_mavlink_out_command_ack);
  chEvtInit(&event_mavlink_out_rc_channels_raw);
  chEvtInit(&event_mavlink_out_raw_imu);
  chEvtInit(&event_mavlink_out_scaled_imu);
  chEvtInit(&event_mavlink_out_raw_pressure);
  chEvtInit(&event_mavlink_out_scaled_pressure);
  chEvtInit(&event_mavlink_out_sys_status);
  chEvtInit(&event_mavlink_out_vfr_hud);
  chEvtInit(&event_mavlink_out_global_position_int);
  chEvtInit(&event_mavlink_out_attitude);
  chEvtInit(&event_mavlink_out_mission_count);
  chEvtInit(&event_mavlink_out_mission_item);
  chEvtInit(&event_mavlink_out_mission_request);
  chEvtInit(&event_mavlink_out_mission_current);
  chEvtInit(&event_mavlink_out_mission_item_reached);
  chEvtInit(&event_mavlink_out_mission_ack);

  chEvtInit(&event_mavlink_in_command_long);
  chEvtInit(&event_mavlink_in_param_set);
  chEvtInit(&event_mavlink_in_param_request_list);
  chEvtInit(&event_mavlink_in_param_request_read);
  chEvtInit(&event_mavlink_in_manual_control);
  chEvtInit(&event_mavlink_in_set_mode);
  chEvtInit(&event_mavlink_in_mission_set_current);
  chEvtInit(&event_mavlink_in_mission_count);
  chEvtInit(&event_mavlink_in_mission_clear_all);
  chEvtInit(&event_mavlink_in_mission_item);
  chEvtInit(&event_mavlink_in_mission_request);
  chEvtInit(&event_mavlink_in_mission_request_list);
  chEvtInit(&event_mavlink_in_mission_ack);

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
  mavlink_system_struct.type = *(uint8_t *)param_registry.valueSearch("SYS_mavtype");
}

/**
 *
 */
void ParamSendOut(void){
  chEvtBroadcastFlags(&event_mavlink_out_param_value, EVMSK_MAVLINK_OUT_PARAM_VALUE);
}
