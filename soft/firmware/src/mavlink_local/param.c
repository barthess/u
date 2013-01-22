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

#define SEND_VALUE_PAUSE    MS2ST(100)

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

extern mavlink_param_value_t          mavlink_param_value_struct;
extern mavlink_param_set_t            mavlink_param_set_struct;
extern mavlink_param_request_read_t   mavlink_param_request_read_struct;

extern EventSource event_mavlink_out_param_value;
extern EventSource event_mavlink_in_param_set;
extern EventSource event_mavlink_in_param_request_list;
extern EventSource event_mavlink_in_param_request_read;

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
static bool_t send_value(char *key, uint32_t n){
  int32_t index = -1;

  if (key != NULL)
    index = key_index_search(key);
  else
    index = n;

  if ((index >= 0) && (index <= OnboardParamCount)){
    /* fill all fields */
    mavlink_param_value_struct.param_value = GlobalParam[index].valuep->f32;
    mavlink_param_value_struct.param_type  = GlobalParam[index].param_type;
    mavlink_param_value_struct.param_count = OnboardParamCount;
    mavlink_param_value_struct.param_index = index;
    memcpy(mavlink_param_value_struct.param_id, GlobalParam[index].name, ONBOARD_PARAM_NAME_LENGTH);

    /* inform sending thread */
    chEvtBroadcastFlags(&event_mavlink_out_param_value, EVMSK_MAVLINK_OUT_PARAM_VALUE);
    chThdSleep(SEND_VALUE_PAUSE);
  }
  else
    return PARAM_FAILED;

  return PARAM_SUCCESS;
}

/**
 * Send all values one by one.
 */
static void send_all_values(void){
  int32_t i = 0;
  int32_t retry = 20;

  msg_t status = RDY_RESET;
  while ((i < OnboardParamCount) && (retry > 0)){
    status = send_value(NULL, i);
    if (status == PARAM_SUCCESS)
      i++;
    else
      retry--;
  }
}

/**
 * The MAV has to acknowledge the write operation by emitting a
 * PARAM_VALUE value message with the newly written parameter value.
 */
static void param_set_handler(void){
  floatint *valuep = NULL;
  const GlobalParam_t *paramp = NULL;
  param_status_t status;
  mavlink_param_set_t p; /* local copy for thread safety */

  if (CH_SUCCESS != memcpy_ts(&p, &mavlink_param_set_struct, sizeof(p), 4))
    return;

  valuep = (floatint *)&(p.param_value);
  paramp = &GlobalParam[key_index_search(p.param_id)];
  status = set_global_param(valuep, paramp);

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
  send_value(p.param_id, 0);
}

/**
 *
 */
void param_request_read_handler(void){
  mavlink_param_request_read_t p; /* local copy */

  if (CH_SUCCESS != memcpy_ts(&p, &mavlink_param_request_read_struct, sizeof(p), 4))
    return;

  if (p.param_index >= 0)
    send_value(NULL, p.param_index);
  else
    send_value(p.param_id, 0);
}


/**
 * Receive messages with parameters and transmit parameters by requests.
 */
static WORKING_AREA(ParametersThreadWA, 256);
static msg_t ParametersThread(void *arg){
  chRegSetThreadName("Parameters");
  (void)arg;

  while(GlobalFlags.messaging_ready == 0)
    chThdSleepMilliseconds(50);

  eventmask_t evt = 0;
  struct EventListener el_param_set;
  struct EventListener el_param_request_list;
  struct EventListener el_param_request_read;
  chEvtRegisterMask(&event_mavlink_in_param_set,           &el_param_set,          EVMSK_MAVLINK_IN_PARAM_SET);
  chEvtRegisterMask(&event_mavlink_in_param_request_list,  &el_param_request_list, EVMSK_MAVLINK_IN_PARAM_REQUEST_LIST);
  chEvtRegisterMask(&event_mavlink_in_param_request_read,  &el_param_request_read, EVMSK_MAVLINK_IN_PARAM_REQUEST_READ);

  while (!chThdShouldTerminate()) {
    evt = chEvtWaitOne(EVMSK_MAVLINK_IN_PARAM_SET | EVMSK_MAVLINK_IN_PARAM_REQUEST_LIST | EVMSK_MAVLINK_IN_PARAM_REQUEST_READ);

    switch (evt){
    /* set param */
    case EVMSK_MAVLINK_IN_PARAM_SET:
      param_set_handler();
      break;

    /* request all */
    case EVMSK_MAVLINK_IN_PARAM_REQUEST_LIST:
      send_all_values();
      break;

    /* request single */
    case EVMSK_MAVLINK_IN_PARAM_REQUEST_READ:
      param_request_read_handler();
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
