/*
 * dsp.h
 *
 *  Created on: Jul 12, 2012
 *      Author: barthess
 */

#ifndef DSP_H_
#define DSP_H_

#include "arm_math.h"

/**
 *
 */
typedef struct alphabeta_instance_q31 alphabeta_instance_q31;
struct alphabeta_instance_q31{
  /**
   * @brief   Accumulator.
   */
  q31_t acc;
  /**
   * @brief   Filter length.
   * @details This is the power of 2.
   */
  uint8_t len;
};


q31_t alhpabeta_q31(alphabeta_instance_q31 *S, q31_t val);
bool_t alhpabeta_init_q31(alphabeta_instance_q31 *S, uint16_t len, q31_t acc);
bool_t alhpabeta_change_len_q31(alphabeta_instance_q31 *S, uint16_t len);

#endif /* DSP_H_ */
