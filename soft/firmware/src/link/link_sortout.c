#include "ch.h"
#include "hal.h"

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
extern mavlink_system_t                 mavlink_system_struct;

extern mavlink_gps_raw_int_t            mavlink_gps_raw_int_struct;
extern mavlink_raw_pressure_t           mavlink_raw_pressure_struct;
extern mavlink_raw_imu_t                mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t             mavlink_scaled_imu_struct;
extern mavlink_scaled_pressure_t        mavlink_scaled_pressure_struct;
extern mavlink_sys_status_t             mavlink_sys_status_struct;
extern mavlink_command_ack_t            mavlink_command_ack_struct;
extern mavlink_vfr_hud_t                mavlink_vfr_hud_struct; /* air and ground speed values */
extern mavlink_global_position_int_t    mavlink_global_position_int_struct;
extern mavlink_attitude_t               mavlink_attitude_struct;
extern mavlink_heartbeat_t              mavlink_heartbeat_struct;
extern mavlink_param_value_t            mavlink_param_value_struct;
extern mavlink_local_position_ned_t     mavlink_local_position_ned_struct;
extern mavlink_nav_controller_output_t  mavlink_nav_controller_output_struct;
extern mavlink_statustext_t             mavlink_statustext_struct;

extern mavlink_mission_count_t          mavlink_mission_count_struct;
extern mavlink_mission_item_t           mavlink_mission_item_struct;
extern mavlink_mission_request_t        mavlink_mission_request_struct;
extern mavlink_mission_ack_t            mavlink_mission_ack_struct;
extern mavlink_mission_current_t        mavlink_mission_current_struct;
extern mavlink_mission_item_reached_t   mavlink_mission_item_reached_struct;

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

#include "link_sortout_autogenerated.c"

/**
 * @brief Helper function.
 *
 * Определяет тип сообщения, чтобы применить правильную функцию упаковки.
 * Пакует письмо из ящика в мавлинковое сообщение.
 * Сигналит через семафор сообщения отправителю, когд данные обработаны.
 * Возвращает длинну получившегося сообщения.
 */
uint16_t sort_output_mail(Mail *mailp, mavlink_message_t *mavlink_msgbuf){
  uint16_t len = 0;

  len = mavencoder(mailp->invoice, mavlink_system_struct.sysid, mavlink_msgbuf);
  ReleaseMail(mailp);
  return len;
}

