#include <math.h>

#include "uav.h"
#include "global_flags.h"
#include "sensors.hpp"
#include "dsp.hpp"
#include "param_registry.hpp"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern ParamRegistry param_registry;

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
static uint32_t const *flen_adc;      /* length of filter for ADC */

static ADCConfig adccfg; // dummy for STM32

static adcsample_t samples[ADC_NUM_CHANNELS * ADC_BUF_DEPTH];

/**/
static AlphaBeta<int32_t> main_current;
static AlphaBeta<int32_t> main_voltage;
static AlphaBeta<int32_t> secondary_voltage;

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

  raw_data.main_current = main_current.update(samples[ADC_CURRENT_SENS_OFFSET], *flen_adc);
  raw_data.main_voltage = main_voltage.update(samples[ADC_MAIN_VOLTAGE_OFFSET], *flen_adc);
  raw_data.secondary_voltage = secondary_voltage.update(samples[ADC_6V_OFFSET], *flen_adc);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ADCInitLocal(void){
  flen_adc = (uint32_t *)param_registry.valueSearch("FLEN_adc");

  adcStart(&ADCD1, &adccfg);
  adcStartConversion(&ADCD1, &adccg, samples, ADC_BUF_DEPTH);
}


