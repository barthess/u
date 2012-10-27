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
extern const mavlink_system_t mavlink_system_struct;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define PWR_CHECK_PERIOD          20 /* mS */

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
static uint32_t const *bat_cap;       /* battery capacitance in A*mS */
static uint32_t const *bat_fill;      /* battery filling in A*mS */
static uint32_t const *adc_I_b;
static uint32_t const *adc_I_k;
static uint32_t const *adc_sv_gain;   /* secondary voltage gain */
static uint32_t const *adc_mv_gain;   /* main voltage gain */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/* пересчет из условных единиц АЦП в mV */
static uint16_t get_comp_secondary_voltage(uint16_t raw){
  return (uint16_t)(((uint32_t)raw * *adc_sv_gain) / 1000);
}

/* STUB */
//static uint16_t get_comp_main_voltage(uint16_t raw){
//  return (uint16_t)(((uint32_t)raw * *adc_mv_gain) / 1000);
//}

/* пересчет из условных единиц в mA согласно формуле y=kx+b
 * Формула выводится из уравнения прямой
 *
 * y - y1    x - x1
 * ------- = -------
 * y2 - y1   x2 - x1
 *
 *     (x - x1) * (y2 - y1)
 * y = -------------------  + y1
 *            x2 - x1
 *
 * Для того, чтобы воспользоваться ей, нам необходимо снять 2 точки.
 * Для машинки:
 * (АЦП; мА) -- (193;87), (388;200)
 * откуда получается (мА):
 * y = 0.58x + 24.841
 * или (мкА)
 * y = 580x + 24841
 */
static uint32_t get_comp_main_current(uint16_t raw){
  return ((((uint32_t)raw) * *adc_I_k) + *adc_I_b) / 1000;
}

/*
 * Process ADC data.
 */
static WORKING_AREA(PowerKeeperThreadWA, 64);
static msg_t PowerKeeperThread(void *arg){
  chRegSetThreadName("PowerKeeper");
  (void)arg;

  uint32_t start_bat_fill = 0; /* percents */
  uint32_t tmp = 0;

  systime_t time = chTimeNow();     // T0
  while (TRUE) {
    time += MS2ST(PWR_CHECK_PERIOD);              // Next deadline

    if (start_bat_fill != *bat_fill){
      start_bat_fill = *bat_fill;
      raw_data.battery_consumed = 0;
    }

    comp_data.main_current = get_comp_main_current(raw_data.main_current);
    comp_data.secondary_voltage = get_comp_secondary_voltage(raw_data.secondary_voltage);

    raw_data.battery_consumed += (comp_data.main_current * PWR_CHECK_PERIOD) / CH_FREQUENCY;

    /* ((mAc) / 3600) * 100    mAc * 100        mAc
     * -------------------- = ------------ = ----------
     *      start             start * 3600   36 * start
     */
    tmp = raw_data.battery_consumed / (36 * *bat_cap);
    if (tmp < start_bat_fill)
      mavlink_sys_status_struct.battery_remaining = start_bat_fill - tmp;
    else
      mavlink_sys_status_struct.battery_remaining = 0;
    mavlink_sys_status_struct.current_battery   = (uint16_t)(comp_data.main_current / 10);
    mavlink_sys_status_struct.voltage_battery   = comp_data.secondary_voltage;
    log_write_schedule(MAVLINK_MSG_ID_SYS_STATUS, NULL, 0);

    chThdSleepUntil(time);
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void PwrMgmtInit(void){
  bat_cap  = ValueSearch("BAT_cap");
  bat_fill = ValueSearch("BAT_fill");

  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    adc_I_k = ValueSearch("ADC_car_I_k");
    adc_I_b = ValueSearch("ADC_car_I_b");
  }
  else{
    adc_I_k = ValueSearch("ADC_plane_I_k");
    adc_I_b = ValueSearch("ADC_plane_I_b");
  }

  adc_sv_gain  = ValueSearch("ADC_SV_gain");
  adc_mv_gain  = ValueSearch("ADC_MV_gain");

  chThdCreateStatic(PowerKeeperThreadWA,
          sizeof(PowerKeeperThreadWA),
          NORMALPRIO,
          PowerKeeperThread,
          NULL);
}


