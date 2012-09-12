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