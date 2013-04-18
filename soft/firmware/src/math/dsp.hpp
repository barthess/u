#ifndef DSP_H_
#define DSP_H_

typedef int32_t q31_t;
typedef q31_t alphabeta_instance_q31;
typedef float alphabeta_instance_float;

q31_t alphabeta_q31(alphabeta_instance_q31 *S, q31_t val, uint32_t len);
float alphabeta_float(alphabeta_instance_float *S, float val, uint32_t len);

uint32_t median_filter_5(uint32_t *buf, uint32_t sample);
uint32_t median_filter_3(uint32_t *buf, uint32_t sample);

#endif /* DSP_H_ */
