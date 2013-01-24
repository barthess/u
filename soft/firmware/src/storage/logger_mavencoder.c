/* 
!!! Atomatically generated by
src/storage/gen_logger_mavencoder.py
Do not edit it manually. 
*/
#include "logger_mavencoder.h"

extern mavlink_gps_raw_int_t mavlink_gps_raw_int_struct;
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern mavlink_raw_pressure_t mavlink_raw_pressure_struct;
extern mavlink_scaled_pressure_t mavlink_scaled_pressure_struct;
extern mavlink_sys_status_t mavlink_sys_status_struct;
extern mavlink_vfr_hud_t mavlink_vfr_hud_struct;
extern mavlink_global_position_int_t mavlink_global_position_int_struct;
extern mavlink_attitude_t mavlink_attitude_struct;
extern mavlink_heartbeat_t mavlink_heartbeat_struct;
extern mavlink_param_value_t mavlink_param_value_struct;
extern mavlink_statustext_t mavlink_statustext_struct;

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 * Autogenerated helper function.
 * Chose proper packing function based on the message type.
 */
uint16_t mavencoder(uint8_t msg_id, uint8_t system_id, uint8_t *threadsafe_buf, mavlink_message_t* msg){
  uint16_t len = 0;

  switch (msg_id){
  case MAVLINK_MSG_ID_GPS_RAW_INT:
    memcpy_ts(threadsafe_buf, &mavlink_gps_raw_int_struct, sizeof(mavlink_gps_raw_int_struct), 4);
    mavlink_msg_gps_raw_int_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_gps_raw_int_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_RAW_IMU:
    memcpy_ts(threadsafe_buf, &mavlink_raw_imu_struct, sizeof(mavlink_raw_imu_struct), 4);
    mavlink_msg_raw_imu_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_raw_imu_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_SCALED_IMU:
    memcpy_ts(threadsafe_buf, &mavlink_scaled_imu_struct, sizeof(mavlink_scaled_imu_struct), 4);
    mavlink_msg_scaled_imu_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_scaled_imu_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_RAW_PRESSURE:
    memcpy_ts(threadsafe_buf, &mavlink_raw_pressure_struct, sizeof(mavlink_raw_pressure_struct), 4);
    mavlink_msg_raw_pressure_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_raw_pressure_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_SCALED_PRESSURE:
    memcpy_ts(threadsafe_buf, &mavlink_scaled_pressure_struct, sizeof(mavlink_scaled_pressure_struct), 4);
    mavlink_msg_scaled_pressure_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_scaled_pressure_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_SYS_STATUS:
    memcpy_ts(threadsafe_buf, &mavlink_sys_status_struct, sizeof(mavlink_sys_status_struct), 4);
    mavlink_msg_sys_status_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_sys_status_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_VFR_HUD:
    memcpy_ts(threadsafe_buf, &mavlink_vfr_hud_struct, sizeof(mavlink_vfr_hud_struct), 4);
    mavlink_msg_vfr_hud_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_vfr_hud_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
    memcpy_ts(threadsafe_buf, &mavlink_global_position_int_struct, sizeof(mavlink_global_position_int_struct), 4);
    mavlink_msg_global_position_int_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_global_position_int_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_ATTITUDE:
    memcpy_ts(threadsafe_buf, &mavlink_attitude_struct, sizeof(mavlink_attitude_struct), 4);
    mavlink_msg_attitude_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_attitude_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_HEARTBEAT:
    memcpy_ts(threadsafe_buf, &mavlink_heartbeat_struct, sizeof(mavlink_heartbeat_struct), 4);
    mavlink_msg_heartbeat_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_heartbeat_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_PARAM_VALUE:
    memcpy_ts(threadsafe_buf, &mavlink_param_value_struct, sizeof(mavlink_param_value_struct), 4);
    mavlink_msg_param_value_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_param_value_t *)threadsafe_buf);
    break;

  case MAVLINK_MSG_ID_STATUSTEXT:
    memcpy_ts(threadsafe_buf, &mavlink_statustext_struct, sizeof(mavlink_statustext_struct), 4);
    mavlink_msg_statustext_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_statustext_t *)threadsafe_buf);
    break;

  default:
    chDbgPanic("ID not handled");
    break;
  }
  return len;
}