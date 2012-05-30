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

    SENDCASE(heartbeat, HEARTBEAT,                      ALL)
    SENDCASE(sys_status, SYS_STATUS,                    ALL)
    SENDCASE(param_value, PARAM_VALUE,                  ALL)
    SENDCASE(vfr_hud, VFR_HUD,                          ALL)

    SENDCASE(gps_raw_int, GPS_RAW_INT,                  GPS)
    SENDCASE(global_position_int, GLOBAL_POSITION_INT,  GPS)

    SENDCASE(raw_imu, RAW_IMU,                          IMU)
    SENDCASE(scaled_imu, SCALED_IMU,                    IMU)
    SENDCASE(attitude, ATTITUDE,                        IMU)
    SENDCASE(attitude_quaternion, ATTITUDE_QUATERNION,  IMU)
    SENDCASE(raw_pressure, RAW_PRESSURE,                IMU)

  default:
    break;
  }
  return 0;
}


