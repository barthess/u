#include <stdlib.h>
#include <math.h>

#include "uav.h"
#include "geometry.hpp"
#include "itg3200.hpp"
#include "param_registry.hpp"
#include "message.hpp"
#include "sensors.hpp"
#include "misc_math.hpp"
#include "timekeeping.hpp"

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
extern CompensatedData comp_data;
extern ParamRegistry param_registry;

extern mavlink_raw_imu_t mavlink_out_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_out_scaled_imu_struct;

uint32_t GyroUpdatePeriodUs = 10000; /* uS */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Получение приращения угла исходя из угловой скорости и временем между выборками
 */
static float get_degrees(float raw){
  float t = (float)GyroUpdatePeriodUs / 1000000.0f;
  return raw * ((t * 180) / PI);
}

/**
 *
 */
void ITG3200::pickle(void){
  int32_t raw[3];
  uint32_t i = 0;

  comp_data.gyrotemp  = complement2signed(rxbuf[0], rxbuf[1]);
  raw[0] = complement2signed(rxbuf[2], rxbuf[3]);
  raw[1] = complement2signed(rxbuf[4], rxbuf[5]);
  raw[2] = complement2signed(rxbuf[6], rxbuf[7]);
  sort3(raw, *sortmtrx);

  /* adjust rotation direction */
  raw[0] *= *xpol;
  raw[1] *= *ypol;
  raw[2] *= *zpol;

  /* fill debug struct */
  mavlink_out_raw_imu_struct.xgyro = raw[0];
  mavlink_out_raw_imu_struct.ygyro = raw[1];
  mavlink_out_raw_imu_struct.zgyro = raw[2];
  mavlink_out_raw_imu_struct.time_usec = pnsGetTimeUnixUsec();

  /* now get angular rate in rad/sec */
  comp_data.gyro[0] = fdeg2rad(((float)raw[0] - *x_offset) / *xsens);
  comp_data.gyro[1] = fdeg2rad(((float)raw[1] - *y_offset) / *ysens);
  comp_data.gyro[2] = fdeg2rad(((float)raw[2] - *z_offset) / *zsens);

  /* calc summary angle for debug purpose */
  for(i=0; i<3; i++)
    comp_data.gyro_angle[i] += get_degrees(comp_data.gyro[i]);

  /* fill scaled debug struct */
//  mavlink_out_scaled_imu_struct.xgyro = (int16_t)(10 * comp_data.xgyro_angle);
//  mavlink_out_scaled_imu_struct.ygyro = (int16_t)(10 * comp_data.ygyro_angle);
//  mavlink_out_scaled_imu_struct.zgyro = (int16_t)(10 * comp_data.zgyro_angle);
  mavlink_out_scaled_imu_struct.xgyro = (int16_t)(comp_data.gyro[0] * 1000);
  mavlink_out_scaled_imu_struct.ygyro = (int16_t)(comp_data.gyro[1] * 1000);
  mavlink_out_scaled_imu_struct.zgyro = (int16_t)(comp_data.gyro[2] * 1000);
  mavlink_out_scaled_imu_struct.time_boot_ms = TIME_BOOT_MS;
}

/**
 *
 */
ITG3200::ITG3200(I2CDriver *i2cdp, i2caddr_t addr):
I2CSensor(i2cdp, addr)
{
  ready = false;
}

void ITG3200::stop(void){
  // TODO: power down sensor here
  ready = false;
}

/**
 *
 */
void ITG3200::update(void){
  chDbgCheck((true == ready), "not ready");
  txbuf[0] = GYRO_OUT_DATA;
  transmit(txbuf, 1, rxbuf, 8);
  this->pickle();
}

/**
 *
 */
void ITG3200::hw_init_fast(void){
}

/**
 *
 */
void ITG3200::hw_init_full(void){

  txbuf[0] = GYRO_PWR_MGMT;
  txbuf[1] = 0b1000000; /* soft reset */
  transmit(txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(60);

//  txbuf[0] = GYRO_WHOAMI;
//  i2c_transmit(itg3200addr, txbuf, 1, rxbuf, 2);
//  chDbgCheck((rxbuf[0] >> 1) == GYRO_WHOAMI_VAL, "Wrong whoami respose");
//  chThdSleepMilliseconds(5);

  txbuf[0] = GYRO_PWR_MGMT;
  txbuf[1] = 1; /* select clock source */
  transmit(txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(5);

  txbuf[0] = GYRO_SMPLRT_DIV;
  txbuf[1] = 9; /* sample rate. Approximatelly (1000 / (9 + 1)) = 100Hz*/
  txbuf[2] = GYRO_DLPF_CFG | GYRO_FS_SEL; /* диапазон измерений и частота среза внутреннего фильтра */
  //txbuf[3] = 0b00110001; /* configure and enable interrupts */
  txbuf[3] = 0b00010001; /* configure and enable interrupts */
  transmit(txbuf, 4, rxbuf, 0);
}

/**
 *
 */
void ITG3200::start(void){

  for (int i=0; i<3; i++)
    comp_data.gyro_angle[i] = 0;

  if (need_full_init()){
    hw_init_full();
  }
  else{
    hw_init_fast();
  }

  xsens     = (const float*)param_registry.valueSearch("GYRO_xsens");
  ysens     = (const float*)param_registry.valueSearch("GYRO_ysens");
  zsens     = (const float*)param_registry.valueSearch("GYRO_zsens");

  xpol      = (const int32_t*)param_registry.valueSearch("GYRO_xpol");
  ypol      = (const int32_t*)param_registry.valueSearch("GYRO_ypol");
  zpol      = (const int32_t*)param_registry.valueSearch("GYRO_zpol");

  x_offset  = (const float*)param_registry.valueSearch("GYRO_x_offset");
  y_offset  = (const float*)param_registry.valueSearch("GYRO_y_offset");
  z_offset  = (const float*)param_registry.valueSearch("GYRO_z_offset");

  sortmtrx  = (const uint32_t*)param_registry.valueSearch("GYRO_sortmtrx");

  ready = true;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

