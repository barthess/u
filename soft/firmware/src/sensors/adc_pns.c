#include "ch.h"
#include "hal.h"

#include "adc_pns.h"
#include "message.h"
#include "main.h"
#include "imu.h"
#include "dsp.h"
#include "link.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern CompensatedData comp_data;
extern mavlink_sys_status_t mavlink_sys_status_struct;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define DEFAULT_CURRENT_COEFF     1912   // коэффициент пересчета из условных единиц в амперы для саломёта -- 37, для машинки -- 1912
#define DEFAULT_CURRENT_OFFSET    16   // смещение нуля датчика тока в единицах АЦП
#define DEFAULT_VOLTAGE_COEFF     1022 // коэффициент пересчета из условных единиц в децывольты

#define ADC_NUM_CHANNELS          6
#define ADC_BUF_DEPTH             1

/* человекочитабельные названия каналов */
#define ADC_CURRENT_SENS          ADC_CHANNEL_IN10
#define ADC_MAIN_SUPPLY           ADC_CHANNEL_IN11
#define ADC_6V_SUPPLY             ADC_CHANNEL_IN12
#define ADC_AN33_0                ADC_CHANNEL_IN13
#define ADC_AN33_1                ADC_CHANNEL_IN14
#define ADC_AN33_2                ADC_CHANNEL_IN15

// где лежат текущие значения АЦП
#define ADC_CURRENT_SENS_OFFSET   (ADC_CHANNEL_IN10 - 10)
#define ADC_MAIN_SUPPLY_OFFSET    (ADC_CHANNEL_IN11 - 10)
#define ADC_6V_SUPPLY_OFFSET      (ADC_CHANNEL_IN12 - 10)
#define ADC_AN33_0_OFFSET         (ADC_CHANNEL_IN13 - 10)
#define ADC_AN33_1_OFFSET         (ADC_CHANNEL_IN14 - 10)
#define ADC_AN33_2_OFFSET         (ADC_CHANNEL_IN15 - 10)

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

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

/* пересчет из условных единиц АЦП в mV */
uint16_t get_comp_secondary_voltage(uint16_t raw){
  uint32_t v = 6200; // такое количество милливольт
  uint32_t adc = 770;// приходится на такое количество условных единиц
  return (uint16_t)(((uint32_t)raw * v) / adc);
}

/* пересчет из условных единиц в сантиамперы */
uint16_t get_comp_main_current(uint16_t raw){
  uint16_t A = (raw - DEFAULT_CURRENT_OFFSET) * DEFAULT_CURRENT_COEFF;
  return A * 100;
}

/* Поток для запроса данных АЦП по таймеру */
static WORKING_AREA(PollADCThreadWA, 256);
static msg_t PollADCThread(void *arg){
  chRegSetThreadName("PollADC");
  (void)arg;

  while(TRUE){
    chThdSleepMilliseconds(20);
    raw_data.main_current = samples[ADC_CURRENT_SENS_OFFSET];
    raw_data.main_voltage = samples[ADC_MAIN_SUPPLY_OFFSET];
    raw_data.secondary_voltage = samples[ADC_6V_SUPPLY_OFFSET];

    comp_data.main_current = get_comp_main_current(raw_data.main_current);
    comp_data.secondary_voltage = get_comp_secondary_voltage(raw_data.secondary_voltage);

    mavlink_sys_status_struct.battery_remaining = 86;
    mavlink_sys_status_struct.current_battery   = comp_data.main_current;
    mavlink_sys_status_struct.voltage_battery   = comp_data.secondary_voltage;
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

  chThdCreateStatic(PollADCThreadWA,
          sizeof(PollADCThreadWA),
          NORMALPRIO,
          PollADCThread,
          NULL);
}


