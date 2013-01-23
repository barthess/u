/* 
!!! Atomatically generated by
src/link/gen_link_packer.py
Do not edit it manually. 
*/
#include "uav.h"

extern mavlink_system_t mavlink_system_struct;

extern GlobalFlags_t GlobalFlags;

extern mavlink_gps_raw_int_t mavlink_gps_raw_int_struct;
extern EventSource event_mavlink_out_gps_raw_int;

extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern EventSource event_mavlink_out_raw_imu;

extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern EventSource event_mavlink_out_scaled_imu;

extern mavlink_raw_pressure_t mavlink_raw_pressure_struct;
extern EventSource event_mavlink_out_raw_pressure;

extern mavlink_scaled_pressure_t mavlink_scaled_pressure_struct;
extern EventSource event_mavlink_out_scaled_pressure;

extern mavlink_sys_status_t mavlink_sys_status_struct;
extern EventSource event_mavlink_out_sys_status;

extern mavlink_vfr_hud_t mavlink_vfr_hud_struct;
extern EventSource event_mavlink_out_vfr_hud;

extern mavlink_global_position_int_t mavlink_global_position_int_struct;
extern EventSource event_mavlink_out_global_position_int;

extern mavlink_attitude_t mavlink_attitude_struct;
extern EventSource event_mavlink_out_attitude;

extern mavlink_heartbeat_t mavlink_heartbeat_struct;
extern EventSource event_mavlink_out_heartbeat;

extern mavlink_param_value_t mavlink_param_value_struct;
extern EventSource event_mavlink_out_param_value;

extern mavlink_statustext_t mavlink_statustext_struct;
extern EventSource event_mavlink_out_statustext;


