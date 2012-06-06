#!/usr/bin/env python

#           name              component id
names = [
        ("sys_status",          "ALL"),
        ("heartbeat",           "ALL"),
        ("vfr_hud",             "ALL"),
        ("param_value",         "ALL"),
        ("set_mode",            "IMU"),
        ("attitude",            "IMU"),
        ("raw_pressure",        "IMU"),
        ("raw_imu",             "IMU"),
        ("scaled_imu",          "IMU"),
        ("scaled_pressure",     "IMU"),
        ("command_long",        "IMU"),
        ("global_position_int", "GPS"),
        ("gps_raw_int",         "GPS")
        ]

for i in names:
    print(
    "  case MAVLINK_MSG_ID_" + str.upper(i[0]) + ":\n"
    "    len = mavlink_msg_" + i[0] + "_encode(system_id, MAV_COMP_ID_" + i[1] + ", msg, (mavlink_" + i[0] + "_t*)content);\n"
    "    break;"
    )

print (
'  default:\n'
'    chDbgPanic("ID not defined");\n'
'    break;'
)
