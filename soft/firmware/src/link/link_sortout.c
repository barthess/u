#include "ch.h"
#include "hal.h"

#include "link.h"
#include "link_sortout.h"
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
extern mavlink_system_t mavlink_system_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */

/**
 * Autogenerated helper function.
 */
static uint16_t megamavlink(uint8_t msg_id, uint8_t system_id, mavlink_message_t* msg, const void *content){
  uint16_t len;
  len = 0;

  switch (msg_id){
  case MAVLINK_MSG_ID_SYS_STATUS:
    len = mavlink_msg_sys_status_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_sys_status_t*)content);
    break;
  case MAVLINK_MSG_ID_HEARTBEAT:
    len = mavlink_msg_heartbeat_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_heartbeat_t*)content);
    break;
  case MAVLINK_MSG_ID_VFR_HUD:
    len = mavlink_msg_vfr_hud_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_vfr_hud_t*)content);
    break;
  case MAVLINK_MSG_ID_PARAM_VALUE:
    len = mavlink_msg_param_value_encode(system_id, MAV_COMP_ID_ALL, msg, (mavlink_param_value_t*)content);
    break;
  case MAVLINK_MSG_ID_SET_MODE:
    len = mavlink_msg_set_mode_encode(system_id, MAV_COMP_ID_IMU, msg, (mavlink_set_mode_t*)content);
    break;
  case MAVLINK_MSG_ID_ATTITUDE:
    len = mavlink_msg_attitude_encode(system_id, MAV_COMP_ID_IMU, msg, (mavlink_attitude_t*)content);
    break;
  case MAVLINK_MSG_ID_RAW_PRESSURE:
    len = mavlink_msg_raw_pressure_encode(system_id, MAV_COMP_ID_IMU, msg, (mavlink_raw_pressure_t*)content);
    break;
  case MAVLINK_MSG_ID_RAW_IMU:
    len = mavlink_msg_raw_imu_encode(system_id, MAV_COMP_ID_IMU, msg, (mavlink_raw_imu_t*)content);
    break;
  case MAVLINK_MSG_ID_SCALED_IMU:
    len = mavlink_msg_scaled_imu_encode(system_id, MAV_COMP_ID_IMU, msg, (mavlink_scaled_imu_t*)content);
    break;
  case MAVLINK_MSG_ID_SCALED_PRESSURE:
    len = mavlink_msg_scaled_pressure_encode(system_id, MAV_COMP_ID_IMU, msg, (mavlink_scaled_pressure_t*)content);
    break;
  case MAVLINK_MSG_ID_COMMAND_LONG:
    len = mavlink_msg_command_long_encode(system_id, MAV_COMP_ID_IMU, msg, (mavlink_command_long_t*)content);
    break;
  case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
    len = mavlink_msg_global_position_int_encode(system_id, MAV_COMP_ID_GPS, msg, (mavlink_global_position_int_t*)content);
    break;
  case MAVLINK_MSG_ID_GPS_RAW_INT:
    len = mavlink_msg_gps_raw_int_encode(system_id, MAV_COMP_ID_GPS, msg, (mavlink_gps_raw_int_t*)content);
    break;
  default:
    chDbgPanic("ID not defined");
    break;
  }
  return len;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * @brief Helper function.
 *
 * ���������� ��� ���������, ����� ��������� ���������� ������� ��������.
 * ������ ������ �� ����� � ����������� ���������.
 * ��NULL��� ��������� �� ����������, ��� ���� ����, ��� ������ ����������.
 * ���������� ������ ��������� ������������� ���������.
 */
uint16_t sort_output_mail(Mail *mailp, mavlink_message_t *mavlink_msgbuf){
  uint16_t len;

  len = megamavlink(mailp->invoice,
                    mavlink_system_struct.sysid,
                    mavlink_msgbuf,
                    mailp->payload);

  if (len != 0){
    mailp->payload = NULL;
    if (mailp->confirmbox != NULL){
      chMBPost(mailp->confirmbox, len, TIME_IMMEDIATE);
    }
  }

  return len;
}




/*
 *******************************************************************************
 * OLD JUNK
 *******************************************************************************
 */

/* */
#define SENDCASE(lowercase, UPPERCASE, ID){                                   \
case MAVLINK_MSG_ID_##UPPERCASE:                                              \
  len = mavlink_msg_##lowercase##_encode (                                    \
        mavlink_system_struct.sysid,                                          \
        MAV_COMP_ID_##ID,                                                     \
        mavlink_msgbuf,                                                       \
        (const mavlink_##lowercase##_t*)(mailp->payload));                    \
  mailp->payload = NULL;                                                      \
  if (mailp->confirmbox != NULL){                                             \
    chMBPost(mailp->confirmbox, len, TIME_IMMEDIATE);                         \
  }                                                                           \
  return len;                                                                 \
  break;                                                                      \
}

//uint16_t sort_output_mail(Mail *mailp, mavlink_message_t *mavlink_msgbuf){
//  uint16_t len;
//
//  len = megamavlink(mailp->invoice,
//                    mavlink_system_struct.sysid,
//                    MAV_COMP_ID_ALL,
//                    mavlink_msgbuf,
//                    mailp->payload);
//
//  if (len != 0){
//    mailp->payload = NULL;
//    if (mailp->confirmbox != NULL){
//      chMBPost(mailp->confirmbox, len, TIME_IMMEDIATE);
//    }
//  }
//
//  switch(mailp->invoice){
//
//    SENDCASE(heartbeat, HEARTBEAT,                      ALL)
//    SENDCASE(sys_status, SYS_STATUS,                    ALL)
//    SENDCASE(param_value, PARAM_VALUE,                  ALL)
//    SENDCASE(vfr_hud, VFR_HUD,                          ALL)
//
//    SENDCASE(gps_raw_int, GPS_RAW_INT,                  GPS)
//    SENDCASE(global_position_int, GLOBAL_POSITION_INT,  GPS)
//
//    SENDCASE(raw_imu, RAW_IMU,                          IMU)
//    SENDCASE(scaled_imu, SCALED_IMU,                    IMU)
//    SENDCASE(attitude, ATTITUDE,                        IMU)
//    SENDCASE(attitude_quaternion, ATTITUDE_QUATERNION,  IMU)
//    SENDCASE(raw_pressure, RAW_PRESSURE,                IMU)
//
//  default:
//    break;
//  }
//  return len;
//}





