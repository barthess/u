#!/usr/bin/env python

#       package name            mail struct for it
names = [
        "raw_imu",
        "scaled_imu",
        "raw_pressure",
        "sys_status",
        "global_position_int",
        "attitude",
        "scaled_pressure",
        "vfr_hud",
        "local_position_ned",
        "nav_controller_output",
        ]

print "// Atogenerated file. Do not edit it manually \n"

for i in names:
    print ("static Mail mail_"+i+" = {NULL, MAVLINK_MSG_ID_"+str.upper(i)+", NULL};")
print ""

for i in names:
    print(
    "static bool_t send_"+i+"(void){\n"
    "  msg_t status = RDY_OK;\n"
    "  mail_"+i+".payload = &mavlink_"+i+"_struct;\n"
    "  status = chMBPost(&tolink_mb, (msg_t)&mail_"+i+", TIME_IMMEDIATE);\n"
    "  if (status == RDY_OK)\n"
    "    return TLM_SUCCESS;\n"
    "  else\n"
    "    return TLM_FAILED;\n"
    "}"
    )

print "/* autoinitialized array */"
print "static tlm_registry_t Registy[] = {"
n = 10
for i in names:
    n += 1
    print(
    "    {"+str(n)+", NULL, send_"+i+"},"
    )
print "};"
