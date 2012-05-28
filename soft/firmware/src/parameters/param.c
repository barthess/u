#include <math.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "param.h"
#include "persistant.h"
#include "main.h"
#include "imu.h"
#include "servo.h"
#include "eeprom.h"
#include "link.h"
#include "utils.h"

/*
 ******************************************************************************
 * DEFINES
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

/**
 * Default boundary checker.
 */
static bool_t default_setval(float value,  GlobalParam_t *param){
  float initial_value = value;

  putinrange(value, param->min, param->max);
  param->value = value;

  if (value == initial_value)
    return PARAM_SUCCESS;
  else
    return PARAM_FAILED;
}

/**
 * Default boundary checker for integer values.
 */
static bool_t int_setval(float value,  GlobalParam_t *param){
  float initial_value = value;

  putinrange(value, param->min, param->max);
  param->value = roundf(value);

  if (value == initial_value)
    return PARAM_SUCCESS;
  else
    return PARAM_FAILED;
}

/**
 * Cheker for inversion coefficients used (for example) in gyros
 * to invert direction values.
 */
bool_t polarity_setval(float value,  GlobalParam_t *param){
  if ((value > -1.1) && (value < -0.9)){
    param->value = -1;
    return PARAM_SUCCESS;
  }
  else{
    param->value = 1;
    return PARAM_FAILED;
  }
}


