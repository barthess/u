#!/usr/bin/env python

#       package name            mail struct for it
names = [
        ("param_request_list",  "param_set"),
        ("param_request_read",  "param_set"),
        ("param_set",           "param_set"),
        ("command_long",        "command_long"),
        ]

for i in names:
    print(
    "  /* automatically generated handler */\n"
    "  case MAVLINK_MSG_ID_" + str.upper(i[0]) + ":\n"
    "    mavlink_msg_" + i[0] + "_decode(msg, &mavlink_" + i[0] + "_struct);\n"
    "    if (mavlink_" + i[0] + "_struct.target_system != mavlink_system_struct.sysid)\n"
    "      return LINK_SUCCESS; /* silently ignore messages not for this system */\n"
    "    if (" + i[1] + "_mail.payload == NULL){\n"
    "      " + i[1] + "_mail.invoice = MAVLINK_MSG_ID_" + str.upper(i[0]) + ";\n"
    "      " + i[1] + "_mail.payload = &mavlink_" + i[0] + "_struct;\n"
    "      status = chMBPost(&mavlink_" + i[1] + "_mb, (msg_t)&" + i[1] +"_mail, TIME_IMMEDIATE);\n"
    "      if (status != RDY_OK)\n"
    "        return LINK_FAILED;\n"
    "    }\n"
    "    else\n"
    "      return LINK_SUCCESS;\n"
    "    break;\n"
    )

