#ifndef UTILS_H_
#define UTILS_H_

#include "ch.h"
#include "hal.h"

#define putinrange(v, vmin, vmax){                                            \
  chDbgCheck(vmin <= vmax, "");                                               \
  if (v <= vmin)                                                              \
    v = vmin;                                                                 \
  else if (v >= vmax)                                                         \
    v = vmax;                                                                 \
}

uint32_t pack8to32(uint8_t *buf);
uint16_t pack8to16(uint8_t *buf);

int32_t Simpson(int32_t a, int32_t b, int32_t c, int32_t t);
int32_t Simpson38(int32_t a, int32_t b, int32_t c, int32_t d, int32_t t);

int16_t complement2signed(uint8_t msb, uint8_t lsb);

uint32_t median_filter_5(uint32_t *buf, uint32_t sample);
uint32_t median_filter_3(uint32_t *buf, uint32_t sample);

uint32_t isqrt(uint32_t x);

float fdeg2rad(float deg);
float frad2deg(float rad);

int32_t wrap_180(int32_t error);
float wrap_pi(float error);
int32_t wrap_360(int32_t angle);
float wrap_2pi(float angle);

float crosstrack( float start_x,    float start_y,
                  float current_x,  float current_y,
                  float crs_AB);

#endif /* UTILS_H_ */
