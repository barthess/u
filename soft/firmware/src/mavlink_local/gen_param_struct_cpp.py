#!/usr/bin/env python
# -*- coding: utf-8 -*-


import argparse

parser = argparse.ArgumentParser(description='Description will be here.')
parser.add_argument('-n', '--name', metavar='N', type=str, required=True,
                   help='Subsystem name. Can be `ns`, or `acs`')
args = parser.parse_args()



# C name of array with values in RAM
arr = "gp_val"

SERVO_MIN   = 1000
SERVO_MAX   = 2000

SEND_MIN    = 20
SEND_MAX    = 5000

ONBOARD_PARAM_NAME_LENGTH = 15

#    key            min     default max     type checker    help
param_ns = [
("SYS_ID",          1,      20,     255,    "u", "default", "System ID.\\n This value MUST BE FIRST in param structure. Value 0 reserved for ground station."),
("SYS_mavtype",     0,      10,     16,     "u", "default", "Autopilot type (0 - generic, 1 - fixed wing, 10 - ground rover).\\nOther types you can found in enum MAV_TYPE \\nNOTE! You MUST REBOOT device after changing it."),
("SH_enable",       0,      0,      1,      "u", "default", "Set to 1 to switch off telemetry sending and enabling shell."),

("IMU_still_thr",   100,    10000,  100000, "u", "default", "Stillness threshold of device during calibration (micro g).\\n If acceleration delta less than this value that device is still"),

#/* veights of different components */
("IMU_accweight",   0.0,    0.005,  0.1,    "f", "default", "NULL"),
("IMU_magweight",   0.0,    0.05,   0.9,    "f", "default", "NULL"),
("IMU_gpsweight",   0.0,    0.05,   0.1,    "f", "default", "NULL"),
("IMU_reserved1",   -1,     0,      1,      "f", "default", "NULL"),
("IMU_reserved2",   -1,     0,      1,      "f", "default", "NULL"),
("IMU_reserved3",   -1,     0,      1,      "f", "default", "NULL"),

# /**** Magnetometer ****/
# /* zero offsets */
("MAG_xoffset",     -5000,  0,      5000,   "i", "default", "NULL"),
("MAG_yoffset",     -5000,  0,      5000,   "i", "default", "NULL"),
("MAG_zoffset",     -5000,  0,      5000,   "i", "default", "NULL"),
# /* axis sensitivity */
("MAG_xsens",       0.001,  0.1,    1.0,    "f", "default", "NULL"),
("MAG_ysens",       0.001,  0.1,    1.0,    "f", "default", "NULL"),
("MAG_zsens",       0.001,  0.1,    1.0,    "f", "default", "NULL"),
# /* axis polarities. Relative to device axis */
("MAG_xpol",        -1,     1,      1,      "i", "polarity","NULL"),
("MAG_ypol",        -1,     1,      1,      "i", "polarity","NULL"),
("MAG_zpol",        -1,     1,      1,      "i", "polarity","NULL"),
# /* declination in degrees */
("MAG_declinate",   -90,    7,      90,     "i", "default", "Magnetic declination. \\nThe declination is positive when the magnetic north is east of true north. \\nhttp://www.ngdc.noaa.gov/geomagmodels/Declination.jsp"),
# /* count of samples to zero calibration */
("MAG_zerocnt",     256,    512,    4096,   "i", "default", "NULL"),
("MAG_sortmtrx",    0, 0b100010001, 1,      "u", "sort_mtrx","Sorting matrix for acquired gyro values\\nto correspond with real device axis"),
("MAG_reserved2",   0,      0,      4096,   "u", "default", "NULL"),

#/**** accelerometer ****/
#/* zero offsets */
("ACC_xoffset",     -100,   0,      100,    "i", "default", "NULL"),
("ACC_yoffset",     -100,   0,      100,    "i", "default", "NULL"),
("ACC_zoffset",     -100,   0,      100,    "i", "default", "NULL"),
#/* sens LSB/g, nominals: 4096, 8192, 16384 ****/
("ACC_xsens",       3000,   8192,   17000,  "u", "default", "sens LSB/g, nominals: 4096, 8192, 16384"),
("ACC_ysens",       3000,   8192,   17000,  "u", "default", "sens LSB/g, nominals: 4096, 8192, 16384"),
("ACC_zsens",       3000,   8192,   17000,  "u", "default", "sens LSB/g, nominals: 4096, 8192, 16384"),
#/* axis polarities. Relative to device axis  */
("ACC_xpol",        -1,     1,      1,      "i", "polarity","NULL"),
("ACC_ypol",        -1,     1,      1,      "i", "polarity","NULL"),
("ACC_zpol",        -1,     1,      1,      "i", "polarity","NULL"),
("ACC_sortmtrx",    0, 0b100010001, 1,      "u", "sort_mtrx","Sorting matrix for acquired gyro values\\nto correspond with real device axis"),
("ACC_reserved2",   -1,     1,      1,      "i", "default", "NULL"),

#/* Gyroscope */
#/* sens (LSB/(deg/s)) */
("GYRO_xsens",      7.0,    14.375, 30.0,   "f", "default", "NULL"),
("GYRO_ysens",      7.0,    14.375, 30.0,   "f", "default", "NULL"),
("GYRO_zsens",      7.0,    14.375, 30.0,   "f", "default", "NULL"),
#/* polarities */
("GYRO_xpol",       -1,     1,      1,      "i", "polarity","NULL"),
("GYRO_ypol",       -1,     1,      1,      "i", "polarity","NULL"),
("GYRO_zpol",       -1,     1,      1,      "i", "polarity","NULL"),
#/* sens (LSB/(deg/s)) */
("GYRO_xoffset",    -70.0,  0.0,    70.0,   "f", "default", "NULL"),
("GYRO_yoffset",    -70.0,  0.0,    70.0,   "f", "default", "NULL"),
("GYRO_zoffset",    -70.0,  0.0,    70.0,   "f", "default", "NULL"),

("GYRO_zerocnt",    512,    2048,   16384,  "i", "default", "Sample count for zeroing using accumulated sums"),
("GYRO_x_zerosum",  -20000000, 0, 20000000, "i", "default", "accumulated sum X"),
("GYRO_y_zerosum",  -20000000, 0, 20000000, "i", "default", "accumulated sum Y"),
("GYRO_z_zerosum",  -20000000, 0, 20000000, "i", "default", "accumulated sum Z"),
("GYRO_sortmtrx",   0,  0b100010001, 1,     "u", "sort_mtrx","Sorting matrix for acquired gyro values\\nto correspond with real device axis"),

("GYRO_reserved3",  -20000000, 0, 20000000, "i", "default", "NULL"),

#/**** PMU - pressure measurement unit ****/
#// coefficients for thermal compensation
("PMU_reserved0",   -2000000, 0, 2000000,   "i", "default", "NULL"),
("PMU_reserved1",   -2000000, 0, 2000000,   "i", "default", "NULL"),

#/* intervals between sending different data (mS) */
("T_raw_imu",       SEND_MIN, 0, SEND_MAX, "u", "send_tmo","Interval of sending this data in milliseconds.\\nSet it to 0 for disabling"),
("T_raw_press",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","Timeout help here"),
("T_scal_imu",      SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_scal_press",    SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_attitude",      SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_vfr_hud",       SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_gps_int",       SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_sys_status",    SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_position_ned",  SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_nav_output",    SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved2",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved3",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved4",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved5",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved6",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),

#/* Timezone. */
("TIME_zone",       -24,    0,      24,     "i", "default", "Simple offset in hours."),

#/* Length of filters for different systems. */
("FLEN_adc",        0,      6,      30,     "u", "default", "NULL"),
("FLEN_pres_dyn",   0,      6,      30,     "u", "default", "NULL"),
("FLEN_pres_stat",  0,      6,      30,     "u", "default", "NULL"),
("FLEN_climb",      0,      6,      30,     "u", "default", "NULL"),
("FLEN_reserved1",  0,      6,      30,     "u", "default", "NULL"),
("FLEN_reserved2",  0,      6,      30,     "u", "default", "NULL"),
("FLEN_reserved3",  0,      6,      30,     "u", "default", "NULL"),
("FLEN_reserved4",  0,      6,      30,     "u", "default", "NULL"),

#/**** Variables for debugging purposes ****/
("DBG_reserved0",   0,      0,      10000,  "u", "default", "NULL"),
("DBG_reserved1",   0,      0,      10000,  "u", "default", "NULL"),
("DBG_reserved2",   0,      0,      10000,  "u", "default", "NULL"),

#/**** fake field with 14 symbols name ****/
("param_end_mark",  0,      0,      1224,   "u", "default", "Fake parameter with maximum allowable name length"),
]



#    key            min     default max     type checker    help
param_acs = [
("SYS_ID",          1,      20,     255,    "u", "default", "System ID.\\n This value MUST BE FIRST in param structure. Value 0 reserved for ground station."),
("SYS_mavtype",     0,      10,     16,     "u", "default", "Autopilot type (0 - generic, 1 - fixed wing, 10 - ground rover).\\nOther types you can found in enum MAV_TYPE \\nNOTE! You MUST REBOOT device after changing it."),
("SH_enable",       0,      0,      1,      "u", "default", "Set to 1 to switch off telemetry sending and enabling shell."),

#/**** Servos coefficients ****/
("SERVO_1_min",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_1_max",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_1_neutra",  SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_2_min",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_2_max",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_2_neutra",  SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_3_min",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_3_max",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_3_neutra",  SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_4_min",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_4_max",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_4_neutra",  SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_5_min",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_5_max",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_5_neutra",  SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_6_min",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_6_max",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_6_neutra",  SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_7_min",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_7_max",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_7_neutra",  SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_8_min",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_8_max",     SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),
("SERVO_8_neutra",  SERVO_MIN, 1500, SERVO_MAX, "u", "default","NULL"),

#/* intervals between sending different data (mS) */
("T_reserved0",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved1",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved2",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved3",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved4",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved5",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),
("T_reserved6",     SEND_MIN, 0, SEND_MAX, "u", "send_tmo","NULL"),

#/* Timezone. */
("TIME_zone",       -24,    0,      24,     "i", "default", "Simple offset in hours."),

#/*  */
("SPD_pulse2m",     0.0,    0.0555555, 1.0, "f", "default", "Multiply odometer pulses count by this coefficient to get\\ntrip in meters. Coarse value is 0.05555555"),
#/**** pid coefficients for speed control ****/
("SPD_iGain",       -1.0,   0,      1.0,    "f", "default", "NULL"),
("SPD_pGain",       -200.0, 0,      200.0,  "f", "default", "NULL"),
("SPD_dGain",       -10000.0, 0, 10000.0,   "f", "default", "NULL"),
("SPD_iMin",        -10000.0, 0, 10000.0,   "f", "default", "NULL"),
("SPD_iMax",        -10000.0, 0, 10000.0,   "f", "default", "NULL"),
#/**** pid coefficients for heading control ****/
("HEAD_iGain",      -1.0,   0,      1.0,    "f", "default", "NULL"),
("HEAD_pGain",      -200.0, 0,      200.0,  "f", "default", "NULL"),
("HEAD_dGain",      -10000.0, 0, 10000.0,   "f", "default", "NULL"),
("HEAD_iMin",       -10000.0, 0, 10000.0,   "f", "default", "NULL"),
("HEAD_iMax",       -10000.0, 0, 10000.0,   "f", "default", "NULL"),
#/* device's speed limits */
("SPD_speed_min",   0.0,    0,      60.0,   "f", "default", "NULL"),
("SPD_speed_max",   0.0,    0,      60.0,   "f", "default", "NULL"),
#/**** pid coefficients for cross track correction ****/
("XTRACK_iGain",    -1.0,   0,      1.0,    "f", "default", "NULL"),
("XTRACK_pGain",    -200.0, 0,      200.0,  "f", "default", "NULL"),
("XTRACK_dGain",    -10000.0, 0, 10000.0,   "f", "default", "NULL"),
("XTRACK_iMin",     -10000.0, 0, 10000.0,   "f", "default", "NULL"),
("XTRACK_iMax",     -10000.0, 0, 10000.0,   "f", "default", "NULL"),

#/**** Variables for debugging purposes ****/
("DBG_reserved0",   0,      0,      10000,  "u", "default", "NULL"),
("DBG_reserved1",   0,      0,      10000,  "u", "default", "NULL"),
("DBG_reserved2",   0,      0,      10000,  "u", "default", "NULL"),

#/**** fake field with 14 symbols name ****/
("param_end_mark",  0,      0,      1224,   "u", "default", "Fake parameter with maximum allowable name length"),
]



# check what we have to use as parameter array
if args.name == "ns":
    param = param_ns
elif args.name == "acs":
    param = param_acs
else:
    print "wrong name"
    exit(1)


######### checkers ###############
# name lengths
for i in param:
    if len(i[0]) > ONBOARD_PARAM_NAME_LENGTH - 1: # -1 because last char must be 0x00
        print "ERROR: name", '"'+i[0]+'"', "is more than", ONBOARD_PARAM_NAME_LENGTH - 1, "characters"
        exit()

# name duplications
n = 0
while n < len(param):
    p = n + 1
    while p < len(param):
        if param[n][0] == param[p][0]:
            print "ERROR: duplicated parameter names detected"
            print param[n][0]
            exit()
        p += 1
    n += 1

# values' types
for i in param:
    if i[4] == "u" or i[4] == "i":
        if (type(i[1]) is not int) or (type(i[2]) is not int) or (type(i[3]) is not int):
            print "ERROR: type set to integer but given vales are floats."
            print i
            exit()
    if i[4] == "u" and ((i[1] < 0) or (i[2] < 0) or (i[1] < 0)):
        print "ERROR: type set to unsigned but given values are negative."
        print i
        exit()

    if (i[4] != "u") and (i[4] != "i") and (i[4] != "f"):
        print "ERROR: unsupported type"
        print i
        exit()

# boundaries
for i in param:
    if i[5] == "NULL": # for default checker
        if (i[1] <= i[2]) and (i[2] <= i[3]) and (i[1] != i[3]):
            pass
        else:
            print "ERROR: bad boundaries in", i[0]
            exit()
    else: # for different checkers
        if i[1] >= i[3]:
            print "ERROR: bad boundaries in", i[0]
            exit()


# print header
print "// This file is automatically generated."
print "// Do not edit it"
print "// open gen_param_struct.py, edit struct definition and run it to generate new file"
print "const int32_t OnboardParamCount =", str(len(param)) +";"
print """
/*
 * variable array of parameters in RAM
 */ """
print "static floatint", arr+"["+str(len(param))+"];"
print """
/**
 *
 */ """
print "const GlobalParam_t GlobalParam[] = {"


########### generator #############
n = 0
for i in param:
    # delete pythonic new line symbols and enclose in quotes text strings
    if i[6] != "NULL":
        helpstr = ""
        for s in i[6]:
            if s != "\n":
                helpstr += s
        helpstr = "\"" + helpstr + "\""
    else:
        helpstr = "NULL"

    # create checker function string
    checker = "PARAM_" + str.upper(i[5])

    # create format string
    if i[4] == "u":
        fmt = "{\"%s\", {.u32 = %u}, {.u32 = %u}, {.u32 = %u}, &%s[%u], %s, MAVLINK_TYPE_UINT32_T, %s},"
    elif i[4] == "i":
        fmt = "{\"%s\", {.i32 = %d}, {.i32 = %d}, {.i32 = %d}, &%s[%u], %s, MAVLINK_TYPE_INT32_T,  %s},"
    elif i[4] == "f":
        fmt = "{\"%s\", {.f32 = %F}, {.f32 = %F}, {.f32 = %F}, &%s[%u], %s, MAVLINK_TYPE_FLOAT,    %s},"
    else:
        print "ERROR: unsupported type"
        exit()

    print fmt % (i[0],         i[1],         i[2],        i[3], arr, n,  checker,                  helpstr)
    n += 1

print "};"
