#include <math.h>
#include "uav.h"
#include "misc_math.hpp"

/**
 *
 */
uint32_t pack8to32(uint8_t *buf){
  uint32_t result = 0;
  result |= buf[0]<<24;
  result |= buf[1]<<16;
  result |= buf[2]<<8;
  result |= buf[3];
  return result;
}

/**
 *
 */
uint16_t pack8to16(uint8_t *buf){
  uint16_t result = 0;
  result |= buf[0]<<8;
  result |= buf[1];
  return result;
}

/**
 *
 */
int16_t complement2signed(uint8_t msb, uint8_t lsb){
  uint16_t word = 0;
  word = (msb << 8) + lsb;
  if (msb > 0x7F){
    return -1 * ((int16_t)((~word) + 1));
  }
  return (int16_t)word;
}

/**
 * @brief   Crude polled delay. Suitable for delays shorter than OS time quantum.
 *
 * @param[in] uS    delay in uS.
 */
void polled_delay_us(uint32_t uS){
  uint32_t t1, tmo;

  tmo = 1 + (halGetCounterFrequency() * uS) / 1000000;
  t1 = halGetCounterValue();
  while ((halGetCounterValue() - t1) < tmo)
    ;
}

/*
Caution added by Martin L. Buchanan, mlb@backgroundtask.com, Wed 11/16/2005:

If number is the maximum unsigned int value, call it MAX_VAL, then the first
evaluation of NEXT(n, number), with n == 1, produces an overflow when
1 + MAX_VAL/1 is evaluated. For an unsigned type the overflow typically
wraps around and yields zero as the macro result and zero as the
overall function result.
*/
//#define NEXT(n, i)  (((n) + (i)/(n)) >> 1)
//
//uint32_t isqrt(uint32_t number){
//  uint32_t n  = 1;
//  uint32_t n1 = NEXT(n, number);
//
//  while(abs(n1 - n) > 1){
//    n  = n1;
//    n1 = NEXT(n, number);
//  }
//  while(n1*n1 > number)
//    n1--;
//  return n1;
//}


/* But the following algorithm is many times faster, even when you have
 * hardware multiplication and division. */
uint32_t sqrti(uint32_t x){
  uint32_t op, res, one;

  op = x;
  res = 0;

  /* "one" starts at the highest power of four <= than the argument. */
  one = 1 << 30;  /* second-to-top bit set */
  while (one > op) one >>= 2;

  while (one != 0) {
    if (op >= res + one) {
      op -= res + one;
      res += one << 1;  // <-- faster than 2 * one
    }
    res >>= 1; /* div by 2 */
    one >>= 2; /* div by 4 */
  }
  return res;
}

/**
 * Integer power function.
 */
int32_t powi(int32_t base, uint32_t exp){
  int32_t result = 1;
  while (exp > 0){
    result *= base;
    exp--;
  }
  return result;
}

/* mod(a, 2*pi) is the remainder you get when you divide a by 2*pi;
that is, subtract the largest multiple of 2*pi less than a from a,
and that's the answer. */
float fmodulo(float x, float y){
  return x - y * floorf(x/y);
}


