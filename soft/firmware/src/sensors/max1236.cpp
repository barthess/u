#include "uav.h"

#include "sensors.hpp"
#include "message.hpp"
#include "param_registry.hpp"
#include "misc_math.hpp"
#include "max1236.hpp"
#include "dsp.hpp"
#include "timekeeping.hpp"
#include "airspeed.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/**сонар выдает Vcc/1024 вольт на см
 * разрешающая способность АЦП Vcc/4096
 * Итого: для получения высоты в см надо полученный результат поделить на 4 */
#define SONAR_COEF 4

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern CompensatedData comp_data;
extern ParamRegistry param_registry;

extern mavlink_raw_pressure_t     mavlink_out_raw_pressure_struct;
extern mavlink_scaled_pressure_t  mavlink_out_scaled_pressure_struct;
extern mavlink_vfr_hud_t          mavlink_out_vfr_hud_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static alphabeta_instance_q31 press_diff_filter;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */


MAX1236::MAX1236(I2CDriver* i2cdp, i2caddr_t addr):
I2CSensor(i2cdp, addr)
{
  ready = false;
}


/** Опрос max1236
 * после настройки достаточно просто читать из него данные, по 2 байта на канал
 * после отправки запроса АЦП занимает линию примерно на 8.3uS, после чего
 * отдает результат. Как только мастер вычитал нужное количество байт - дает
 * в шину STOP.
 * При частоте 100кГц на вычитывание 4 значений уйдет примерно:
 * 10 * (4 * 2 * 8) + 8.3 * 4 = 673.2 uS
 */
void MAX1236::update(void) {
  q31_t press;
  uint16_t sonar;
  const uint16_t rest = 10000; // constant for compesate filter flyback delay

  chDbgCheck((true == ready), "you must start() this device");

  receive(rxbuf, MAX1236_RX_DEPTH);

  press = ((rxbuf[0] & 0xF) << 8) + rxbuf[1];
  sonar = ((rxbuf[2] & 0xF) << 8) + rxbuf[3];

  press = alphabeta_q31(&press_diff_filter, press + rest, *flen_pres_dyn) - rest;

  raw_data.pressure_dynamic = press;
  raw_data.altitude_sonar = sonar;

  mavlink_out_vfr_hud_struct.airspeed = calc_air_speed(raw_data.pressure_dynamic);

  mavlink_out_raw_pressure_struct.press_diff1 = raw_data.pressure_dynamic;
  mavlink_out_raw_pressure_struct.temperature = raw_data.temp_tmp75;
  mavlink_out_raw_pressure_struct.time_usec = pnsGetTimeUnixUsec();

  mavlink_out_scaled_pressure_struct.time_boot_ms = TIME_BOOT_MS;

  comp_data.air_speed = (uint16_t)(1000 * mavlink_out_vfr_hud_struct.airspeed);
}

/**
 *
 */
void MAX1236::start(void) {
  if (need_full_init())
    hw_init_full();
  else
    hw_init_fast();

  flen_pres_dyn = (const uint32_t*)param_registry.valueSearch("FLEN_pres_dyn");

  ready = true;
}

/**
 *
 */
void MAX1236::stop(void) {
  ready = false;
}

/**
 *
 */
void MAX1236::pickle(void) {
}

/**
 *
 */
void MAX1236::hw_init_full(void) {
  /**
  * see datasheet on page 13 how to initialize ADC
  */
  txbuf[0] = 0b11110011;
  txbuf[1] = 0b00000101;
  transmit(txbuf, 2, rxbuf, 0);
}


void MAX1236::hw_init_fast(void) {
}

