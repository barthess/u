#include <math.h>

#include "uav.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define ADC_NUM_CHANNELS          6
#define ADC_BUF_DEPTH             1

/* human readable names */
#define ADC_CURRENT_SENS          ADC_CHANNEL_IN10
#define ADC_MAIN_SUPPLY           ADC_CHANNEL_IN11
#define ADC_6V_SUPPLY             ADC_CHANNEL_IN12
#define ADC_AN33_0                ADC_CHANNEL_IN13
#define ADC_AN33_1                ADC_CHANNEL_IN14
#define ADC_AN33_2                ADC_CHANNEL_IN15

#define ADC_CURRENT_SENS_OFFSET   (ADC_CHANNEL_IN10 - 10)
#define ADC_MAIN_VOLTAGE_OFFSET   (ADC_CHANNEL_IN11 - 10)
#define ADC_6V_OFFSET             (ADC_CHANNEL_IN12 - 10)
#define ADC_AN33_0_OFFSET         (ADC_CHANNEL_IN13 - 10)
#define ADC_AN33_1_OFFSET         (ADC_CHANNEL_IN14 - 10)
#define ADC_AN33_2_OFFSET         (ADC_CHANNEL_IN15 - 10)

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */
static void adccallback(ADCDriver *adcp, adcsample_t *samples, size_t n);

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint32_t *flen_adc;      /* length of filter for ADC */

static ADCConfig adccfg; // dummy for STM32

static adcsample_t samples[ADC_NUM_CHANNELS * ADC_BUF_DEPTH];

/**/
static alphabeta_instance_q31 main_current_filter;
static alphabeta_instance_q31 main_voltage_filter;
static alphabeta_instance_q31 secondary_voltage_filter;

/*
 * ADC conversion group.
 */
static const ADCConversionGroup adccg = {
  TRUE,
  ADC_NUM_CHANNELS,
  adccallback,
  NULL,
  0,                        /* CR1 */
  ADC_CR2_SWSTART,          /* CR2 */
  ADC_SMPR1_SMP_AN10(ADC_SAMPLE_480) |
    ADC_SMPR1_SMP_AN11(ADC_SAMPLE_480) |
    ADC_SMPR1_SMP_AN12(ADC_SAMPLE_480) |
    ADC_SMPR1_SMP_AN13(ADC_SAMPLE_480) |
    ADC_SMPR1_SMP_AN14(ADC_SAMPLE_480) |
    ADC_SMPR1_SMP_AN15(ADC_SAMPLE_480),
  0,                        /* SMPR2 */
  ADC_SQR1_NUM_CH(ADC_NUM_CHANNELS),
  0,
  ADC_SQR3_SQ6_N(ADC_AN33_2)          |
    ADC_SQR3_SQ5_N(ADC_AN33_1)        |
    ADC_SQR3_SQ4_N(ADC_AN33_0)        |
    ADC_SQR3_SQ3_N(ADC_6V_SUPPLY)     |
    ADC_SQR3_SQ2_N(ADC_MAIN_SUPPLY)   |
    ADC_SQR3_SQ1_N(ADC_CURRENT_SENS)
};

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/*
 * ADC streaming callback.
 */
static void adccallback(ADCDriver *adcp, adcsample_t *samples, size_t n) {
  (void)adcp;
  (void)samples;
  (void)n;

  raw_data.main_current = alphabeta_q31(&main_current_filter,
      samples[ADC_CURRENT_SENS_OFFSET], *flen_adc);
  raw_data.main_voltage = alphabeta_q31(&main_voltage_filter,
      samples[ADC_MAIN_VOLTAGE_OFFSET], *flen_adc);
  raw_data.secondary_voltage = alphabeta_q31(&secondary_voltage_filter,
      samples[ADC_6V_OFFSET], *flen_adc);

//  raw_data.main_current = samples[ADC_CURRENT_SENS_OFFSET];
//  raw_data.main_voltage = samples[ADC_MAIN_VOLTAGE_OFFSET];
//  raw_data.secondary_voltage = samples[ADC_6V_OFFSET];
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ADCInit_local(void){
  flen_adc = ValueSearch("FLEN_adc");

  adcStart(&ADCD1, &adccfg);
  adcStartConversion(&ADCD1, &adccg, samples, ADC_BUF_DEPTH);
}


