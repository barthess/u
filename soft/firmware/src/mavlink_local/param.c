#include <math.h>
#include <string.h>
#include <limits.h>

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
static param_status_t _polarity_param_checker(void *value, const GlobalParam_t *param);
static param_status_t _sendtmo_param_checker(void *value, const GlobalParam_t *param);
static param_status_t _sortmtrx_param_checker(void *value, const GlobalParam_t *param);

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

EepromFileStream EepromSettingsFile;
BinarySemaphore SettingsFile_sem;

extern GlobalFlags_t GlobalFlags;
extern Mailbox mavlink_param_set_mb;
extern Mailbox tolink_mb;
extern mavlink_system_t mavlink_system_struct;
extern mavlink_param_value_t mavlink_param_value_struct;


#include "param_autogenerated.c"


/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

static uint8_t eeprom_buf[EEPROM_TX_DEPTH];

static const I2CEepromFileConfig eeprom_settings_cfg = {
  &EEPROM_I2CD,
  EEPROM_SETTINGS_START,
  EEPROM_SETTINGS_END,
  EEPROM_SIZE,
  EEPROM_PAGE_SIZE,
  EEPROM_I2C_ADDR,
  MS2ST(EEPROM_WRITE_TIME_MS),
  eeprom_buf,
};

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

static bool_t __is_sortmtrx_good(uint32_t v){
  uint32_t p0 = (v & 0b111);
  uint32_t p1 = (v & 0b111000) >> 3;
  uint32_t p2 = (v & 0b111000000) >> 6;

  if (((p0 | p1 | p2) == 0b111) && ((p0 & p1 & p2) == 0))
    return TRUE;
  else
    return FALSE;
}
static param_status_t _sortmtrx_param_checker(void *value, const GlobalParam_t *param){
  uint32_t v = param->valuep->u32;
  if ( ! __is_sortmtrx_good(v))
    param->valuep->u32 = param->def.u32;

  v = *(uint32_t*)value;

  if (v == param->valuep->u32)
    return PARAM_NOT_CHANGED;

  if (__is_sortmtrx_good(v)){
    param->valuep->u32 = v;
    return PARAM_OK;
  }
  else{
    return PARAM_INCONSISTENT;
  }
}

/**
 * Polarity accessibility checker.
 * Value must be 1 OR -1.
 * Only write and emit changes if there is actually a difference
 */
static bool_t __is_polarity_good(int32_t v){
  if ((v == 1) || (v == -1))
    return TRUE;
  else
    return FALSE;
}
static param_status_t _polarity_param_checker(void *value, const GlobalParam_t *param){

  int32_t v = param->valuep->i32;
  if ( ! __is_polarity_good(v))
    param->valuep->i32 = param->def.i32;

  v = *(int32_t*)value;
  if (param->valuep->i32 == v)
    return PARAM_NOT_CHANGED;

  if ( ! __is_polarity_good(v))
    return PARAM_INCONSISTENT;
  else
    param->valuep->i32 = v;

  /* value good */
  return PARAM_OK;
}

/**
 * Check send periods for different messages.
 * It must be zero OR between min and max.
 */
