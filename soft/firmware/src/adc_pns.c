#include "ch.h"
#include "hal.h"

#include "adc_pns.h"
#include "message.h"
#include "main.h"
#include "i2c.h"
#include "imu.h"
#include "dsp.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern LogItem log_item;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define DEFAULT_CURRENT_COEFF  1912   // коэффициент пересчета из условных единиц в амперы для саломёта -- 37, для машинки -- 1912
#define DEFAULT_CURRENT_OFFSET 16   // смещение нуля датчика тока в единицах АЦП
#define DEFAULT_VOLTAGE_COEFF  1022 // коэффициент пересчета из условных единиц в децывольты

#define ADC_NUM_CHANNELS      6
#define ADC_BUF_DEPTH         1

/* человекочитабельные названия каналов */
#define ADC_CURRENT_SENS  ADC_CHANNEL_IN10
#define ADC_MAIN_SUPPLY   ADC_CHANNEL_IN11
#define ADC_6V_SUPPLY     ADC_CHANNEL_IN12
#define ADC_AN33_0        ADC_CHANNEL_IN13
#define ADC_AN33_1        ADC_CHANNEL_IN14
#define ADC_AN33_2        ADC_CHANNEL_IN15

// где лежат текущие значения АЦП
#define ADC_CURRENT_SENS_OFFSET  (ADC_CHANNEL_IN10 - 10)
#define ADC_MAIN_SUPPLY_OFFSET   (ADC_CHANNEL_IN11 - 10)
#define ADC_6V_SUPPLY_OFFSET     (ADC_CHANNEL_IN12 - 10)
#define ADC_AN33_0_OFFSET        (ADC_CHANNEL_IN13 - 10)
#define ADC_AN33_1_OFFSET        (ADC_CHANNEL_IN14 - 10)
#define ADC_AN33_2_OFFSET        (ADC_CHANNEL_IN15 - 10)

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

static uint16_t cal_CurrentCoeff  = DEFAULT_CURRENT_COEFF;
static uint16_t cal_CurrentOffset = DEFAULT_CURRENT_OFFSET;
static uint16_t cal_VoltageCoeff  = DEFAULT_VOLTAGE_COEFF;

static ADCConfig adccfg; // для STM32 -- должна быть пустышка

static adcsample_t samples[ADC_NUM_CHANNELS * ADC_BUF_DEPTH];

/*
 * ADC streaming callback.
 */
static void adccallback(ADCDriver *adcp, adcsample_t *samples, size_t n) {
  (void)adcp;
  (void)samples;
  (void)n;
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
  (void)adcp;
  (void)err;
  chSysHalt();
}

/*
 * ADC conversion group.
 */
static const ADCConversionGroup adccg = {
  TRUE,
  ADC_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
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
  (ADC_SQR3_SQ6_N(ADC_AN33_2)         | ADC_SQR3_SQ5_N(ADC_AN33_1) |
      ADC_SQR3_SQ4_N(ADC_AN33_0)      | ADC_SQR3_SQ3_N(ADC_6V_SUPPLY) |
      ADC_SQR3_SQ2_N(ADC_MAIN_SUPPLY) | ADC_SQR3_SQ1_N(ADC_CURRENT_SENS))
};

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/* Поток для запроса данных АЦП по таймеру */
static WORKING_AREA(PollADCThreadWA, 256);
static msg_t PollADCThread(void *arg){
  chRegSetThreadName("PollADC");
  (void)arg;

  while(TRUE){
    chThdSleepMilliseconds(20);
    raw_data.main_current = samples[ADC_CURRENT_SENS_OFFSET];
    raw_data.main_voltage = samples[ADC_MAIN_SUPPLY_OFFSET];
    log_item.main_current = (uint16_t)((__USAT(raw_data.main_current - cal_CurrentOffset, 15) * 1000) / cal_CurrentCoeff);
    uint16_t voltage = (raw_data.main_voltage * 100) / cal_VoltageCoeff;
    log_item.main_voltage = (uint8_t)__USAT(voltage, 8);
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ADCInit_pns(void){

  adcStart(&ADCD1, &adccfg);
  adcStartConversion(&ADCD1, &adccg, samples, ADC_BUF_DEPTH);

  //"TODO: Read settings from EEPROM here"
  cal_CurrentCoeff  = DEFAULT_CURRENT_COEFF;
  cal_CurrentOffset = DEFAULT_CURRENT_OFFSET;
  cal_VoltageCoeff  = DEFAULT_VOLTAGE_COEFF;

  chThdCreateStatic(PollADCThreadWA,
          sizeof(PollADCThreadWA),
          NORMALPRIO,
          PollADCThread,
          NULL);
}


