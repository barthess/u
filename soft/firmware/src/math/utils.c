#include "uav.h"

#include "arm_math.h"

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

/**
 * Measure execution time of some function for dubug purpose.
 */
void time_test(void){
  TimeMeasurement tmup;
  volatile float x = 0;
  volatile uint32_t y = 0;
  volatile uint32_t n = 1000000;
  volatile uint32_t imu_update_period = 0;

  tmObjectInit(&tmup);
  tmStartMeasurement(&tmup);
  x = arm_cos_f32(PI/3.0);
  tmStopMeasurement(&tmup);
  imu_update_period = tmup.last;

  imu_update_period = 0;
  tmStartMeasurement(&tmup);
  for (;n >0; n--)
    y = arm_cos_q31(n);
  tmStopMeasurement(&tmup);
  imu_update_period = tmup.last;

  (void)x;
  (void)y;
  (void)imu_update_period;
}

/**
 * Median filter on 5 points
 * *buf[in]     pointer to fifo buffer
 * sample[in]   new sample
 *
 * return       median value
 */
uint32_t median_filter_5(uint32_t *buf, uint32_t sample){
  const uint32_t N_samples = 5;
  uint32_t j = 0, i = 0;
  int32_t sorted[N_samples];
  int32_t tmp;

  /* place new sample in fifo */
  for(j=1; j<N_samples; j++){
    buf[j-1] = buf[j];
  }
  buf[j-1] = sample;

  /* place data in temporal buffer */
  for(j=0; j<N_samples; j++){
    sorted[j] = buf[j];
  }

  /* booble sort */
  for(i=0; i<=N_samples-1; i++){
    for(j=i+1; j<N_samples;j++){
      if(sorted[i] > sorted[j]){
        tmp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = tmp;
      }
    }
  }

  return sorted[2];
}

/**
 * Median filter on 3 points
 * *buf[in]     pointer to fifo buffer
 * sample[in]   new sample
 *
 * return       median value
 */
uint32_t median_filter_3(uint32_t *buf, uint32_t sample){
  const uint32_t N_samples = 3;
  uint32_t j = 0, i = 0;
  int32_t sorted[N_samples];
  int32_t tmp;

  /* place new sample in fifo */
  for(j=1; j<N_samples; j++){
    buf[j-1] = buf[j];
  }
  buf[j-1] = sample;

  /* place data in temporal buffer */
  for(j=0; j<N_samples; j++){
    sorted[j] = buf[j];
  }

  /* booble sort */
  for(i=0; i<=N_samples-1; i++){
    for(j=i+1; j<N_samples;j++){
      if(sorted[i] > sorted[j]){
        tmp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = tmp;
      }
    }
  }

  return sorted[1];
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
uint32_t isqrt(uint32_t x){
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
 * convert from degrees to radians
 */
float fdeg2rad(float deg){
  return deg * (PI / 180.0);
}

/**
 * convert from degrees to radians
 */
float frad2deg(float rad){
  return rad * (180.0 / PI);
}

/* mod(a, 2*pi) is the remainder you get when you divide a by 2*pi;
that is, subtract the largest multiple of 2*pi less than a from a,
and that's the answer. */
float fmodulo(float x, float y){
  return x - y * floor(x/y);
}

int32_t wrap_180(int32_t error){
  if (error > 180)
    error -= 360;
  if (error < -180)
    error += 360;
  return error;
}

float wrap_pi(float error){
  if (error > PI)
    error -= 2*PI;
  if (error < -PI)
    error += 2*PI;
  return error;
}

int32_t wrap_360(int32_t angle){
  if (angle > 360)
    angle -= 360;
  if (angle < 0)
    angle += 360;
  return angle;
}

float wrap_2pi(float angle){
  if (angle > 2*PI)
    angle -= 2*PI;
  if (angle < 0)
    angle += 2*PI;
  return angle;
}

/**
 * Suppose you are proceeding on a great circle route from A to B
 * (course =crs_AB) and end up at D, perhaps off course.
 * (We presume that A is not a pole!) You can calculate the course from
 * A to D (crs_AD) and the distance from A to D (dist_AD) using the
 * formulae above. In terms of these the cross track error, XTD,
 * (distance off course) is given by
 *
 * (positive XTD means right of course, negative means left)
 */
float crosstrack( float start_x,    float start_y,
                  float current_x,  float current_y,
                  float crs_AB){

  float crs_AD, dist_AD;
  float XTD;
  float delta_x, delta_y;

  delta_x = current_x - start_x;
  delta_y = current_y - start_y;
  dist_AD = sqrtf(delta_x*delta_x + delta_y*delta_y);

  crs_AD = atan2f(delta_y, delta_x);
  XTD = asinf(sinf(dist_AD) * sinf(crs_AD - crs_AB));
  return XTD;
}