static param_status_t _sendtmo_param_checker(void *value, const GlobalParam_t *param){
  uint32_t initial_value = *(uint32_t*)value;
  uint32_t v = initial_value;

  /**/
  if (v == SEND_OFF){
    if (param->valuep->u32 == v)
      return PARAM_NOT_CHANGED;
    else{
      param->valuep->u32 = v;
      return PARAM_OK;
    }
  }

  /**/
  putinrange(v, param->min.u32, param->max.u32);
  param->valuep->u32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * Float boundary checker.
 * Only write and emit changes if there is actually a difference
 */
static param_status_t _float_param_checker(void *value, const GlobalParam_t *param){
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
static param_status_t _int_param_checker(void *value, const GlobalParam_t *param){
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
static param_status_t _uint_param_checker(void *value, const GlobalParam_t *param){
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

  if (!GlobalFlags.tlm_link_ready)
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
    param_value_struct->param_value = GlobalParam[index].valuep->f32;
    param_value_struct->param_type  = GlobalParam[index].param_type;
    param_value_struct->param_count = OnboardParamCount;
    param_value_struct->param_index = index;
    for (j = 0; j < ONBOARD_PARAM_NAME_LENGTH; j++)
      param_value_struct->param_id[j] = GlobalParam[index].name[j];

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

      status = set_global_param(&(set->param_value),
                  &GlobalParam[key_index_search(set->param_id)]);

      /* send confirmation */
      switch(status){
      case PARAM_CLAMPED:
        mavlink_dbg_print(MAV_SEVERITY_WARNING, "PARAM: clamped");
        break;
      case PARAM_NOT_CHANGED:
        mavlink_dbg_print(MAV_SEVERITY_WARNING, "PARAM: not changed");
        break;
      case PARAM_INCONSISTENT:
        mavlink_dbg_print(MAV_SEVERITY_ERROR, "PARAM: inconsistent");
        break;
      case PARAM_WRONG_TYPE:
        mavlink_dbg_print(MAV_SEVERITY_ERROR, "PARAM: wrong type");
        break;
      case PARAM_OK:
        break;
      }
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
    if (strcmp(key, GlobalParam[i].name) == 0)
      return i;
  }
  return -1;
}

/**
 * Return pointer to value. Hi level function.
 */
void *ValueSearch(const char *str){
  int32_t i = -1;

  chDbgCheck(GlobalFlags.parameters_got == 1, "parameters not ready");

  i = key_index_search(str);
  if (i == -1){
    chDbgPanic("key not found");
    return NULL;
  }
  else
    return GlobalParam[i].valuep;
}

/**
 * @brief   Global boundary checker.
 *
 * @param[in] value   input value that must be checked and saved into
 * @param[in] param   appropriate parameter in array
 *
 * @return            operation status.
 */
param_status_t set_global_param(void *value, const GlobalParam_t *param){

  if (param->func == NULL){
    switch(param->param_type){
    case MAVLINK_TYPE_FLOAT:
      return _float_param_checker(value, param);
      break;
    case MAVLINK_TYPE_UINT32_T:
      return _uint_param_checker(value, param);
      break;
    case MAVLINK_TYPE_INT32_T:
      return _int_param_checker(value, param);
      break;
    }
    chDbgPanic("type unsupported");
    return PARAM_WRONG_TYPE;
  }
  else
    return param->func(value, param);
}

/**
 *
 */
void ParametersInit(void){

//  (void)_sendtmo_param_checker;   /*warning supressor */
//  (void)_polarity_param_checker;  /*warning supressor */
//  (void)_sortmtrx_param_checker;  /*warning supressor */

  chDbgCheck(GlobalFlags.i2c_ready == 1, "bus not ready");

  int32_t i = 0;
  int32_t n = 0;
  int32_t gd_val_cnt = sizeof(gp_val) / sizeof(gp_val[0]);

  /* initialise variable array with zeroes to be safe */
  floatint v;
  v.u32 = 0;
  for (i = 0; i < gd_val_cnt; i++){
    gp_val[i] = v;
  }

  /* check hardcoded name lengths */
  for (i = 0; i < OnboardParamCount; i++){
    if (sizeof (*(GlobalParam[i].name)) > ONBOARD_PARAM_NAME_LENGTH)
      chDbgPanic("name too long");
  }

  /* check available length of variable array */
  if (OnboardParamCount > gd_val_cnt)
    chDbgPanic("not enough space in RAM to store parameters");

  /* check uniqueness of pointers to variable parameters */
  for (i = 0; i < OnboardParamCount; i++){
    void *vp = GlobalParam[i].valuep;
    for (n = i+1; n < OnboardParamCount; n++){
      if (vp == GlobalParam[n].valuep)
        chDbgPanic("Duplicate indexes detected");
    }
  }

  /* check boundaries */
  bool_t got = FALSE;
  for (i = 0; i < OnboardParamCount; i++){
    void *vp = GlobalParam[i].valuep;

    for (n = 0; n < gd_val_cnt; n++){
      if (vp == &gp_val[n])
        got = TRUE;
    }
    if (got == FALSE)
      chDbgPanic("probably pointer points out of arrya bounds");

    got = FALSE; /* go to next cycle */
  }

  /* check allowed size in EEPROM */
  uint32_t len = PARAM_ID_SIZE;
  len += sizeof(GlobalParam[0].valuep);
  if (OnboardParamCount * len > EEPROM_SETTINGS_SIZE)
    chDbgPanic("not enough space in EEPROM settings slice");

  /* open EEPROM region as file */
  chBSemInit(&SettingsFile_sem, FALSE);
  EepromFileOpen(&EepromSettingsFile, &eeprom_settings_cfg);

  /* read data from eeprom to memory mapped structure */
  load_params_from_eeprom();

  chThdCreateStatic(ParametersThreadWA,
          sizeof(ParametersThreadWA),
          LINK_THREADS_PRIO + 1,
          ParametersThread,
          NULL);

  setGlobalFlag(GlobalFlags.parameters_got);
}
