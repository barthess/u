#!/usr/bin/env python
# -*- coding: utf-8 -*-

#           name                    component id
names = [
        ("sys_status",              "ALL"),
        ("heartbeat",               "ALL"),
        ("vfr_hud",                 "ALL"),
        ("param_value",             "ALL"),
        ("command_ack",             "ALL"),
        ("attitude",                "IMU"),
        ("raw_pressure",            "IMU"),
        ("raw_imu",                 "IMU"),
        ("scaled_imu",              "IMU"),
        ("scaled_pressure",         "IMU"),
        ("global_position_int",     "GPS"),
        ("gps_raw_int",             "GPS"),
        ("nav_controller_output",   "ALL"),
        ("local_position_ned",      "ALL"),
        ("mission_count",           "MISSIONPLANNER"),
        ("mission_item",            "MISSIONPLANNER"),
        ("mission_request",         "MISSIONPLANNER"),
        ("mission_ack",             "MISSIONPLANNER"),
        ("mission_current",         "MISSIONPLANNER"),
        ("mission_item_reached",    "MISSIONPLANNER"),
        ("statustext",              "ALL"),
        ]


print "/* \n!!! Atomatically generated by\n", __file__, "\nDo not edit it manually. \n*/"

print """
#include "uav.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern mavlink_system_t                 mavlink_system_struct;
"""
for i in names:
    print "extern mavlink_" + i[0] + "_t mavlink_" + i[0] + "_struct;"


print """
/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 * Autogenerated helper function.
 * Chose proper packing function based on the message type.
 */
uint16_t mavencoder(uint8_t msg_id, uint8_t system_id, mavlink_message_t* msg){
  uint16_t len;
  len = 0;

  switch (msg_id){"""

for i in names:
    print(
    "  case MAVLINK_MSG_ID_" + str.upper(i[0]) + ":\n"
    "    len = mavlink_msg_" + i[0] + "_encode(system_id, MAV_COMP_ID_" + i[1] + ", msg, &mavlink_" + i[0] + "_struct);\n"
    "    break;"
    )

print"""
  default:
    chDbgPanic("ID not defined");
    break;
  }
  return len;
}

/**
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
"""
