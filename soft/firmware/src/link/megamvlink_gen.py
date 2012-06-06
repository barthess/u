#!/usr/bin/env python

# test

names = ["sys_status",
        "heartbeat",
        "raw_pressure",
        "raw_imu",
        "scaled_imu",
        "scaled_pressure",
        "command_long",
        "vfr_hud",
        "set_mode",
        "global_position_int",
        "attitude",
        "param_value",
        ]

for i in names:
    print(
    "  case MAVLINK_MSG_ID_" + str.upper(i) + ":\n"
    "    len = mavlink_msg_" + i + "_encode(system_id, component_id, msg, (mavlink_" + i + "_t*)content);\n"
    "    break;"
    )

print (
'  default:\n'
'    chDbgPanic("ID not defined");\n'
'    break;'
)
