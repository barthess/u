/*
 * dsp.h
 *
 *  Created on: Jul 12, 2012
 *      Author: barthess
 */

#ifndef DSP_H_
#define DSP_H_

#include "arm_math.h"

typedef q31_t alphabeta_instance_q31;

q31_t alphabeta_q31(alphabeta_instance_q31 *S, q31_t val, uint32_t len);


#endif /* DSP_H_ */
