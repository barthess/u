#include <math.h>
#include <string.h>
#include <limits.h>

#include "uav.h"
#include "message.hpp"
#include "param_registry.hpp"
#include "misc_math.hpp"

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
static bool_t sortmtrx_good(uint32_t v){
  uint32_t p0 = (v & 0b111);
  uint32_t p1 = (v & 0b111000) >> 3;
  uint32_t p2 = (v & 0b111000000) >> 6;

  if (((p0 | p1 | p2) == 0b111) && ((p0 & p1 & p2) == 0))
    return TRUE;
  else
    return FALSE;
}

param_status_t ParamValidator::sortmtrx_val(void *value, const GlobalParam_t *param){
  uint32_t v = param->valuep->u32;
  if ( ! sortmtrx_good(v))
    param->valuep->u32 = param->def.u32;

  v = *(uint32_t*)value;

  if (v == param->valuep->u32)
    return PARAM_NOT_CHANGED;

  if (sortmtrx_good(v)){
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
static bool_t polarity_good(int32_t v){
  if ((v == 1) || (v == -1))
    return TRUE;
  else
    return FALSE;
}

param_status_t ParamValidator::polarity_val(void *value, const GlobalParam_t *param){

  int32_t v = param->valuep->i32;
  if ( ! polarity_good(v))
    param->valuep->i32 = param->def.i32;

  v = *(int32_t*)value;
  if (param->valuep->i32 == v)
    return PARAM_NOT_CHANGED;

  if ( ! polarity_good(v))
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
param_status_t ParamValidator::sendtmo_val(void *value, const GlobalParam_t *param){
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
  v = putinrange(v, param->min.u32, param->max.u32);
  param->valuep->u32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * Uint32 boundary checker.
 */
param_status_t ParamValidator::uint_val(void *value, const GlobalParam_t *param){
  uint32_t initial_value = *(uint32_t*)value;
  uint32_t v = initial_value;

  if (param->valuep->u32 == v)
    return PARAM_NOT_CHANGED;

  v = putinrange(v, param->min.u32, param->max.u32);
  param->valuep->u32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * Float boundary checker.
 */
param_status_t ParamValidator::float_val(void *value, const GlobalParam_t *param){
  float initial_value = *(float*)value;
  float v = initial_value;

  // AND only write if new value is NOT "not-a-number" AND is NOT infinity
  if (isnan(v) || isinf(v))
    return PARAM_INCONSISTENT;

  if (param->valuep->f32 == v)
    return PARAM_NOT_CHANGED;

  v = putinrange(v, param->min.f32, param->max.f32);
  param->valuep->f32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

/**
 * Int32 boundary checker.
 */
param_status_t ParamValidator::int_val(void *value, const GlobalParam_t *param){
  int32_t initial_value = *(int32_t*)value;
  int32_t v = initial_value;

  if (param->valuep->i32 == v)
    return PARAM_NOT_CHANGED;

  v = putinrange(v, param->min.i32, param->max.i32);
  param->valuep->i32 = v;

  if (v == initial_value)
    return PARAM_OK;
  else
    return PARAM_CLAMPED;
}

param_status_t ParamValidator::default_val(void *value, const GlobalParam_t *param){
  switch(param->param_type){
  case MAVLINK_TYPE_FLOAT:
    return this->float_val(value, param);
    break;
  case MAVLINK_TYPE_UINT32_T:
    return this->uint_val(value, param);
    break;
  case MAVLINK_TYPE_INT32_T:
    return this->int_val(value, param);
    break;
  default:
    return PARAM_WRONG_TYPE;
  }
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * @brief   Global boundary checker.
 *
 * @param[in] value   input value that must be checked and saved into
 * @param[in] param   appropriate parameter in array
 *
 * @return            operation status.
 */
param_status_t ParamValidator::set(void *value, const GlobalParam_t *param){

  switch(param->func){
  case PARAM_DEFAULT:
    return this->default_val(value, param);
    break;
  case PARAM_SEND_TMO:
    return this->sendtmo_val(value, param);
    break;
  case PARAM_SORT_MTRX:
    return this->sortmtrx_val(value, param);
    break;
  case PARAM_POLARITY:
    return this->polarity_val(value, param);
    break;
  default:
    chDbgPanic("unhandled type");
    break;
  }
  return PARAM_WRONG_TYPE;/* warning suppressor */
}
