#include <math.h>
#include <string.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

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
extern Mailbox mavlink_param_set_mb;
extern Mailbox tolink_mb;
extern mavlink_system_t mavlink_system_struct;
extern mavlink_param_value_t mavlink_param_value_struct;

uint32_t OnboardParamCount = 0;

/**
 *
 */
GlobalParam_t global_data[] = {
  /*  key             min                  val                  max                  type                  */
  /*-------------------------------------------------------------------------------------------------------*/
  {"SYS_ID",          {.u32 = 1},          {.u32 = 20},         {.u32 = 255},        MAVLINK_TYPE_UINT32_T},
  /* тип автопилота (см. MAV_TYPE enum)
   * для возможности переключения между машиной и самолетом. Эти изменения
   * вступают в силу только после ребута. */
  {"SYS_mavtype",     {.u32 = 0},          {.u32 = 1},          {.u32 = 16},         MAVLINK_TYPE_UINT32_T},

  /**** всякие флаги для коммандной оболочки ****/
  {"SH_enable",       {.u32 = 0},          {.u32 = 0},          {.u32 = 1},          MAVLINK_TYPE_UINT32_T},

  /* IMU - inertial measurement unit */
  {"IMU_g1",          {.f32 = -1},         {.f32 = 0.1},        {.f32 = 1},          MAVLINK_TYPE_FLOAT},
  {"IMU_g2",          {.f32 = -1},         {.f32 = 0.2},        {.f32 = 1},          MAVLINK_TYPE_FLOAT},
  {"IMU_g3",          {.f32 = -1},         {.f32 = 0.3},        {.f32 = 1},          MAVLINK_TYPE_FLOAT},
  {"IMU_reserved",    {.u32 = 0},          {.u32 = 100},        {.u32 = 1000},       MAVLINK_TYPE_UINT32_T},

  /**** смещения нулей магнитометра ****/
  {"MAG_xoffset",     {.i32 = -5000},      {.i32 = 110},        {.i32 = 5000},       MAVLINK_TYPE_INT32_T},
  {"MAG_yoffset",     {.i32 = -5000},      {.i32 = -90},        {.i32 = 5000},       MAVLINK_TYPE_INT32_T},
  {"MAG_zoffset",     {.i32 = -5000},      {.i32 = 351},        {.i32 = 5000},       MAVLINK_TYPE_INT32_T},
  /**** чувствительность магнитометра ****/
  {"MAG_xsens",       {.f32 = 0.001},      {.f32 = 0.1},        {.f32 = 1.0},        MAVLINK_TYPE_FLOAT},
  {"MAG_ysens",       {.f32 = 0.001},      {.f32 = 0.1},        {.f32 = 1.0},        MAVLINK_TYPE_FLOAT},
  {"MAG_zsens",       {.f32 = 0.001},      {.f32 = 0.1},        {.f32 = 1.0},        MAVLINK_TYPE_FLOAT},
  /**** полярности осей. Направление осей приведено к осям автопилота ****/
  {"MAG_xpol",        {.i32 = -1},         {.i32 = 1},          {.i32 = 1},          MAVLINK_TYPE_INT32_T},
  {"MAG_ypol",        {.i32 = -1},         {.i32 = 1},          {.i32 = 1},          MAVLINK_TYPE_INT32_T},
  {"MAG_zpol",        {.i32 = -1},         {.i32 = 1},          {.i32 = 1},          MAVLINK_TYPE_INT32_T},
  /* магнитное склонение */
  {"MAG_inclinate",   {.i32 = -90},        {.i32 = 7},          {.i32 = 90},         MAVLINK_TYPE_INT32_T},

  /**** смещения нулей акселерометра ****/
  {"ACC_xoffset",     {.i32 = -100},       {.i32 = 2},          {.i32 = 100},        MAVLINK_TYPE_INT32_T},
  {"ACC_yoffset",     {.i32 = -100},       {.i32 = 0},          {.i32 = 100},        MAVLINK_TYPE_INT32_T},
  {"ACC_zoffset",     {.i32 = -100},       {.i32 = -3},         {.i32 = 100},        MAVLINK_TYPE_INT32_T},
  /**** чувствительность акселерометра LSB/g, номинальные: 4096, 8192, 16384 ****/
  {"ACC_xsens",       {.u32 = 3000},       {.u32 = 8192},       {.u32 = 17000},      MAVLINK_TYPE_UINT32_T},
  {"ACC_ysens",       {.u32 = 3000},       {.u32 = 8192},       {.u32 = 17000},      MAVLINK_TYPE_UINT32_T},
  {"ACC_zsens",       {.u32 = 3000},       {.u32 = 8192},       {.u32 = 17000},      MAVLINK_TYPE_UINT32_T},
  /**** полярности осей. Направление осей приведено к осям автопилота ****/
  {"ACC_xpol",        {.i32 = -1},         {.i32 = 1},          {.i32 = 1},          MAVLINK_TYPE_INT32_T},
  {"ACC_ypol",        {.i32 = -1},         {.i32 = 1},          {.i32 = 1},          MAVLINK_TYPE_INT32_T},
  {"ACC_zpol",        {.i32 = -1},         {.i32 = 1},          {.i32 = 1},          MAVLINK_TYPE_INT32_T},

  /**** чувствительности осей гироскопа (LSB/(deg/s)). Направление осей приведено к осям автопилота ****/
  {"GYRO_xsens",      {.f32 = 7.0},        {.f32 = 14.375},     {.f32 = 30.0},       MAVLINK_TYPE_FLOAT},
  {"GYRO_ysens",      {.f32 = 7.0},        {.f32 = 14.375},     {.f32 = 30.0},       MAVLINK_TYPE_FLOAT},
  {"GYRO_zsens",      {.f32 = 7.0},        {.f32 = 14.375},     {.f32 = 30.0},       MAVLINK_TYPE_FLOAT},
  /**** полярности вращения осей. Направление осей приведено к осям автопилота ****/
  {"GYRO_xpol",       {.i32 = -1},         {.i32 = -1},         {.i32 = 1},          MAVLINK_TYPE_INT32_T},
  {"GYRO_ypol",       {.i32 = -1},         {.i32 = 1},          {.i32 = 1},          MAVLINK_TYPE_INT32_T},
  {"GYRO_zpol",       {.i32 = -1},         {.i32 = 1},          {.i32 = 1},          MAVLINK_TYPE_INT32_T},

  /**** PMU - pressure measurement unit ****/
  // coefficients for thermal compensation
  {"PMU_c1",          {.i32 = -2000000},   {.i32 = -9},         {.i32 = 2000000},    MAVLINK_TYPE_INT32_T},
  {"PMU_c2",          {.i32 = -2000000},   {.i32 = 408},        {.i32 = 2000000},    MAVLINK_TYPE_INT32_T},
  {"PMU_c3",          {.i32 = -2000000},   {.i32 = 7587},       {.i32 = 2000000},    MAVLINK_TYPE_INT32_T},
  {"PMU_c4",          {.i32 = -2000000},   {.i32 = 60011},      {.i32 = 2000000},    MAVLINK_TYPE_INT32_T},
  {"PMU_reserved",    {.i32 = -2000000},   {.i32 = 100},        {.i32 = 2000000},    MAVLINK_TYPE_INT32_T},

  /**** ADC coefficients ****/
  // смещение нуля датчика тока в условных единицах АЦП
  {"ADC_I_offset",    {.u32 = 0},          {.u32 = 16},         {.u32 = 4096},       MAVLINK_TYPE_UINT32_T},
  // на столько надо поделить, чтобы получить амперы. Для машинки 1912, для самолета 37
  {"ADC_I_gain",      {.u32 = 0},          {.u32 = 1912},       {.u32 = 12240},      MAVLINK_TYPE_UINT32_T},
  // secondary voltage. на столько надо умножить, чтобы получить uV
  {"ADC_SV_gain",     {.u32 = 0},          {.u32 = 8052},       {.u32 = 122400},     MAVLINK_TYPE_UINT32_T},
  // main voltage. на столько надо умножить, чтобы получить uV
  {"ADC_MV_gain",     {.u32 = 0},          {.u32 = 8050},       {.u32 = 122400},     MAVLINK_TYPE_UINT32_T},

  /**** Bttery parameters ****/
  // battery capacity (mAh)
  {"BAT_cap",         {.u32 = 0},          {.u32 = 2200},       {.u32 = 11000},      MAVLINK_TYPE_UINT32_T},
  // battery filling in percents
  {"BAT_fill",        {.u32 = 0},          {.u32 = 98},         {.u32 = 100},        MAVLINK_TYPE_UINT32_T},

  /**** Servos coefficients ****/
  {"SERVO_1_min",     {.u32 = SERVO_MIN},  {.u32 = 1000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_1_max",     {.u32 = SERVO_MIN},  {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_1_neutra",  {.u32 = SERVO_MIN},  {.u32 = 1500},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_2_min",     {.u32 = SERVO_MIN},  {.u32 = 1000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_2_max",     {.u32 = SERVO_MIN},  {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_2_neutra",  {.u32 = SERVO_MIN},  {.u32 = 1500},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_3_min",     {.u32 = SERVO_MIN},  {.u32 = 1000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_3_max",     {.u32 = SERVO_MIN},  {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_3_neutra",  {.u32 = SERVO_MIN},  {.u32 = 1500},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_4_min",     {.u32 = SERVO_MIN},  {.u32 = 1000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_4_max",     {.u32 = SERVO_MIN},  {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_4_neutra",  {.u32 = SERVO_MIN},  {.u32 = 1500},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_5_min",     {.u32 = SERVO_MIN},  {.u32 = 1000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_5_max",     {.u32 = SERVO_MIN},  {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_5_neutra",  {.u32 = SERVO_MIN},  {.u32 = 1500},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_6_min",     {.u32 = SERVO_MIN},  {.u32 = 1000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_6_max",     {.u32 = SERVO_MIN},  {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_6_neutra",  {.u32 = SERVO_MIN},  {.u32 = 1500},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_7_min",     {.u32 = SERVO_MIN},  {.u32 = 1000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_7_max",     {.u32 = SERVO_MIN},  {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_7_neutra",  {.u32 = SERVO_MIN},  {.u32 = 1500},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_8_min",     {.u32 = SERVO_MIN},  {.u32 = 1000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_8_max",     {.u32 = SERVO_MIN},  {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_8_neutra",  {.u32 = SERVO_MIN},  {.u32 = 1500},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  /* car specific settings */
  {"SERVO_car_max",   {.u32 = 1},          {.u32 = 2000},       {.u32 = SERVO_MAX},  MAVLINK_TYPE_UINT32_T},
  {"SERVO_car_dz",    {.u32 = 1},          {.u32 = 32},         {.u32 = 64},         MAVLINK_TYPE_UINT32_T},

  /*  */
  {"IMU_accweight",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.1},        MAVLINK_TYPE_FLOAT},
  {"IMU_magweight",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.9},        MAVLINK_TYPE_FLOAT},
  {"IMU_gpsweight",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.1},        MAVLINK_TYPE_FLOAT},
  {"IMU_reserved1",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.1},        MAVLINK_TYPE_FLOAT},
  {"IMU_reserved2",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.1},        MAVLINK_TYPE_FLOAT},
  {"IMU_reserved3",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.1},        MAVLINK_TYPE_FLOAT},
  {"IMU_reserved4",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.1},        MAVLINK_TYPE_FLOAT},
  {"IMU_reserved5",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.1},        MAVLINK_TYPE_FLOAT},
  {"IMU_reserved6",   {.f32 = 0.0},        {.f32 = 0.01},       {.f32 = 0.1},        MAVLINK_TYPE_FLOAT},

  /* sample count for zeroing */
  {"GYRO_zeroconut",  {.u32 = 256},        {.u32 = 2048},       {.u32 = 16384},      MAVLINK_TYPE_UINT32_T},

  /* intervals between sending different data (mS) */
  {"T_raw_imu",       {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_raw_press",     {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_scal_imu",      {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_scal_press",    {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_attitude",      {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_vfr_hud",       {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_gps_int",       {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_sys_status",    {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_reserved0",     {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_reserved1",     {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_reserved2",     {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_reserved3",     {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_reserved4",     {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_reserved5",     {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},
  {"T_reserved6",     {.u32 = SEND_OFF},   {.u32 = 100},        {.u32 = SEND_MAX},   MAVLINK_TYPE_UINT32_T},

  /* Timezone. Just simple offset in hours. */
  {"TIME_zone",       {.i32 = -24},        {.i32 = 3},          {.i32 = 24},         MAVLINK_TYPE_INT32_T},

  /* Length of filters for different systems. */
  {"FLEN_adc",        {.u32 = 0},          {.u32 = 4},          {.u32 = 30},         MAVLINK_TYPE_UINT32_T},
  {"FLEN_pres_dyn",   {.u32 = 0},          {.u32 = 4},          {.u32 = 30},         MAVLINK_TYPE_UINT32_T},
  {"FLEN_pres_stat",  {.u32 = 0},          {.u32 = 4},          {.u32 = 30},         MAVLINK_TYPE_UINT32_T},
  {"FLEN_reserved0",  {.u32 = 0},          {.u32 = 4},          {.u32 = 30},         MAVLINK_TYPE_UINT32_T},
  {"FLEN_reserved1",  {.u32 = 0},          {.u32 = 4},          {.u32 = 30},         MAVLINK_TYPE_UINT32_T},
  {"FLEN_reserved2",  {.u32 = 0},          {.u32 = 4},          {.u32 = 30},         MAVLINK_TYPE_UINT32_T},
  {"FLEN_reserved3",  {.u32 = 0},          {.u32 = 4},          {.u32 = 30},         MAVLINK_TYPE_UINT32_T},
  {"FLEN_reserved4",  {.u32 = 0},          {.u32 = 4},          {.u32 = 30},         MAVLINK_TYPE_UINT32_T},

  /* fake field with 14 symbols name */
  {"param_end_mark",  {.u32 = 1},          {.u32 = 1048},       {.u32 = 1224},       MAVLINK_TYPE_UINT32_T},
};

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static BinarySemaphore param_confirm_sem;     /* to sync with tlm sender */

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
static param_status_t _float_setval(void *value,  GlobalParam_t *param){
  float initial_value = *(float*)value;
  float v = initial_value;

  // AND only write if new value is NOT "not-a-number" AND is NOT infinity
  if (isnan(v) || isinf(v))
    return PARAM_INCONSISTENT;

  if (param->value.f32 == v)
    return PARAM_NOT_CHANGED;

  putinrange(v, param->min.f32, param->max.f32);
  param->value.f32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * Int32 boundary checker.
 * Only write and emit changes if there is actually a difference
 */
static param_status_t _int_setval(void *value,  GlobalParam_t *param){
  int32_t initial_value = *(int32_t*)value;
  int32_t v = initial_value;

  if (param->value.i32 == v)
    return PARAM_NOT_CHANGED;

  putinrange(v, param->min.i32, param->max.i32);
  param->value.i32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * Uint32 boundary checker.
 * Only write and emit changes if there is actually a difference
 */
static param_status_t _uint_setval(void *value,  GlobalParam_t *param){
  uint32_t initial_value = *(uint32_t*)value;
  uint32_t v = initial_value;

  if (param->value.u32 == v)
    return PARAM_NOT_CHANGED;

  putinrange(v, param->min.u32, param->max.u32);
  param->value.u32 = v;

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

  if (key != NULL)
    index = key_index_search(key);
  else
    index = n;

  if ((index >= 0) && (index <= (int)OnboardParamCount)){
    /* fill all fields */
    param_value_struct->param_value = global_data[index].value.f32;
    param_value_struct->param_type  = global_data[index].param_type;
    param_value_struct->param_count = OnboardParamCount;
    param_value_struct->param_index = index;
    for (j = 0; j < ONBOARD_PARAM_NAME_LENGTH; j++)
      param_value_struct->param_id[j] = global_data[index].name[j];

    /* send */
    param_value_mail->payload = param_value_struct;
    //status = chMBPostAhead(&tolink_mb, (msg_t)param_value_mail, MS2ST(5));
    status = chMBPost(&tolink_mb, (msg_t)param_value_mail, MS2ST(5));
    if (status != RDY_OK)
      return PARAM_FAILED;

    /* wait until message processed */
    chBSemWaitTimeout(&param_confirm_sem, TIME_INFINITE);
  }
  else
    return PARAM_FAILED;

  return PARAM_SUCCESS;
}

/**
 * Send all values one by one.
 */
static void send_all_values(Mail *mail, mavlink_param_value_t *param_struct){
  uint32_t i = 0;
  for (i = 0; i < OnboardParamCount; i++){
    send_value(mail, param_struct, NULL, i);
  }
}

/**
 * Receive messages with parameters and transmit parameters by requests.
 */
static WORKING_AREA(ParametersThreadWA, 512);
static msg_t ParametersThread(void *arg){
  chRegSetThreadName("Parameters");
  (void)arg;

  Mail param_value_mail = {NULL, MAVLINK_MSG_ID_PARAM_VALUE, &param_confirm_sem};

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
      if ((status == PARAM_OK) && (status == PARAM_CLAMPED))
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

  for (i = 0; i < (int)OnboardParamCount; i++){
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
    return &(global_data[i].value);
}

/**
 * @brief   Global boundary checker.
 *
 * @param[in] value   input value that must be checked and saved in
 * @param[in] param   appropriate parameter in array
 *
 * @return            operation status.
 */
param_status_t set_global_param(void *value,  GlobalParam_t *param){

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

  OnboardParamCount = (sizeof(global_data) / sizeof(GlobalParam_t));

  chBSemInit(&param_confirm_sem, FALSE); /* semaphore is not taken */

  /* check hardcoded values */
  uint32_t i = 0;
  for (i = 0; i < OnboardParamCount; i++){
    if (sizeof (*(global_data[i].name)) > ONBOARD_PARAM_NAME_LENGTH)
      chDbgPanic("name too long");
  }

  /* check allowed size in EEPROM */
  uint32_t len = PARAM_ID_SIZE;
  len += sizeof(global_data[0].value);
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
