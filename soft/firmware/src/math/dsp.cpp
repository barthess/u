#include "uav.h"
#include "dsp.hpp"

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


