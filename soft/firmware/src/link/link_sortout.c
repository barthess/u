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
#define finalize_receive_mail() {                                             \
  mailp->payload = NULL;                                                      \
  if (mailp->confirmbox != NULL){                                             \
    chMBPost(mailp->confirmbox, len, TIME_IMMEDIATE);                         \
  }                                                                           \
  return len;                                                                 \
}

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern mavlink_system_t mavlink_system;

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

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * @brief Helper function.
 *
 * Определяет тип сообщения, чтобы применить правильную функцию упаковки.
 * Пакует письмо из ящика в мавлинковое сообщение.
 * ЗаNULLяет указатель на содержимое, как знак того, что данные обработаны.
 * Возвращает длинну сообщения получившегося сообщения.
 */
uint16_t sort_output_mail(Mail *mailp, mavlink_message_t *mavlink_msgbuf){
  uint16_t len;

  switch(mailp->invoice){

  case MAVLINK_MSG_ID_HEARTBEAT:
    len = mavlink_msg_heartbeat_encode(
        mavlink_system.sysid,
        MAV_COMP_ID_ALL,
        mavlink_msgbuf,
        (const mavlink_heartbeat_t*)(mailp->payload));
    finalize_receive_mail();
    break;

  case MAVLINK_MSG_ID_SYS_STATUS:
    len = mavlink_msg_sys_status_encode(
        mavlink_system.sysid,
        MAV_COMP_ID_ALL,
        mavlink_msgbuf,
        (const mavlink_sys_status_t*)(mailp->payload));
    finalize_receive_mail();
    break;

  case MAVLINK_MSG_ID_PARAM_VALUE:
    len = mavlink_msg_param_value_encode(
        mavlink_system.sysid,
        MAV_COMP_ID_ALL,
        mavlink_msgbuf,
        (const mavlink_param_value_t*)(mailp->payload));
    finalize_receive_mail();
    break;

  case MAVLINK_MSG_ID_RAW_IMU:
    len = mavlink_msg_raw_imu_encode (
        mavlink_system.sysid,
        MAV_COMP_ID_IMU,
        mavlink_msgbuf,
        (const mavlink_raw_imu_t*)(mailp->payload));
    finalize_receive_mail();
    break;

  case MAVLINK_MSG_ID_GPS_RAW_INT:
    len = mavlink_msg_gps_raw_int_encode (
        mavlink_system.sysid,
        MAV_COMP_ID_GPS,
        mavlink_msgbuf,
        (const mavlink_gps_raw_int_t*)(mailp->payload));
    finalize_receive_mail();
    break;

  case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
    len = mavlink_msg_global_position_int_encode (
        mavlink_system.sysid,
        MAV_COMP_ID_GPS,
        mavlink_msgbuf,
        (const mavlink_global_position_int_t*)(mailp->payload));
    finalize_receive_mail();
    break;

  case MAVLINK_MSG_ID_RAW_PRESSURE:
    len = mavlink_msg_raw_pressure_encode (
        mavlink_system.sysid,
        MAV_COMP_ID_IMU,
        mavlink_msgbuf,
        (const mavlink_raw_pressure_t*)(mailp->payload));
    finalize_receive_mail();
    break;

  default:
    break;
  }
  return 0;
}

#undef finalize_receive_mail