void PackCycle(SerialDriver *sdp){
  struct EventListener el_gps_raw_int;
  chEvtRegisterMask(&event_mavlink_out_gps_raw_int, &el_gps_raw_int, EVMSK_MAVLINK_OUT_GPS_RAW_INT);

  struct EventListener el_raw_imu;
  chEvtRegisterMask(&event_mavlink_out_raw_imu, &el_raw_imu, EVMSK_MAVLINK_OUT_RAW_IMU);

  struct EventListener el_scaled_imu;
  chEvtRegisterMask(&event_mavlink_out_scaled_imu, &el_scaled_imu, EVMSK_MAVLINK_OUT_SCALED_IMU);

  struct EventListener el_raw_pressure;
  chEvtRegisterMask(&event_mavlink_out_raw_pressure, &el_raw_pressure, EVMSK_MAVLINK_OUT_RAW_PRESSURE);

  struct EventListener el_scaled_pressure;
  chEvtRegisterMask(&event_mavlink_out_scaled_pressure, &el_scaled_pressure, EVMSK_MAVLINK_OUT_SCALED_PRESSURE);

  struct EventListener el_sys_status;
  chEvtRegisterMask(&event_mavlink_out_sys_status, &el_sys_status, EVMSK_MAVLINK_OUT_SYS_STATUS);

  struct EventListener el_vfr_hud;
  chEvtRegisterMask(&event_mavlink_out_vfr_hud, &el_vfr_hud, EVMSK_MAVLINK_OUT_VFR_HUD);

  struct EventListener el_global_position_int;
  chEvtRegisterMask(&event_mavlink_out_global_position_int, &el_global_position_int, EVMSK_MAVLINK_OUT_GLOBAL_POSITION_INT);

  struct EventListener el_attitude;
  chEvtRegisterMask(&event_mavlink_out_attitude, &el_attitude, EVMSK_MAVLINK_OUT_ATTITUDE);

  struct EventListener el_heartbeat;
  chEvtRegisterMask(&event_mavlink_out_heartbeat, &el_heartbeat, EVMSK_MAVLINK_OUT_HEARTBEAT);

  struct EventListener el_param_value;
  chEvtRegisterMask(&event_mavlink_out_param_value, &el_param_value, EVMSK_MAVLINK_OUT_PARAM_VALUE);

  struct EventListener el_statustext;
  chEvtRegisterMask(&event_mavlink_out_statustext, &el_statustext, EVMSK_MAVLINK_OUT_STATUSTEXT);

  eventmask_t evt = 0;
  mavlink_message_t mavlink_message_struct;
  uint8_t sendbuf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len = 0;
  while (!chThdShouldTerminate()) {
    evt = chEvtWaitOneTimeout(EVMSK_MAVLINK_OUT_GPS_RAW_INT | EVMSK_MAVLINK_OUT_RAW_IMU | EVMSK_MAVLINK_OUT_SCALED_IMU | EVMSK_MAVLINK_OUT_RAW_PRESSURE | EVMSK_MAVLINK_OUT_SCALED_PRESSURE | EVMSK_MAVLINK_OUT_SYS_STATUS | EVMSK_MAVLINK_OUT_VFR_HUD | EVMSK_MAVLINK_OUT_GLOBAL_POSITION_INT | EVMSK_MAVLINK_OUT_ATTITUDE | EVMSK_MAVLINK_OUT_HEARTBEAT | EVMSK_MAVLINK_OUT_PARAM_VALUE | EVMSK_MAVLINK_OUT_STATUSTEXT, MS2ST(50));
    switch(evt){
    case EVMSK_MAVLINK_OUT_GPS_RAW_INT:
      memcpy_ts(sendbuf, &mavlink_gps_raw_int_struct, sizeof(mavlink_gps_raw_int_struct), 4);
      mavlink_msg_gps_raw_int_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_gps_raw_int_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_RAW_IMU:
      memcpy_ts(sendbuf, &mavlink_raw_imu_struct, sizeof(mavlink_raw_imu_struct), 4);
      mavlink_msg_raw_imu_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_raw_imu_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_SCALED_IMU:
      memcpy_ts(sendbuf, &mavlink_scaled_imu_struct, sizeof(mavlink_scaled_imu_struct), 4);
      mavlink_msg_scaled_imu_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_scaled_imu_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_RAW_PRESSURE:
      memcpy_ts(sendbuf, &mavlink_raw_pressure_struct, sizeof(mavlink_raw_pressure_struct), 4);
      mavlink_msg_raw_pressure_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_raw_pressure_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_SCALED_PRESSURE:
      memcpy_ts(sendbuf, &mavlink_scaled_pressure_struct, sizeof(mavlink_scaled_pressure_struct), 4);
      mavlink_msg_scaled_pressure_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_scaled_pressure_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_SYS_STATUS:
      memcpy_ts(sendbuf, &mavlink_sys_status_struct, sizeof(mavlink_sys_status_struct), 4);
      mavlink_msg_sys_status_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_sys_status_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_VFR_HUD:
      memcpy_ts(sendbuf, &mavlink_vfr_hud_struct, sizeof(mavlink_vfr_hud_struct), 4);
      mavlink_msg_vfr_hud_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_vfr_hud_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_GLOBAL_POSITION_INT:
      memcpy_ts(sendbuf, &mavlink_global_position_int_struct, sizeof(mavlink_global_position_int_struct), 4);
      mavlink_msg_global_position_int_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_global_position_int_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_ATTITUDE:
      memcpy_ts(sendbuf, &mavlink_attitude_struct, sizeof(mavlink_attitude_struct), 4);
      mavlink_msg_attitude_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_attitude_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_HEARTBEAT:
      memcpy_ts(sendbuf, &mavlink_heartbeat_struct, sizeof(mavlink_heartbeat_struct), 4);
      mavlink_msg_heartbeat_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_heartbeat_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_PARAM_VALUE:
      memcpy_ts(sendbuf, &mavlink_param_value_struct, sizeof(mavlink_param_value_struct), 4);
      mavlink_msg_param_value_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_param_value_t *)sendbuf);
      break;

    case EVMSK_MAVLINK_OUT_STATUSTEXT:
      memcpy_ts(sendbuf, &mavlink_statustext_struct, sizeof(mavlink_statustext_struct), 4);
      mavlink_msg_statustext_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_statustext_t *)sendbuf);
      break;


    default: // probably timeout
      continue;
      break;
    }
    /* write in port after exiting from case */
    if (GlobalFlags.tlm_link_ready){
      len = mavlink_msg_to_send_buffer(sendbuf, &mavlink_message_struct);
      sdWrite(sdp, sendbuf, len);
    }
  }
  chEvtUnregister(&event_mavlink_out_gps_raw_int, &el_gps_raw_int);
  chEvtUnregister(&event_mavlink_out_raw_imu, &el_raw_imu);
  chEvtUnregister(&event_mavlink_out_scaled_imu, &el_scaled_imu);
  chEvtUnregister(&event_mavlink_out_raw_pressure, &el_raw_pressure);
  chEvtUnregister(&event_mavlink_out_scaled_pressure, &el_scaled_pressure);
  chEvtUnregister(&event_mavlink_out_sys_status, &el_sys_status);
  chEvtUnregister(&event_mavlink_out_vfr_hud, &el_vfr_hud);
  chEvtUnregister(&event_mavlink_out_global_position_int, &el_global_position_int);
  chEvtUnregister(&event_mavlink_out_attitude, &el_attitude);
  chEvtUnregister(&event_mavlink_out_heartbeat, &el_heartbeat);
  chEvtUnregister(&event_mavlink_out_param_value, &el_param_value);
  chEvtUnregister(&event_mavlink_out_statustext, &el_statustext);
}