GlobalParam_t global_data[] = {
  /*  key             min         val         max         type                    checker_fucntion   */
  /*--------------------------------------------------------------------------------------------------*/
  {"SYS_ID",          1,          20,         255,        MAVLINK_TYPE_UINT32_T,  default_setval},
  /* тип автопилота (см. MAV_TYPE enum)
   * для возможности переключения между машиной и самолетом. Изменения
   * вступают в силу только после ребута. */
  {"SYS_mavtype",     0,          1,          16,         MAVLINK_TYPE_UINT32_T,  default_setval},

  /**** всякие флаги для коммандной оболочки ****/
  {"SH_enable",       0,          0,          1,          MAVLINK_TYPE_UINT32_T,  default_setval},

  /* IMU - inertial measurement unit */
  {"IMU_g1",          -1,         0.1,        1,          MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_g2",          -1,         0.2,        1,          MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_g3",          -1,         0.3,        1,          MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_send_ms",     SEND_MIN,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  default_setval},

  /**** смещения нулей магнитометра ****/
  {"MAG_xoffset",     -5000,      110,        5000,       MAVLINK_TYPE_INT32_T,   default_setval},
  {"MAG_yoffset",     -5000,      -90,        5000,       MAVLINK_TYPE_INT32_T,   default_setval},
  {"MAG_zoffset",     -5000,      351,        5000,       MAVLINK_TYPE_INT32_T,   default_setval},
  /**** чувствительность магнитометра ****/
  {"MAG_xsens",       0.001,      0.1,        1.0,       MAVLINK_TYPE_FLOAT,     default_setval},
  {"MAG_ysens",       0.001,      0.1,        1.0,       MAVLINK_TYPE_FLOAT,     default_setval},
  {"MAG_zsens",       0.001,      0.1,        1.0,       MAVLINK_TYPE_FLOAT,     default_setval},
  /**** полярности осей. Направление осей приведено к осям автопилота ****/
  {"MAG_xpol",        -1,         1,          1,          MAVLINK_TYPE_INT32_T,   polarity_setval},
  {"MAG_ypol",        -1,         1,          1,          MAVLINK_TYPE_INT32_T,   polarity_setval},
  {"MAG_zpol",        -1,         1,          1,          MAVLINK_TYPE_INT32_T,   polarity_setval},
  /* магнитное склонение */
  {"MAG_inclinate",   -90,        7,          90,         MAVLINK_TYPE_INT32_T,   default_setval},

  /**** смещения нулей акселерометра ****/
  {"ACC_xoffset",     -100,       2,          100,        MAVLINK_TYPE_INT32_T,   default_setval},
  {"ACC_yoffset",     -100,       0,          100,        MAVLINK_TYPE_INT32_T,   default_setval},
  {"ACC_zoffset",     -100,       -3,         100,        MAVLINK_TYPE_INT32_T,   default_setval},
  /**** чувствительность акселерометра LSB/g, номинальные: 4096, 8192, 16384 ****/
  {"ACC_xsens",       3000,       8192,       17000,      MAVLINK_TYPE_FLOAT,     default_setval},
  {"ACC_ysens",       3000,       8192,       17000,      MAVLINK_TYPE_FLOAT,     default_setval},
  {"ACC_zsens",       3000,       8192,       17000,      MAVLINK_TYPE_FLOAT,     default_setval},
  /**** полярности осей. Направление осей приведено к осям автопилота ****/
  {"ACC_xpol",        -1,         1,          1,          MAVLINK_TYPE_INT32_T,   polarity_setval},
  {"ACC_ypol",        -1,         1,          1,          MAVLINK_TYPE_INT32_T,   polarity_setval},
  {"ACC_zpol",        -1,         1,          1,          MAVLINK_TYPE_INT32_T,   polarity_setval},

  /**** чувствительности осей гироскопа (LSB/(deg/s)). Направление осей приведено к осям автопилота ****/
  {"GYRO_xsens",      7.0,        14.375,     30.0,       MAVLINK_TYPE_FLOAT,     default_setval},
  {"GYRO_ysens",      7.0,        14.375,     30.0,       MAVLINK_TYPE_FLOAT,     default_setval},
  {"GYRO_zsens",      7.0,        14.375,     30.0,       MAVLINK_TYPE_FLOAT,     default_setval},
  /**** полярности вращения осей. Направление осей приведено к осям автопилота ****/
  {"GYRO_xpol",       -1,         -1,         1,          MAVLINK_TYPE_INT32_T,   polarity_setval},
  {"GYRO_ypol",       -1,         1,          1,          MAVLINK_TYPE_INT32_T,   polarity_setval},
  {"GYRO_zpol",       -1,         1,          1,          MAVLINK_TYPE_INT32_T,   polarity_setval},

  /**** PMU - pressure measurement unit ****/
  //Коэффициенты полинома для термокомпенсации нуля
  {"PMU_c1",          -2000000,   -9,         2000000,    MAVLINK_TYPE_INT32_T,   default_setval},
  {"PMU_c2",          -2000000,   408,        2000000,    MAVLINK_TYPE_INT32_T,   default_setval},
  {"PMU_c3",          -2000000,   7587,       2000000,    MAVLINK_TYPE_INT32_T,   default_setval},
  {"PMU_c4",          -2000000,   60011,      2000000,    MAVLINK_TYPE_INT32_T,   default_setval},
  {"PMU_send_ms",     SEND_MIN,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  default_setval},

  /**** ADC coefficients ****/
  // смещение нуля датчика тока
  {"ADC_I_offset",    0,          16,         4096,       MAVLINK_TYPE_UINT32_T,  default_setval},
  // на столько надо поделить, чтобы получить амперы. Для машинки 1912, для самолета 37
  {"ADC_I_gain",      0,          1912,       12240,      MAVLINK_TYPE_UINT32_T,  default_setval},
  // secondary voltage. на столько надо умножить, чтобы получить nV
  {"ADC_SV_gain",     0,          8052,       12240,      MAVLINK_TYPE_UINT32_T,  default_setval},
  // main voltage. на столько надо умножить, чтобы получить nV
  {"ADC_MV_gain",     0,          8050,       12240,      MAVLINK_TYPE_UINT32_T,  default_setval},

  /**** Bttery parameters ****/
  // емкость батареи в mAh
  {"BAT_cap",         0,          2200,       11000,      MAVLINK_TYPE_UINT32_T,  default_setval},
  // на столько процентов заряжена перед установкой в самолет
  {"BAT_fill",        0,          98,         100,        MAVLINK_TYPE_UINT32_T,  default_setval},

  /**** Servos coefficients ****/
  {"SERVO_1_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_1_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_1_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_2_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_2_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_2_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_3_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_3_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_3_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_4_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_4_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_4_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_5_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_5_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_5_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_6_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_6_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_6_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_7_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_7_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_7_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_8_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_8_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_8_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  /* машинко-специфичные настройки */
  {"SERVO_car_max",   1,          2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T,  default_setval},
  {"SERVO_car_dz",    1,          32,         64,         MAVLINK_TYPE_UINT32_T,  default_setval},

  /* настройки инерциалки */
  {"IMU_accweight",   0.0,        0.01,       0.1,        MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_magweight",   0.0,        0.01,       0.9,        MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_gpsweight",   0.0,        0.01,       0.1,        MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_reserved1",   0.0,        0.01,       0.1,        MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_reserved2",   0.0,        0.01,       0.1,        MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_reserved3",   0.0,        0.01,       0.1,        MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_reserved4",   0.0,        0.01,       0.1,        MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_reserved5",   0.0,        0.01,       0.1,        MAVLINK_TYPE_FLOAT,     default_setval},
  {"IMU_reserved6",   0.0,        0.01,       0.1,        MAVLINK_TYPE_FLOAT,     default_setval},

  /* sample count for zeroing */
  {"GYRO_zeroconut",  256,        2048,       16384,      MAVLINK_TYPE_UINT32_T,  default_setval},

  /* время между посылками данных определенного типа в mS
   * 60001 - означает отключение посылок данного типа */
  {"T_raw_imu",       SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_raw_press",     SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_scal_imu",      SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_scal_press",    SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_attitude",      SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_vfr_hud",       SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_gps_int",       SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_sys_status",    SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_heartbeat",     SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_reserved1",     SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_reserved2",     SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_reserved3",     SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_reserved4",     SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_reserved5",     SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},
  {"T_reserved6",     SEND_OFF,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T,  int_setval},

  /* fake field with 14 symbols name */
  {"fake_14_bytes_",  1,          1048,       1224,       MAVLINK_TYPE_UINT32_T,  default_setval},
};

const uint32_t ONBOARD_PARAM_COUNT = (sizeof(global_data) / sizeof(GlobalParam_t));

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static Mailbox param_confirm_mb;
static msg_t param_confirm_mb_buf[1];


/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Checks parameter and writes it to global struct.
 */
static bool_t set_parameter(mavlink_param_set_t *paramset){
  int32_t index = -1;

  index = _key_index_search(paramset->param_id);

  if (index >= 0){
    // Only write and emit changes if there is actually a difference
    // AND only write if new value is NOT "not-a-number"
    // AND is NOT infinity
    if ((paramset->param_type == MAVLINK_TYPE_FLOAT) &&
        (isnan(paramset->param_value) || isinf(paramset->param_value))){
      return PARAM_FAILED;
    }
    if (global_data[index].value == paramset->param_value){
      return PARAM_FAILED;
    }

    /* If value fall out of min..max bound than just set nearest allowable value */
    return global_data[index].setval(paramset->param_value, &global_data[index]);
  }

  /* default returning value */
  return PARAM_FAILED;
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
  msg_t tmp = 0;
  uint32_t j = 0;

  if (key != NULL)
    index = _key_index_search(key);
  else
    index = n;

  if ((index >= 0) && (index <= ONBOARD_PARAM_COUNT)){
    /* fill all fields */
    param_value_struct->param_value = global_data[index].value;
    param_value_struct->param_count = ONBOARD_PARAM_COUNT;
    param_value_struct->param_index = index;
    param_value_struct->param_type  = MAVLINK_TYPE_FLOAT;
    for (j = 0; j < ONBOARD_PARAM_NAME_LENGTH; j++)
      param_value_struct->param_id[j] = global_data[index].name[j];

    /* send */
    param_value_mail->payload = param_value_struct;
    //status = chMBPostAhead(&tolink_mb, (msg_t)param_value_mail, MS2ST(5));
    status = chMBPost(&tolink_mb, (msg_t)param_value_mail, MS2ST(5));
    if (status != RDY_OK)
      return PARAM_FAILED;

    /* wait until message processed */
    chMBFetch(&param_confirm_mb, &tmp, TIME_INFINITE);
  }
  else
    return PARAM_FAILED;

  return SUCCESS;
}

/**
 * Send all values one by one.
 */
static void send_all_values(Mail *mail, mavlink_param_value_t *param_struct){
  uint32_t i = 0;
  for (i = 0; i < ONBOARD_PARAM_COUNT; i++){
    send_value(mail, param_struct, NULL, i);
  }
}

/**
 * Поток принимающий сообщения с параметрами и отправляющий параметры по запросу.
 */
static WORKING_AREA(ParametersThreadWA, 512);
static msg_t ParametersThread(void *arg){
  chRegSetThreadName("Parameters");
  (void)arg;

  /* переменные для отправки установленных параметров */
  mavlink_param_value_t param_value_struct;
  Mail param_value_mail = {NULL, MAVLINK_MSG_ID_PARAM_VALUE, &param_confirm_mb};

  /* переменные для приема параметров */
  msg_t tmp = 0;
  Mail *input_mail = NULL;
  mavlink_param_set_t *set = NULL;
  mavlink_param_request_list_t *list = NULL;
  mavlink_param_request_read_t *read = NULL;
  bool_t status = PARAM_FAILED;

  while (TRUE) {
    chMBFetch(&mavlink_param_set_mb, &tmp, TIME_INFINITE);
    input_mail = (Mail*)tmp;

    switch (input_mail->invoice){
    /*
     * согласно протоколу, при успешной установке параметра, мы должны
     * вычитать и выслать в ответ этот параметр в качестве подтверждения
     */
    case MAVLINK_MSG_ID_PARAM_SET:
      set = (mavlink_param_set_t *)(input_mail->payload);
      input_mail->payload = NULL;
      status = set_parameter(set);
      if (status == SUCCESS){
        send_value(&param_value_mail, &param_value_struct, set->param_id, 0);
      }
      break;

    /*
     * запрос всех параметров
     */
    case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
      list = (mavlink_param_request_list_t *)(input_mail->payload);
      input_mail->payload = NULL;
      if (list->target_system == mavlink_system_struct.sysid)
        send_all_values(&param_value_mail, &param_value_struct);
      break;

    /*
     * запрос одного параметра
     */
    case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
      read = (mavlink_param_request_read_t *)(input_mail->payload);
      input_mail->payload = NULL;
      if (read->param_index >= 0)
        send_value(&param_value_mail, &param_value_struct, NULL, read->param_index);
      else
        send_value(&param_value_mail, &param_value_struct, read->param_id, 0);
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
int32_t _key_index_search(char* key){
  int32_t i = 0;

  for (i = 0; i < ONBOARD_PARAM_COUNT; i++){
    if (strcmp(key, global_data[i].name) == 0)
      return i;
  }
  return -1;
}

/**
 * Возвращает указатель прямо на значение.
 *
 * Данный функционал вынесен в отдельную функцию на тот случай, если
 * приложению понадобится знать другие поля структуры
 */
float *ValueSearch(char *str){
  int32_t i = -1;

  i = _key_index_search(str);
  if (i == -1){
    chDbgPanic("key not found");
    return NULL;
  }
  else
    return &(global_data[i].value);
}



void ParametersInit(void){

  chMBInit(&param_confirm_mb, param_confirm_mb_buf, (sizeof(param_confirm_mb_buf)/sizeof(msg_t)));

  /* check hardcoded values */
  uint32_t i = 0;
  for (i = 0; i < ONBOARD_PARAM_COUNT; i++){
    if (sizeof (*(global_data[i].name)) > ONBOARD_PARAM_NAME_LENGTH)
      chDbgPanic("name too long");
    if ((global_data[i].value < global_data[i].min) ||
        (global_data[i].value > global_data[i].max))
      chDbgPanic("value out of bounds");
  }

  /* check allowed size in EEPROM */
  uint32_t len = PARAM_ID_SIZE;
  len += sizeof(global_data[0].value);
  if (ONBOARD_PARAM_COUNT * len > EEPROM_SETTINGS_SIZE)
    chDbgPanic("not enough space in EEPROM settings slice");

  /* read data from eeprom to memory mapped structure */
  load_params_from_eeprom();

  chThdCreateStatic(ParametersThreadWA,
          sizeof(ParametersThreadWA),
          LINK_THREADS_PRIO + 1,
          ParametersThread,
          NULL);
}

