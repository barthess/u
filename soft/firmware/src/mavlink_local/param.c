#include <math.h>
#include <string.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define PARAM_CONFIRM_TMO   MS2ST(1000)
#define PARAM_POST_TMO      MS2ST(50)

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;
extern Mailbox mavlink_param_set_mb;
extern Mailbox tolink_mb;
extern mavlink_system_t mavlink_system_struct;
extern mavlink_param_value_t mavlink_param_value_struct;

int32_t OnboardParamCount = 0;

/*
 * variable array of parameters in RAM
 */
static floatint gd_val[128];

/**
 *
 */
const GlobalParam_t global_data[] = {
  /*  key             min                  val            max                  type                       */
  /*-------------------------------------------------------------------------------------------------------*/
  {"SYS_ID",          {.u32 = 1},          &gd_val[0],    {.u32 = 255},         MAVLINK_TYPE_UINT32_T, "System ID. Value 0 reserved for ground station."},

  /* Atopilot type (MAV_TYPE enum) to be able to switch between car and plane.
   * You need to reboot after changing it. */
  {"SYS_mavtype",     {.u32 = 0},          &gd_val[1],    {.u32 = 16},          MAVLINK_TYPE_UINT32_T, "Autopilot type (0 - generic, 1 - fixed wing, 10 - ground rover).\nOther types you can found in enum MAV_TYPE \nNOTE! You MUST REBOOT device after changing it."},

  /**** всякие флаги для коммандной оболочки ****/
  {"SH_enable",       {.u32 = 0},          &gd_val[2],    {.u32 = 1},           MAVLINK_TYPE_UINT32_T, NULL},

  /**** IMU - inertial measurement unit */
  /* Milli g. If acceleration delta < this value that device is still */
  {"IMU_still_thr",   {.u32 = 100},        &gd_val[3],    {.u32 = 100000},      MAVLINK_TYPE_UINT32_T, NULL},
  /* veights of different components */
  {"IMU_accweight",   {.f32 = 0.0},        &gd_val[4],    {.f32 = 0.1},         MAVLINK_TYPE_FLOAT, NULL},
  {"IMU_magweight",   {.f32 = 0.0},        &gd_val[5],    {.f32 = 0.9},         MAVLINK_TYPE_FLOAT, NULL},
  {"IMU_gpsweight",   {.f32 = 0.0},        &gd_val[6],    {.f32 = 0.1},         MAVLINK_TYPE_FLOAT, NULL},
  {"IMU_reserved1",   {.f32 = -1},         &gd_val[7],    {.f32 = 1},           MAVLINK_TYPE_FLOAT, NULL},
  {"IMU_reserved2",   {.f32 = -1},         &gd_val[8],    {.f32 = 1},           MAVLINK_TYPE_FLOAT, NULL},
  {"IMU_reserved3",   {.f32 = -1},         &gd_val[9],    {.f32 = 1},           MAVLINK_TYPE_FLOAT, NULL},

  /**** Magnetometer ****/
  /* zero offsets */
  {"MAG_xoffset",     {.i32 = -5000},      &gd_val[10],    {.i32 = 5000},       MAVLINK_TYPE_INT32_T, NULL},
  {"MAG_yoffset",     {.i32 = -5000},      &gd_val[11],    {.i32 = 5000},       MAVLINK_TYPE_INT32_T, NULL},
  {"MAG_zoffset",     {.i32 = -5000},      &gd_val[12],    {.i32 = 5000},       MAVLINK_TYPE_INT32_T, NULL},
  /* axis sensitivity */
  {"MAG_xsens",       {.f32 = 0.001},      &gd_val[13],    {.f32 = 1.0},        MAVLINK_TYPE_FLOAT, NULL},
  {"MAG_ysens",       {.f32 = 0.001},      &gd_val[14],    {.f32 = 1.0},        MAVLINK_TYPE_FLOAT, NULL},
  {"MAG_zsens",       {.f32 = 0.001},      &gd_val[15],    {.f32 = 1.0},        MAVLINK_TYPE_FLOAT, NULL},
  /* axis polarities. Relative to device axis */
  {"MAG_xpol",        {.i32 = -1},         &gd_val[16],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  {"MAG_ypol",        {.i32 = -1},         &gd_val[17],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  {"MAG_zpol",        {.i32 = -1},         &gd_val[18],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  /* declination in degrees */
  {"MAG_declinate",   {.f32 = -90},        &gd_val[19],    {.f32 = 90},         MAVLINK_TYPE_FLOAT, "Magnetic declination. \nThe declination is positive when the magnetic north is east of true north. \nhttp://www.ngdc.noaa.gov/geomagmodels/Declination.jsp"},
  /* count of samples to zero calibration */
  {"MAG_zerocnt",     {.i32 = 256},        &gd_val[20],    {.i32 = 4096},       MAVLINK_TYPE_INT32_T, NULL},
  {"MAG_reserved1",   {.i32 = 0},          &gd_val[21],    {.i32 = 4096},       MAVLINK_TYPE_INT32_T, NULL},
  {"MAG_reserved2",   {.i32 = 0},          &gd_val[22],    {.i32 = 4096},       MAVLINK_TYPE_INT32_T, NULL},

  /**** accelerometer ****/
  /* zero offsets */
  {"ACC_xoffset",     {.i32 = -100},       &gd_val[23],    {.i32 = 100},        MAVLINK_TYPE_INT32_T, NULL},
  {"ACC_yoffset",     {.i32 = -100},       &gd_val[24],    {.i32 = 100},        MAVLINK_TYPE_INT32_T, NULL},
  {"ACC_zoffset",     {.i32 = -100},       &gd_val[25],    {.i32 = 100},        MAVLINK_TYPE_INT32_T, NULL},
  /* sens LSB/g, nominals: 4096, 8192, 16384 ****/
  {"ACC_xsens",       {.u32 = 3000},       &gd_val[26],    {.u32 = 17000},      MAVLINK_TYPE_UINT32_T, NULL},
  {"ACC_ysens",       {.u32 = 3000},       &gd_val[27],    {.u32 = 17000},      MAVLINK_TYPE_UINT32_T, NULL},
  {"ACC_zsens",       {.u32 = 3000},       &gd_val[28],    {.u32 = 17000},      MAVLINK_TYPE_UINT32_T, NULL},
  /* axis polarities. Relative to device axis  */
  {"ACC_xpol",        {.i32 = -1},         &gd_val[29],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  {"ACC_ypol",        {.i32 = -1},         &gd_val[30],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  {"ACC_zpol",        {.i32 = -1},         &gd_val[31],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  {"ACC_reserved1",   {.i32 = -1},         &gd_val[32],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  {"ACC_reserved2",   {.i32 = -1},         &gd_val[33],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},

  /* Gyroscopes */
  /* sens (LSB/(deg/s)) */
  {"GYRO_xsens",      {.f32 = 7.0},        &gd_val[34],    {.f32 = 30.0},       MAVLINK_TYPE_FLOAT, NULL},
  {"GYRO_ysens",      {.f32 = 7.0},        &gd_val[35],    {.f32 = 30.0},       MAVLINK_TYPE_FLOAT, NULL},
  {"GYRO_zsens",      {.f32 = 7.0},        &gd_val[36],    {.f32 = 30.0},       MAVLINK_TYPE_FLOAT, NULL},
  /* polarities */
  {"GYRO_xpol",       {.i32 = -1},         &gd_val[37],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  {"GYRO_ypol",       {.i32 = -1},         &gd_val[38],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  {"GYRO_zpol",       {.i32 = -1},         &gd_val[39],    {.i32 = 1},          MAVLINK_TYPE_INT32_T, NULL},
  /* sample count for zeroing */
  {"GYRO_zerocnt",    {.u32 = 0},          &gd_val[40],    {.u32 = 16384},      MAVLINK_TYPE_UINT32_T, NULL},
  {"GYRO_reserv1",    {.u32 = 0},          &gd_val[41],    {.u32 = 16384},      MAVLINK_TYPE_UINT32_T, NULL},
  {"GYRO_reserv2",    {.u32 = 0},          &gd_val[42],    {.u32 = 16384},      MAVLINK_TYPE_UINT32_T, NULL},

  /**** PMU - pressure measurement unit ****/
  // coefficients for thermal compensation
  {"PMU_reserved1",   {.i32 = -2000000},   &gd_val[43],    {.i32 = 2000000},    MAVLINK_TYPE_INT32_T, NULL},
  {"PMU_reserved2",   {.i32 = -2000000},   &gd_val[44],    {.i32 = 2000000},    MAVLINK_TYPE_INT32_T, NULL},
  {"PMU_reserved3",   {.i32 = -2000000},   &gd_val[45],    {.i32 = 2000000},    MAVLINK_TYPE_INT32_T, NULL},
  {"PMU_reserved4",   {.i32 = -2000000},   &gd_val[46],    {.i32 = 2000000},    MAVLINK_TYPE_INT32_T, NULL},
  {"PMU_reserved5",   {.i32 = -2000000},   &gd_val[47],    {.i32 = 2000000},    MAVLINK_TYPE_INT32_T, NULL},

  /**** ADC coefficients ****/
  // смещение нуля датчика тока в условных единицах АЦП
  {"ADC_I_offset",    {.u32 = 0},          &gd_val[48],    {.u32 = 4096},       MAVLINK_TYPE_UINT32_T, NULL},
  // на столько надо поделить, чтобы получить амперы. Для машинки 1912, для самолета 37
  {"ADC_I_gain",      {.u32 = 0},          &gd_val[49],    {.u32 = 12240},      MAVLINK_TYPE_UINT32_T, NULL},
  // secondary voltage. на столько надо умножить, чтобы получить uV
  {"ADC_SV_gain",     {.u32 = 0},          &gd_val[50],    {.u32 = 122400},     MAVLINK_TYPE_UINT32_T, NULL},
  // main voltage. на столько надо умножить, чтобы получить uV
  {"ADC_MV_gain",     {.u32 = 0},          &gd_val[51],    {.u32 = 122400},     MAVLINK_TYPE_UINT32_T, NULL},
  {"ADC_reserved1",   {.u32 = 0},          &gd_val[52],    {.u32 = 122400},     MAVLINK_TYPE_UINT32_T, NULL},
  {"ADC_reserved2",   {.u32 = 0},          &gd_val[53],    {.u32 = 122400},     MAVLINK_TYPE_UINT32_T, NULL},

  /**** Bttery parameters ****/
  // battery capacity (mAh)
  {"BAT_cap",         {.u32 = 0},          &gd_val[54],    {.u32 = 11000},      MAVLINK_TYPE_UINT32_T, NULL},
  // battery filling in percents
  {"BAT_fill",        {.u32 = 0},          &gd_val[55],    {.u32 = 100},        MAVLINK_TYPE_UINT32_T, NULL},

  /**** Servos coefficients ****/
  {"SERVO_1_min",     {.u32 = SERVO_MIN},  &gd_val[56],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_1_max",     {.u32 = SERVO_MIN},  &gd_val[57],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_1_neutra",  {.u32 = SERVO_MIN},  &gd_val[58],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_2_min",     {.u32 = SERVO_MIN},  &gd_val[59],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_2_max",     {.u32 = SERVO_MIN},  &gd_val[60],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_2_neutra",  {.u32 = SERVO_MIN},  &gd_val[61],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_3_min",     {.u32 = SERVO_MIN},  &gd_val[62],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_3_max",     {.u32 = SERVO_MIN},  &gd_val[63],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_3_neutra",  {.u32 = SERVO_MIN},  &gd_val[64],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_4_min",     {.u32 = SERVO_MIN},  &gd_val[65],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_4_max",     {.u32 = SERVO_MIN},  &gd_val[66],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_4_neutra",  {.u32 = SERVO_MIN},  &gd_val[67],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_5_min",     {.u32 = SERVO_MIN},  &gd_val[68],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_5_max",     {.u32 = SERVO_MIN},  &gd_val[69],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_5_neutra",  {.u32 = SERVO_MIN},  &gd_val[70],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_6_min",     {.u32 = SERVO_MIN},  &gd_val[71],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_6_max",     {.u32 = SERVO_MIN},  &gd_val[72],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_6_neutra",  {.u32 = SERVO_MIN},  &gd_val[73],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_7_min",     {.u32 = SERVO_MIN},  &gd_val[74],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_7_max",     {.u32 = SERVO_MIN},  &gd_val[75],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_7_neutra",  {.u32 = SERVO_MIN},  &gd_val[76],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_8_min",     {.u32 = SERVO_MIN},  &gd_val[77],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_8_max",     {.u32 = SERVO_MIN},  &gd_val[78],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_8_neutra",  {.u32 = SERVO_MIN},  &gd_val[79],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  /* car specific settings */
  {"SERVO_car_max",   {.u32 = 1},          &gd_val[80],    {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T, NULL},
  {"SERVO_car_dz",    {.u32 = 1},          &gd_val[81],    {.u32 = 64},         MAVLINK_TYPE_UINT32_T, NULL},

  /* intervals between sending different data (mS) */
  {"T_raw_imu",       {.u32 = SEND_OFF},   &gd_val[82],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_raw_press",     {.u32 = SEND_OFF},   &gd_val[83],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_scal_imu",      {.u32 = SEND_OFF},   &gd_val[84],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_scal_press",    {.u32 = SEND_OFF},   &gd_val[85],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_attitude",      {.u32 = SEND_OFF},   &gd_val[86],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_vfr_hud",       {.u32 = SEND_OFF},   &gd_val[87],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_gps_int",       {.u32 = SEND_OFF},   &gd_val[88],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_sys_status",    {.u32 = SEND_OFF},   &gd_val[89],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_position_ned",  {.u32 = SEND_OFF},   &gd_val[90],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_nav_output",    {.u32 = SEND_OFF},   &gd_val[91],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_reserved2",     {.u32 = SEND_OFF},   &gd_val[92],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_reserved3",     {.u32 = SEND_OFF},   &gd_val[93],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_reserved4",     {.u32 = SEND_OFF},   &gd_val[94],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_reserved5",     {.u32 = SEND_OFF},   &gd_val[95],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},
  {"T_reserved6",     {.u32 = SEND_OFF},   &gd_val[96],    {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T, NULL},

  /* Timezone. Just simple offset in hours. */
  {"TIME_zone",       {.i32 = -24},        &gd_val[97],    {.i32 = 24},         MAVLINK_TYPE_INT32_T, NULL},

  /* Length of filters for different systems. */
  {"FLEN_adc",        {.u32 = 0},          &gd_val[98],    {.u32 = 30},         MAVLINK_TYPE_UINT32_T, NULL},
  {"FLEN_pres_dyn",   {.u32 = 0},          &gd_val[99],    {.u32 = 30},         MAVLINK_TYPE_UINT32_T, NULL},
  {"FLEN_pres_stat",  {.u32 = 0},          &gd_val[100],   {.u32 = 30},         MAVLINK_TYPE_UINT32_T, NULL},
  {"FLEN_climb",      {.u32 = 0},          &gd_val[101],   {.u32 = 30},         MAVLINK_TYPE_UINT32_T, NULL},
  {"FLEN_reserved1",  {.u32 = 0},          &gd_val[102],   {.u32 = 30},         MAVLINK_TYPE_UINT32_T, NULL},
  {"FLEN_reserved2",  {.u32 = 0},          &gd_val[103],   {.u32 = 30},         MAVLINK_TYPE_UINT32_T, NULL},
  {"FLEN_reserved3",  {.u32 = 0},          &gd_val[104],   {.u32 = 30},         MAVLINK_TYPE_UINT32_T, NULL},
  {"FLEN_reserved4",  {.u32 = 0},          &gd_val[105],   {.u32 = 30},         MAVLINK_TYPE_UINT32_T, NULL},

  /* multiply odometer pulses count to this coeff to get trip in m
   * coarse value is 0.05555555 */
  {"SPD_pulse2m",     {.f32 = 0.0},        &gd_val[106],   {.f32 = 1.0},        MAVLINK_TYPE_FLOAT, NULL},
  /**** pid coefficients for speed control ****/
  {"SPD_iGain",       {.f32 = -1.0},       &gd_val[107],   {.f32 = 1.0},        MAVLINK_TYPE_FLOAT, NULL},
  {"SPD_pGain",       {.f32 = -200.0},     &gd_val[108],   {.f32 = 200.0},      MAVLINK_TYPE_FLOAT, NULL},
  {"SPD_dGain",       {.f32 = -10000.0},   &gd_val[109],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},
  {"SPD_iMin",        {.f32 = -10000.0},   &gd_val[110],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},
  {"SPD_iMax",        {.f32 = -10000.0},   &gd_val[111],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},
  /**** pid coefficients for heading control ****/
  {"HEAD_iGain",      {.f32 = -1.0},       &gd_val[112],   {.f32 = 1.0},        MAVLINK_TYPE_FLOAT, NULL},
  {"HEAD_pGain",      {.f32 = -200.0},     &gd_val[113],   {.f32 = 200.0},      MAVLINK_TYPE_FLOAT, NULL},
  {"HEAD_dGain",      {.f32 = -10000.0},   &gd_val[114],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},
  {"HEAD_iMin",       {.f32 = -10000.0},   &gd_val[115],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},
  {"HEAD_iMax",       {.f32 = -10000.0},   &gd_val[116],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},
  /* device's speed limits */
  {"SPD_speed_min",   {.f32 = 0.0},        &gd_val[117],   {.f32 = 60.0},       MAVLINK_TYPE_FLOAT, NULL},
  {"SPD_speed_max",   {.f32 = 0.0},        &gd_val[118],   {.f32 = 60.0},       MAVLINK_TYPE_FLOAT, NULL},
  /**** pid coefficients for cross track correction ****/
  {"XTRACK_iGain",    {.f32 = -1.0},       &gd_val[119],   {.f32 = 1.0},        MAVLINK_TYPE_FLOAT, NULL},
  {"XTRACK_pGain",    {.f32 = -200.0},     &gd_val[120],   {.f32 = 200.0},      MAVLINK_TYPE_FLOAT, NULL},
  {"XTRACK_dGain",    {.f32 = -10000.0},   &gd_val[121],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},
  {"XTRACK_iMin",     {.f32 = -10000.0},   &gd_val[122],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},
  {"XTRACK_iMax",     {.f32 = -10000.0},   &gd_val[123],   {.f32 = 10000.0},    MAVLINK_TYPE_FLOAT, NULL},

  /**** fake field with 14 symbols name ****/
  {"param_end_mark",  {.u32 = 1},          &gd_val[124],   {.u32 = 1224},       MAVLINK_TYPE_UINT32_T, "Fake parameter with maximum name length"},
};


/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Float boundary checker.
 * Only write and emit changes if there is actually a difference
 */
static param_status_t _float_setval(void *value, const GlobalParam_t *param){
  float initial_value = *(float*)value;
  float v = initial_value;

  // AND only write if new value is NOT "not-a-number" AND is NOT infinity
  if (isnan(v) || isinf(v))
    return PARAM_INCONSISTENT;

  if (param->valuep->f32 == v)
    return PARAM_NOT_CHANGED;

  putinrange(v, param->min.f32, param->max.f32);
  param->valuep->f32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * Int32 boundary checker.
 * Only write and emit changes if there is actually a difference
 */
static param_status_t _int_setval(void *value, const GlobalParam_t *param){
  int32_t initial_value = *(int32_t*)value;
  int32_t v = initial_value;

  if (param->valuep->i32 == v)
    return PARAM_NOT_CHANGED;

  putinrange(v, param->min.i32, param->max.i32);
  param->valuep->i32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * Uint32 boundary checker.
 * Only write and emit changes if there is actually a difference
 */
static param_status_t _uint_setval(void *value, const GlobalParam_t *param){
  uint32_t initial_value = *(uint32_t*)value;
  uint32_t v = initial_value;

  if (param->valuep->u32 == v)
    return PARAM_NOT_CHANGED;

  putinrange(v, param->min.u32, param->max.u32);
  param->valuep->u32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * @brief   Sends mails to communication thread
 *
 * @param[in] key   if NULL than perform search by index
 * @param[in] n     search index
 */
static bool_t send_value(Mail *param_value_mail,
                         mavlink_param_value_t *param_value_struct,
                         char *key,
                         uint32_t n){
  int32_t index = -1;
  msg_t status = RDY_TIMEOUT;
  uint32_t j = 0;

  if (!(GlobalFlags & TLM_LINK_FLAG))
    return PARAM_FAILED;

  if (key != NULL)
    index = key_index_search(key);
  else
    index = n;
  if ((index >= 0) && (index <= OnboardParamCount)){
    status = chBSemWaitTimeout(param_value_mail->semp, PARAM_CONFIRM_TMO);
    if (status != RDY_OK){
      chBSemSignal(param_value_mail->semp);
      return PARAM_FAILED;
    }

    /* fill all fields */
    param_value_struct->param_value = global_data[index].valuep->f32;
    param_value_struct->param_type  = global_data[index].param_type;
    param_value_struct->param_count = OnboardParamCount;
    param_value_struct->param_index = index;
    for (j = 0; j < ONBOARD_PARAM_NAME_LENGTH; j++)
      param_value_struct->param_id[j] = global_data[index].name[j];

    /* send */
    param_value_mail->payload = param_value_struct;
    status = chMBPostAhead(&tolink_mb, (msg_t)param_value_mail, PARAM_POST_TMO);

    if (status != RDY_OK)
      return PARAM_FAILED;
  }
  else
    return PARAM_FAILED;

  return PARAM_SUCCESS;
}

/**
 * Send all values one by one.
 */
static void send_all_values(Mail *mail, mavlink_param_value_t *param_struct){
  int32_t i = 0;
  int32_t retry = 20;

  msg_t status = RDY_RESET;
  while ((i < OnboardParamCount) && (retry > 0)){
    status = send_value(mail, param_struct, NULL, i);
    if (status == PARAM_SUCCESS)
      i++;
    else
      retry--;
  }
}

/**
 * Receive messages with parameters and transmit parameters by requests.
 */
static WORKING_AREA(ParametersThreadWA, 256);
static msg_t ParametersThread(void *arg){
  chRegSetThreadName("Parameters");
  (void)arg;

  BinarySemaphore confirm_sem;        /* to sync with tlm sender */
  chBSemInit(&confirm_sem, FALSE);    /* semaphore is not taken */
  Mail param_value_mail = {NULL, MAVLINK_MSG_ID_PARAM_VALUE, &confirm_sem};

  msg_t tmp = 0;
  Mail *input_mail = NULL;
  mavlink_param_set_t *set = NULL;
  mavlink_param_request_list_t *list = NULL;
  mavlink_param_request_read_t *read = NULL;
  param_status_t status;

  while (TRUE) {
    chMBFetch(&mavlink_param_set_mb, &tmp, TIME_INFINITE);
    input_mail = (Mail*)tmp;

    switch (input_mail->invoice){
    /* The MAV has to acknowledge the write operation by emitting a
     * PARAM_VALUE value message with the newly written parameter value. */
    case MAVLINK_MSG_ID_PARAM_SET:
      set = (mavlink_param_set_t *)(input_mail->payload);
      input_mail->payload = NULL;

      status = set_global_param(&(set->param_value), &global_data[key_index_search(set->param_id)]);
      if ((status == PARAM_OK) || (status == PARAM_CLAMPED) || (status == PARAM_NOT_CHANGED))
        send_value(&param_value_mail, &mavlink_param_value_struct, set->param_id, 0);
      break;

    /*
     * request all
     */
    case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
      list = (mavlink_param_request_list_t *)(input_mail->payload);
      input_mail->payload = NULL;
      if (list->target_system == mavlink_system_struct.sysid)
        send_all_values(&param_value_mail, &mavlink_param_value_struct);
      break;

    /*
     * request single
     */
    case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
      read = (mavlink_param_request_read_t *)(input_mail->payload);
      input_mail->payload = NULL;
      if (read->param_index >= 0)
        send_value(&param_value_mail, &mavlink_param_value_struct, NULL, read->param_index);
      else
        send_value(&param_value_mail, &mavlink_param_value_struct, read->param_id, 0);
      break;
    }
  }
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * @brief   Performs key-value search. Low level function
 *
 * @return      Index in dictionary.
 * @retval -1   key not found.
 */
int32_t key_index_search(const char* key){
  int32_t i = 0;

  for (i = 0; i < OnboardParamCount; i++){
    if (strcmp(key, global_data[i].name) == 0)
      return i;
  }
  return -1;
}

/**
 * Return pointer to value.
 */
void *ValueSearch(const char *str){
  int32_t i = -1;

  i = key_index_search(str);
  if (i == -1){
    chDbgPanic("key not found");
    return NULL;
  }
  else
    return global_data[i].valuep;
}

/**
 * @brief   Global boundary checker.
 *
 * @param[in] value   input value that must be checked and saved in
 * @param[in] param   appropriate parameter in array
 *
 * @return            operation status.
 */
param_status_t set_global_param(void *value, const GlobalParam_t *param){

  switch(param->param_type){
  case MAVLINK_TYPE_FLOAT:
    return _float_setval(value, param);
    break;
  case MAVLINK_TYPE_UINT32_T:
    return _uint_setval(value, param);
    break;
  case MAVLINK_TYPE_INT32_T:
    return _int_setval(value, param);
    break;
  }
  return PARAM_WRONG_TYPE;
}

/**
 *
 */
void ParametersInit(void){

  int32_t i = 0;
  int32_t n = 0;
  int32_t gd_val_cnt = sizeof(gd_val) / sizeof(gd_val[0]);

  OnboardParamCount = (sizeof(global_data) / sizeof(GlobalParam_t));

  /* initialise variable array with zeroes to be safe */
  floatint v;
  v.u32 = 0;
  for (i = 0; i < gd_val_cnt; i++){
    gd_val[i] = v;
  }

  /* check hardcoded name lengths */
  for (i = 0; i < OnboardParamCount; i++){
    if (sizeof (*(global_data[i].name)) > ONBOARD_PARAM_NAME_LENGTH)
      chDbgPanic("name too long");
  }

  /* check available length of variable array */
  if (OnboardParamCount > gd_val_cnt)
    chDbgPanic("not enough space in RAM to store parameters");

  /* check uniqueness of pointers to variable parameters */
  for (i = 0; i < OnboardParamCount; i++){
    void *vp = global_data[i].valuep;
    for (n = i+1; n < OnboardParamCount; n++){
      if (vp == global_data[n].valuep)
        chDbgPanic("detected two pointers pointing to single parameter");
    }
  }

  /* check boundaries */
  bool_t got = FALSE;
  for (i = 0; i < OnboardParamCount; i++){
    void *vp = global_data[i].valuep;

    for (n = 0; n < gd_val_cnt; n++){
      if (vp == &gd_val[n])
        got = TRUE;
    }
    if (got == FALSE)
      chDbgPanic("probably pointer points out of arrya bounds");

    got = FALSE; /* go to next cycle */
  }

  /* check allowed size in EEPROM */
  uint32_t len = PARAM_ID_SIZE;
  len += sizeof(global_data[0].valuep);
  if (OnboardParamCount * len > EEPROM_SETTINGS_SIZE)
    chDbgPanic("not enough space in EEPROM settings slice");

  /* read data from eeprom to memory mapped structure */
  load_params_from_eeprom();

  chThdCreateStatic(ParametersThreadWA,
          sizeof(ParametersThreadWA),
          LINK_THREADS_PRIO + 1,
          ParametersThread,
          NULL);
}
