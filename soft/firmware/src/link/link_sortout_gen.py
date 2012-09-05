#!/usr/bin/env python

#           name              component id
names = [
        ("sys_status",          "ALL"),
        ("heartbeat",           "ALL"),
        ("vfr_hud",             "ALL"),
        ("param_value",         "ALL"),
        ("command_ack",         "ALL"),
        ("attitude",            "IMU"),
        ("raw_pressure",        "IMU"),
        ("raw_imu",             "IMU"),
        ("scaled_imu",          "IMU"),
        ("scaled_pressure",     "IMU"),
        ("global_position_int", "GPS"),
        ("gps_raw_int",         "GPS"),
        ("mission_count",       "MISSIONPLANNER"),
        ("mission_item",        "MISSIONPLANNER"),
        ("mission_request",     "MISSIONPLANNER"),
        ("mission_ack",         "MISSIONPLANNER"),
        ("mission_current",     "MISSIONPLANNER"),
        ("mission_item_reached","MISSIONPLANNER"),
        ]

for i in names:
    print(
    "  case MAVLINK_MSG_ID_" + str.upper(i[0]) + ":\n"
    "    len = mavlink_msg_" + i[0] + "_encode(system_id, MAV_COMP_ID_" + i[1] + ", msg, &mavlink_" + i[0] + "_struct);\n"
    "    break;"
    )

print (
'  default:\n'
'    chDbgPanic("ID not defined");\n'
'    break;'
)
