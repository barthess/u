#!/usr/bin/env python

#       message name            mail struct for it      mailbox for it
names = [
        ("param_request_list",  "param_set_mail",       "mavlink_param_set_mb"),
        ("param_request_read",  "param_set_mail",       "mavlink_param_set_mb"),
        ("param_set",           "param_set_mail",       "mavlink_param_set_mb"),
        ("command_long",        "command_long_mail",    "mavlink_command_long_mb"),
        ("manual_control",      "manual_control_mail",  "controller_mb"),
        ("set_mode",            "set_mode_mail",        "controller_mb"),
        ]

for i in names:
    print(
    "  /* automatically generated handler */\n"
    "  case MAVLINK_MSG_ID_" + str.upper(i[0]) + ":\n"
    "    mavlink_msg_" + i[0] + "_decode(msg, &mavlink_" + i[0] + "_struct);\n"
    "    if (mavlink_" + i[0] + "_struct.target_system != mavlink_system_struct.sysid)\n"
    "      return LINK_SUCCESS; /* silently ignore messages not for this system */\n"
    "    " + i[1] + ".invoice = MAVLINK_MSG_ID_" + str.upper(i[0]) + ";\n"
    "    " + i[1] + ".payload = &mavlink_" + i[0] + "_struct;\n"
    "    status = chMBPost(&" + i[2] + ", (msg_t)&" + i[1] +", TIME_IMMEDIATE);\n"
    "    if (status != RDY_OK)\n"
    "      return LINK_FAILED;\n"
    "    else\n"
    "      return LINK_SUCCESS;\n"
    "    break;\n"
    )

