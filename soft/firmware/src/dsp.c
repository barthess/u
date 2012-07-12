#include "ch.h"
#include "hal.h"

#include "dsp.h"

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
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * @brief   Do alpha beta filtering.
 * @note    There is no saturation mechanism! Accumulator will wrap over zero
 *          if overflows.
 */
q31_t alphabeta_q31(alphabeta_instance_q31 *S, q31_t val){
  S->acc -= S->acc >> S->len;
  S->acc += val;
  return S->acc >> S->len;
}

/**
 * @brief   Perform init.
 * @param[in] *S points to an instance of the filter structure.
 * @param[in] len is length of filter.
 * @param[in] acc initial value of accumulator.
 */
bool_t alphabeta_init_q31(alphabeta_instance_q31 *S, uint16_t len, q31_t acc){
  S->acc = acc;
  if ((len < 31) && (len > 0)){
    S->len = len;
    return CH_SUCCESS;
  }
  else
    return CH_FAILED;
}

/**
 *
 */
bool_t alphabeta_change_len_q31(alphabeta_instance_q31 *S, uint16_t len){
  if ((len < 31) && (len > 0)){
    S->len = len;
    return CH_SUCCESS;
  }
  else
    return CH_FAILED;
}




