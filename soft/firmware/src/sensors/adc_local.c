#include <math.h>

#include "uav.h"

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
#define ADC_MAIN_VOLTAGE_OFFSET   (ADC_CHANNEL_IN11 - 10)
#define ADC_6V_OFFSET             (ADC_CHANNEL_IN12 - 10)
#define ADC_AN33_0_OFFSET         (ADC_CHANNEL_IN13 - 10)
#define ADC_AN33_1_OFFSET         (ADC_CHANNEL_IN14 - 10)
#define ADC_AN33_2_OFFSET         (ADC_CHANNEL_IN15 - 10)

#define PWR_CHECK_PERIOD          20 /* mS */

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
static uint32_t *bat_cap;       /* battery capacitance in A*mS */
static uint32_t *bat_fill;      /* battery filling in A*mS */
static uint32_t *adc_i_gain;    // коэффициент пересчета из условных единиц в амперы для саломёта -- 37, для машинки -- 1912
static uint32_t *adc_i_offset;  // смещение нуля датчика тока в единицах АЦП
static uint32_t *adc_sv_gain;   /* secondary voltage gain */
static uint32_t *adc_mv_gain;   /* main voltage gain */
static uint32_t *flen_adc;      /* length of filter for ADC */

static ADCConfig adccfg; // для STM32 -- должна быть пустышка

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
  0,                        /* CR2 */
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

/* пересчет из условных единиц АЦП в mV */
uint16_t get_comp_secondary_voltage(uint16_t raw){
  return (uint16_t)(((uint32_t)raw * *adc_sv_gain) / 1000);
}

/* STUB */
uint16_t get_comp_main_voltage(uint16_t raw){
  return (uint16_t)(((uint32_t)raw * *adc_mv_gain) / 1000);
}

/* пересчет из условных единиц в mA */
uint32_t get_comp_main_current(uint16_t raw){
  return ((raw - *adc_i_offset) * 1000) / *adc_i_gain;
}

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

/* Поток для запроса данных АЦП по таймеру */
static WORKING_AREA(PowerKeeperThreadWA, 128);
static msg_t PowerKeeperThread(void *arg){
  chRegSetThreadName("PowerKeeper");
  (void)arg;
  raw_data.battery_remaining = *bat_fill * 1000;

  systime_t time = chTimeNow();     // T0
  while (TRUE) {
    time += MS2ST(PWR_CHECK_PERIOD);              // Next deadline

    comp_data.main_current = get_comp_main_current(raw_data.main_current);
    comp_data.secondary_voltage = get_comp_secondary_voltage(raw_data.secondary_voltage);

    *bat_fill -= (comp_data.main_current * PWR_CHECK_PERIOD) / 1000;

    mavlink_sys_status_struct.battery_remaining = (*bat_fill * 100) / *bat_cap;
    mavlink_sys_status_struct.current_battery   = (uint16_t)(comp_data.main_current / 10);
    mavlink_sys_status_struct.voltage_battery   = comp_data.secondary_voltage;

    chThdSleepUntil(time);
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ADCInit_local(void){
  bat_cap  = ValueSearch("BAT_cap");
  bat_fill = ValueSearch("BAT_fill");

  adc_i_offset = ValueSearch("ADC_I_offset");
  adc_i_gain   = ValueSearch("ADC_I_gain");
  flen_adc     = ValueSearch("FLEN_adc");
  adc_sv_gain  = ValueSearch("ADC_SV_gain");
  adc_mv_gain  = ValueSearch("ADC_MV_gain");

  adcStart(&ADCD1, &adccfg);
  adcStartConversion(&ADCD1, &adccg, samples, ADC_BUF_DEPTH);

  chThdCreateStatic(PowerKeeperThreadWA,
          sizeof(PowerKeeperThreadWA),
          NORMALPRIO,
          PowerKeeperThread,
          NULL);
}


