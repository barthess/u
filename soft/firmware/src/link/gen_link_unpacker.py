#!/usr/bin/env python

names = [
    "command_long",
    "param_set",
    "param_request_list",
    "param_request_read",
    "set_mode",
    "mission_set_current",
    "mission_request_list",
    "mission_clear_all",
    "mission_count",
    "mission_item",
    "mission_request",
    "mission_ack",
    ]

head = """
#include "uav.h"
#include "global_flags.h"
#include <stdio.h>
#include "message.hpp"
#include "mavdbg.hpp"

extern GlobalFlags_t GlobalFlags;

extern mavlink_system_t mavlink_system_struct;
"""

foot = """
        default:
          snprintf(dbg_string, sizeof(dbg_string), "%s%d", "IN_MSG: can not handle ID ", msg.msgid);
          mavlink_dbg_print(MAV_SEVERITY_WARNING, dbg_string);
          break;
        }
      }
    }
  }
}"""

funchead = """

/**
 *
 */
void UnpackCycle(SerialDriver *sdp){
  mavlink_message_t msg;
  mavlink_status_t status;
  msg_t c = 0;
  char dbg_string[52];

  while(GlobalFlags.messaging_ready == 0)
    chThdSleepMilliseconds(50);

  while (!chThdShouldTerminate()) {
    c = sdGetTimeout((SerialDriver *)sdp, MS2ST(50));
    if (c != Q_TIMEOUT){
      if (mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)c, &msg, &status)) {
        switch(msg.msgid){
"""

def printcase(f, i):
    f.write("        case MAVLINK_MSG_ID_" + str.upper(i) + ":\n")
    f.write("          mavlink_msg_" + i + "_decode(&msg, &mavlink_in_" + i + "_struct);\n")
    if (i[:-3] == "heartbeat") or (i == "statustext"):
        f.write("//")
    f.write("          if (mavlink_in_" + i + "_struct.target_system == mavlink_system_struct.sysid)\n")
    f.write("            chEvtBroadcastFlags(&event_mavlink_in_" + i + ", EVMSK_MAVLINK_IN_" + str.upper(i) + ");\n")
    f.write("          break;\n\n")


def gen(arr):
    f = open("./src/link/link_unpacker.cpp", 'w')
    #f = open("./____link_unpacker.c", 'w')
    f.write("/* \n!!! Atomatically generated by\n" + __file__ + "\nDo not edit it manually. \n*/")
    f.write(head)

    for i in arr:
        f.write("extern mavlink_" + i + "_t mavlink_in_" + i + "_struct;\n")
    f.write("\n")

    for i in arr:
        f.write("extern EventSource event_mavlink_in_" + i + ";\n")
    f.write("\n")

    f.write(funchead)

    for i in arr:
        printcase(f, i)

    f.write(foot)
    f.close()

gen(names)
