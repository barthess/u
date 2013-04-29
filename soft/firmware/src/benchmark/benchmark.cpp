#include "main.h"
#include "matrix.hpp"

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
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static TimeMeasurement tmup;
static volatile uint32_t result;

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

//static volatile int32_t t0, t1;
//  t0 = hal_lld_get_counter_value();
//  this->detect_immobility();
//  t1 = hal_lld_get_counter_value() - t0;

/**
 *
 */
float benchmark_matrix_mul(void){
  uint32_t i = 0;
  float m1[15*15];
  float m2[15*15];
  float res[15*15];

  for (i=0; i<225; i++){
    m1[i] = 0;
    m2[i] = 0;
  }
  tmObjectInit(&tmup);
  tmStartMeasurement(&tmup);
  matrix_multiply(15, 15, 15, m1, m2, res);
  tmStopMeasurement(&tmup);

  result = tmup.last;
  return res[113] * result;
}

/**
 *
 */
float benchmark_matrix_inv(void){

  uint32_t i = 0;
  float A[81];

  for (i=0; i<(sizeof(A)/sizeof(A[0])); i++){
    A[i] = i * 0.013f;
  }
  tmObjectInit(&tmup);
  tmStartMeasurement(&tmup);
  matrix_inverse(9, A);
  tmStopMeasurement(&tmup);

  result = tmup.last;
  return A[10] * result;
}



