#include <math.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "param.h"
#include "param_persistant.h"
#include "main.h"
#include "imu.h"
#include "servo.h"
#include "eeprom.h"
#include "link.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/* периодичность посылки данных в милисекундах */
#define SEND_MIN                  25
#define SEND_MAX                  10000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox param_mb;
extern Mailbox tolink_mb;
extern mavlink_system_t mavlink_system;

GlobalParam_t global_data[] = {
    /*  key             min         val         max         type                       */
    /*-----------------------------------------------------------------------*/
    {"SYS_ID",          1,          20,         255,        MAVLINK_TYPE_UINT32_T},
    {"SYS_send_ms",     SEND_MIN,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T},
    /* вс€кие флаги дл€ коммандной оболочки */
    {"SH_enable",       0,          0,          1,          MAVLINK_TYPE_UINT32_T},
    /* IMU - inertial measurement unit */
    {"IMU_g1",          -1,         0.1,        1,          MAVLINK_TYPE_FLOAT},
    {"IMU_g2",          -1,         0.2,        1,          MAVLINK_TYPE_FLOAT},
    {"IMU_g3",          -1,         0.3,        1,          MAVLINK_TYPE_FLOAT},
    {"IMU_send_ms",     SEND_MIN,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T},
    /* смещени€ нулей магнитометра */
    {"MAG_xoffset",     -5000,      110,        5000,       MAVLINK_TYPE_INT32_T},
    {"MAG_yoffset",     -5000,      -90,        5000,       MAVLINK_TYPE_INT32_T},
    {"MAG_zoffset",     -5000,      351,        5000,       MAVLINK_TYPE_INT32_T},
    /* смещени€ нулей акселерометра */
    {"ACC_xoffset",     -100,       2,          100,        MAVLINK_TYPE_INT32_T},
    {"ACC_yoffset",     -100,       0,          100,        MAVLINK_TYPE_INT32_T},
    {"ACC_zoffset",     -100,       -3,         100,        MAVLINK_TYPE_INT32_T},
    /* смещени€ нулей гироскопа */
    {"GYRO_xoffset",    -200,       2,          200,        MAVLINK_TYPE_INT32_T},
    {"GYRO_yoffset",    -200,       0,          200,        MAVLINK_TYPE_INT32_T},
    {"GYRO_zoffset",    -200,       -3,         200,        MAVLINK_TYPE_INT32_T},
    /* PMU - pressure measurement unit
     *  оэффициенты полинома дл€ термокомпенсации нул€ ((c1*t) + c2) */
    {"PMU_c1",          -2000000,   -9,         2000000,    MAVLINK_TYPE_INT32_T},
    {"PMU_c2",          -2000000,   408,        2000000,    MAVLINK_TYPE_INT32_T},
    {"PMU_c3",          -2000000,   7587,       2000000,    MAVLINK_TYPE_INT32_T},
    {"PMU_c4",          -2000000,   60011,      2000000,    MAVLINK_TYPE_INT32_T},
    {"PMU_send_ms",     SEND_MIN,   100,        SEND_MAX,   MAVLINK_TYPE_UINT32_T},
    /* ADC coefficients */
    {"ADC_I_offset",    0,          1048,       1224,       MAVLINK_TYPE_UINT32_T},  /* смещение нул€ датчика тока */
    {"ADC_I_gain",      0,          1048,       1224,       MAVLINK_TYPE_UINT32_T},  /* на столько надо умножить, чтобы получить милливольты */
    /* Bttery parameters */
    {"BAT_cap",         0,          2200,       11000,      MAVLINK_TYPE_UINT32_T},  /* емкость батареи в mAh */
    {"BAT_fill",        0,          98,         100,        MAVLINK_TYPE_UINT32_T},  /* на столько процентов зар€жена перед установкой в самолет */
    /* Servos coefficients */
    {"SERVO_1_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_1_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_1_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_2_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_2_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_2_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_3_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_3_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_3_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_4_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_4_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_4_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_5_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_5_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_5_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_6_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_6_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_6_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_7_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_7_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_7_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_8_min",     SERVO_MIN,  1000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_8_max",     SERVO_MIN,  2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_8_neutra",  SERVO_MIN,  1500,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    /* машинко-специфичные настройки */
    {"SERVO_car_max",   0,          2000,       SERVO_MAX,  MAVLINK_TYPE_UINT32_T},
    {"SERVO_car_dz",    0,          32,         64,         MAVLINK_TYPE_UINT32_T},

    /* fake field with 14 symbols name */
    {"fake_14_bytes_",  0,          1048,       1224,       MAVLINK_TYPE_FLOAT},
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
 * @brief   Performs key-value search.
 *
 * @return      Index in dictionary.
 * @retval -1   key not found.
 */
int32_t key_value_search(char* key){
  uint32_t i = 0;

  for (i = 0; i < ONBOARD_PARAM_COUNT; i++){
    if (strcmp(key, global_data[i].name) == 0)
      return i;
  }
  return -1;
}

/**
 * Checks parameter and writes it to global struct.
 */
static bool_t set_parameter(mavlink_param_set_t *set){
  int32_t index = -1;

  index = key_value_search(set->param_id);

  if (index >= 0){
    // Only write and emit changes if there is actually a difference
    // AND only write if new value is NOT "not-a-number"
    // AND is NOT infinity
    if ((set->param_type == MAVLINK_TYPE_FLOAT) &&
        (isnan(set->param_value) || isinf(set->param_value))){
      return PARAMETERS_FAILED;
    }
    if (global_data[index].value == set->param_value){
      return PARAMETERS_FAILED;
    }
    /* If value fall out of min..max bound than just silently set nearest allowable value */
    if (set->param_value > global_data[index].max){
      global_data[index].value = global_data[index].max;
      return PARAMETERS_SUCCESS;
    }
    if (set->param_value < global_data[index].min){
      global_data[index].value = global_data[index].min;
      return PARAMETERS_SUCCESS;
    }

    global_data[index].value = set->param_value;
    return PARAMETERS_SUCCESS;
  }

  /*error trap*/
  return PARAMETERS_FAILED;
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
    index = key_value_search(key);
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
    status = chMBPostAhead(&tolink_mb, (msg_t)param_value_mail, MS2ST(5));
    if (status != RDY_OK)
      return PARAMETERS_FAILED;

    /* wait until message processed */
    chMBFetch(&param_confirm_mb, &tmp, TIME_INFINITE);
  }
  else
    return PARAMETERS_FAILED;

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
 * ѕоток принимающий сообщени€ с параметрами и отправл€ющий параметры по запросу.
 */
static WORKING_AREA(ParametersThreadWA, 512);
static msg_t ParametersThread(void *arg){
  chRegSetThreadName("Parameters");
  (void)arg;

  /* переменные дл€ отправки установленных параметров */
  mavlink_param_value_t param_value_struct;
  Mail param_value_mail = {NULL, MAVLINK_MSG_ID_PARAM_VALUE, &param_confirm_mb};

  /* переменные дл€ приема параметров */
  msg_t tmp = 0;
  Mail *input_mail = NULL;
  mavlink_param_set_t *set = NULL;
  mavlink_param_request_list_t *list = NULL;
  mavlink_param_request_read_t *read = NULL;
  bool_t status = PARAMETERS_FAILED;

  while (TRUE) {
    chMBFetch(&param_mb, &tmp, TIME_INFINITE);
    input_mail = (Mail*)tmp;

    switch (input_mail->invoice){
    /*
     * согласно протоколу, при успешной установке параметра, мы должны
     * вычитать и выслать в ответ этот параметр в качестве подтверждени€
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
      if (list->target_system == mavlink_system.sysid)
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

