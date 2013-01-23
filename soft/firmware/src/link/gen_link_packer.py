#!/usr/bin/env python

names = [
    "gps_raw_int",
    "raw_imu",
    "scaled_imu",
    "raw_pressure",
    "scaled_pressure",
    "sys_status",
    "vfr_hud",
    "global_position_int",
    "attitude",
    "heartbeat",
    "param_value",
    "statustext",
    "mission_count",
    "mission_item",
    ]

def head(f):
    f.write("""
#include "uav.h"

extern mavlink_system_t mavlink_system_struct;

extern GlobalFlags_t GlobalFlags;

""")


def foot(f,  arr):
    f.write("""
    default: // probably timeout
      continue;
      break;
    }
    /* write in port after exiting from case */
    """)
    f.write("if (GlobalFlags.tlm_link_ready){\n")
    f.write("      len = mavlink_msg_to_send_buffer(sendbuf, &mavlink_message_struct);\n")
    f.write("      sdWrite(sdp, sendbuf, len);\n")
    f.write("    }\n")
    f.write("  }\n")

    for i in arr:
        f.write("  chEvtUnregister(&event_mavlink_out_" + i + ", &el_" + i + ");\n")
    f.write("}")


def gen(arr):
    f = open("./src/link/link_packer.c", 'w')
    f.write("/* \n!!! Atomatically generated by\n" + __file__ + "\nDo not edit it manually. \n*/")
    head(f)

    for i in arr:
        f.write("extern mavlink_" + i + "_t mavlink_" + i + "_struct;\n")
        f.write("extern EventSource event_mavlink_out_" + i + ";\n\n")

    f.write("\nvoid PackCycle(SerialDriver *sdp){\n")
    for i in arr:
        f.write("  struct EventListener el_" + i + ";\n")
        f.write("  chEvtRegisterMask(&event_mavlink_out_" + i + ", &el_" + i + ", EVMSK_MAVLINK_OUT_" + str.upper(i) + ");\n\n")
    f.write("  eventmask_t evt = 0;\n")
    f.write("  mavlink_message_t mavlink_message_struct;\n")
    f.write("  uint8_t sendbuf[MAVLINK_MAX_PACKET_LEN];\n")
    f.write("  uint16_t len = 0;\n")
    f.write("  while (!chThdShouldTerminate()) {\n")

    st = ""
    for i in arr:
        st += "EVMSK_MAVLINK_OUT_" + str.upper(i)
        st += " | "
    st = st[0:-3]
    f.write("    evt = chEvtWaitOneTimeout(" + st + ", MS2ST(50));\n")

    f.write("    switch(evt){\n")
    for i in arr:
        f.write("    case EVMSK_MAVLINK_OUT_" + str.upper(i) + ":\n")
        f.write("      memcpy_ts(sendbuf, &mavlink_" + i + "_struct, sizeof(mavlink_" + i +"_struct), 4);\n")
        f.write("      mavlink_msg_" + i + "_encode(mavlink_system_struct.sysid, MAV_COMP_ID_ALL, &mavlink_message_struct, (mavlink_" + i + "_t *)sendbuf);\n")
        f.write("      break;\n\n")
    foot(f, arr)
    f.close()

# main
gen(names)
