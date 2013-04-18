#include <string.h>

#include "uav.h"
#include "global_flags.h"
#include "message.hpp"
#include "param_registry.hpp"
#include "memfunc.hpp"
#include "mavlink_dbg.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define PARAM_CONFIRM_TMO   MS2ST(1000)
#define PARAM_POST_TMO      MS2ST(50)

#define SEND_VALUE_PAUSE    MS2ST(50)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern ParamRegistry param_registry;
extern GlobalFlags_t GlobalFlags;

extern mavlink_system_t               mavlink_system_struct;
extern mavlink_param_value_t          mavlink_out_param_value_struct;
extern mavlink_param_set_t            mavlink_in_param_set_struct;
extern mavlink_param_request_read_t   mavlink_in_param_request_read_struct;
extern mavlink_param_request_list_t   mavlink_in_param_request_list_struct;

extern EventSource event_mavlink_in_param_set;
extern EventSource event_mavlink_in_param_request_list;
extern EventSource event_mavlink_in_param_request_read;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
/**
 * @brief   Sends mails to communication thread
 *
 * @param[in] key   if NULL than perform search by index
 * @param[in] n     search index
 */
static bool_t send_value(char *key, int32_t n){
  int32_t index = -1;
  const GlobalParam_t *p;

  p = param_registry.getParam(key, n, &index);

  if (-1 != index){
    /* fill all fields */
    mavlink_out_param_value_struct.param_value = p->valuep->f32;
    mavlink_out_param_value_struct.param_type  = p->param_type;
    mavlink_out_param_value_struct.param_count = param_registry.paramCount();
    mavlink_out_param_value_struct.param_index = index;
    memcpy(mavlink_out_param_value_struct.param_id, p->name, ONBOARD_PARAM_NAME_LENGTH);

    /* inform sending thread */
    ParamSendOut();
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
  while ((i < param_registry.paramCount()) && (retry > 0)){
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
  mavlink_param_set_t param_set_msg; /* local copy for thread safety */

  if (CH_SUCCESS != memcpy_ts(&param_set_msg, &mavlink_in_param_set_struct, sizeof(param_set_msg), 4))
    return;

  valuep = (floatint *)&(param_set_msg.param_value);
  paramp = param_registry.getParam(param_set_msg.param_id, -1, NULL);
  status = param_registry.setParam(valuep, paramp);

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
  send_value(param_set_msg.param_id, 0);
}

/**
 *
 */
static void param_request_read_handler(void){
  mavlink_param_request_read_t p; /* local copy */

  if (CH_SUCCESS != memcpy_ts(&p, &mavlink_in_param_request_read_struct, sizeof(p), 4))
    return;

  if (p.param_index >= 0)
    send_value(NULL, p.param_index);
  else
    send_value(p.param_id, 0);
}

/**
 * Deside is this packed addressed to us.
 */
template <typename T>
static bool_t for_me(T *message){
  if (message->target_system != mavlink_system_struct.sysid)
    return FALSE;
  if (message->target_component == mavlink_system_struct.compid)
    return TRUE;
  else if (message->target_component == MAV_COMP_ID_ALL)
    return TRUE;
  else
    return FALSE;
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
    /* setParam param */
    case EVMSK_MAVLINK_IN_PARAM_SET:
      if (for_me(&mavlink_in_param_set_struct))
        param_set_handler();
      break;

    /* request all */
    case EVMSK_MAVLINK_IN_PARAM_REQUEST_LIST:
      if (for_me(&mavlink_in_param_request_list_struct))
        send_all_values();
      break;

    /* request single */
    case EVMSK_MAVLINK_IN_PARAM_REQUEST_READ:
      if (for_me(&mavlink_in_param_request_read_struct))
        param_request_read_handler();
      break;
    }
  }
  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void ParametersInit(void){
  /* read data from eeprom to memory mapped structure */
  param_registry.load();

  chThdCreateStatic(ParametersThreadWA,
          sizeof(ParametersThreadWA),
          LINK_THREADS_PRIO + 1,
          ParametersThread,
          NULL);

  setGlobalFlag(GlobalFlags.parameters_ready);
}
