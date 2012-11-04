#include <math.h>

#include "uav.h"

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


/* Интеграл методом симпсона.
 * Шаг сетки принимается равным 1
 * Значения должны быть отнормированы до вызова функции
 * http://en.wikipedia.org/wiki/Simpson%27s_rule
 */
int32_t Simpson(int32_t a, int32_t b, int32_t c, int32_t t){
  return (t * (a + 4*b + c)) / 3;
}

/* Интеграл методом симпсона 3/8.
 * Шаг сетки принимается равным 1
 * Значения должны быть отнормированы до вызова функции
 * http://en.wikipedia.org/wiki/Simpson%27s_rule
 *
 * От деления на 8 можно избавится, если в вызывающей функции производится
 * умножение на степень двойки, но сильно пострадает инкапсуляция и очевидность.
 */
int32_t Simpson38(int32_t a, int32_t b, int32_t c, int32_t d, int32_t t){
  return (t * 3 * (a + 3*b + 3*c + d)) / 8;
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
  if (exp == 0)
    return 1;
  else{
    while (exp > 0){
      base *= base;
      exp--;
    }
    return base;
  }
}

/* mod(a, 2*pi) is the remainder you get when you divide a by 2*pi;
that is, subtract the largest multiple of 2*pi less than a from a,
and that's the answer. */
float fmodulo(float x, float y){
  return x - y * floorf(x/y);
}

/**
 * Sort vector of 3 values according to sorting matrix
 * |0 1 0|   |v0|
 * |1 0 0| x |v1| = |v1 v0 v2|
 * |0 0 1|   |v2|
 * using matrix multiplication formulae this operation requires
 * 9 multiplies and 6 additions. We can replace this by switch-case logic
 *
 * all possible combinations:
 * 1 2 3 4 5 6
 * -----------
 * 0 1 0 1 2 2
 * 1 0 2 2 1 0
 * 2 2 1 0 0 1
 */
/* reference realization */
void sort_3values(int32_t *in, int32_t *out, uint32_t sortmatrix){
  switch (sortmatrix){
  case 0b001100010: // #6
    //   001
    //   100
    //   010
    out[0] = in[2];
    out[1] = in[0];
    out[2] = in[1];
    break;
  case 0b001010100: // #5
    //   001
    //   010
    //   100
    out[0] = in[2];
    out[1] = in[1];
    out[2] = in[0];
    break;
  case 0b010001100: // #4
    //   010
    //   001
    //   100
    out[0] = in[1];
    out[1] = in[2];
    out[2] = in[0];
    break;
  case 0b100001010: // #3
    //   100
    //   001
    //   010
    out[0] = in[0];
    out[1] = in[2];
    out[2] = in[1];
    break;
  case 0b010100001: // #2
    //   010
    //   100
    //   001
    out[0] = in[1];
    out[1] = in[0];
    out[2] = in[2];
    break;
  case 0b100010001: // #1
    //   100
    //   010
    //   001
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    break;
  default:
    chDbgPanic("bad sorting matrix");
    break;
  }
}

#define __sort3 \
  switch (sortmatrix){\
  case 0b001100010: out[0] = in[2]; out[1] = in[0]; out[2] = in[1]; break;\
  case 0b001010100: out[0] = in[2]; out[1] = in[1]; out[2] = in[0]; break;\
  case 0b010001100: out[0] = in[1]; out[1] = in[2]; out[2] = in[0]; break;\
  case 0b100001010: out[0] = in[0]; out[1] = in[2]; out[2] = in[1]; break;\
  case 0b010100001: out[0] = in[1]; out[1] = in[0]; out[2] = in[2]; break;\
  case 0b100010001: out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; break;\
  default: chDbgPanic("bad sorting matrix"); break;\
  }

void sortf_3values(float *in,    float *out,    uint32_t sortmatrix){
  __sort3
}

void sortu_3values(uint32_t *in, uint32_t *out, uint32_t sortmatrix){
  __sort3
}

void sorti_3values(int32_t *in,  int32_t *out,  uint32_t sortmatrix){
  __sort3
}
