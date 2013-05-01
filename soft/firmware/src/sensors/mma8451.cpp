#include "main.h"
#include "global_flags.h"
#include "mma8451.hpp"
#include "sensors.hpp"
#include "message.hpp"
#include "param_registry.hpp"
#include "misc_math.hpp"
#include "vector3d.hpp"

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
extern mavlink_raw_imu_t mavlink_out_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_out_scaled_imu_struct;
extern CompensatedData comp_data;
extern ParamRegistry param_registry;

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
 *
 */
void MMA8451::update_stillness(float *result){
  float cross[3];
  float filtered[3];
  float modulus_cross;
  float modulus_delta;
  uint32_t i = 0;

  /* update array of filters */
  for (i=0; i<3; i++)
    filtered[i] = abeta[i].update(result[i], *still_flen);

  /* calculate differences between vectors */
  vector3d_cross(result, filtered, cross);
  modulus_cross = vector3d_modulus(cross);
  modulus_delta = vector3d_modulus(result) - vector3d_modulus(filtered);

  if ((fabsf(modulus_delta) > *still_thr) || (fabsf(modulus_cross) > *still_thr))
    immobile = false;
}

/**
 *
 */
void MMA8451::pickle(float *result, uint32_t still_msk) {
  (void)still_msk;
  int32_t raw[3];

  raw[0] = complement2signed(rxbuf[1], rxbuf[2]);
  raw[1] = complement2signed(rxbuf[3], rxbuf[4]);
  raw[2] = complement2signed(rxbuf[5], rxbuf[6]);

  /* convert to NUE coordinate system */
  sort3(raw, *sortmtrx);
  raw[0] *= *xpol;
  raw[1] *= *ypol;
  raw[2] *= *zpol;

  mavlink_out_raw_imu_struct.xacc = raw[0];
  mavlink_out_raw_imu_struct.yacc = raw[1];
  mavlink_out_raw_imu_struct.zacc = raw[2];

  comp_data.acc_i16[0] = (1000 * (raw[0] + *xoffset)) / *xsens;
  comp_data.acc_i16[1] = (1000 * (raw[1] + *yoffset)) / *ysens;
  comp_data.acc_i16[2] = (1000 * (raw[2] + *zoffset)) / *zsens;

  result[0] = comp_data.acc_i16[0] / 1000.0f;
  result[1] = comp_data.acc_i16[1] / 1000.0f;
  result[2] = comp_data.acc_i16[2] / 1000.0f;

  mavlink_out_scaled_imu_struct.xacc = comp_data.acc_i16[0];
  mavlink_out_scaled_imu_struct.yacc = comp_data.acc_i16[1];
  mavlink_out_scaled_imu_struct.zacc = comp_data.acc_i16[2];
}

/**
 *
 */
void MMA8451::hw_init_full(void) {
   /* Помни о том, что большинство конфигурационных регистров нельзя менять
   в активном режиме, надо сначала свалить девайс в STANDBY. */

  // TODO: run autodiagnostic

  txbuf[0] = ACCEL_WHOAMI;
  transmit(txbuf, 1, rxbuf, 1);
  chDbgAssert(rxbuf[0] == ACCEL_WHOAMI_VALUE, "init_mma8451(), #1",
                                    "accelerometer did not respond");

  txbuf[0] = ACCEL_CTRL_REG2;
  txbuf[1] = 0b100000; //Reset
  transmit(txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(8);

  txbuf[0] = ACCEL_CTRL_REG1;
  txbuf[1] = 0b0; //set standby to allow configure device
  transmit(txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(2);

  txbuf[0] = ACCEL_XYZ_DATA_CFG;
  txbuf[1] = (uint8_t)(ACCEL_SENS >> 2);
  transmit(txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(2);

  txbuf[0] = ACCEL_CTRL_REG2;
  txbuf[1] = 0b10;    // High Resolution
  txbuf[2] = 0b10;    // Interrupt active high
  //txbuf[3] = 0b01;  // Interrupt on data ready
  txbuf[3] = 0;       // disable interrupts
  transmit(txbuf, 4, rxbuf, 0);
  chThdSleepMilliseconds(2);

  txbuf[0] = ACCEL_CTRL_REG1;
  txbuf[1] = 0b10101; //200Hz, low noice, active
  //txbuf[1] = 0b11101; //100Hz, low noice, active
  //txbuf[1] = 0b11001; //100Hz, normal noice, active
  //txbuf[1] = 0b100101; //50Hz, low noice, active
  transmit(txbuf, 2, rxbuf, 0);
}


void MMA8451::hw_init_fast(void) {
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 *
 */
MMA8451::MMA8451(I2CDriver* i2cdp, i2caddr_t addr):
I2CSensor(i2cdp, addr)
{
  ready = false;
  immobile = false;
}

/**
 *
 */
void MMA8451::start(void) {
  if (need_full_init())
    hw_init_full();
  else
    hw_init_fast();

  xoffset   = (const int32_t*)param_registry.valueSearch("ACC_xoffset");
  yoffset   = (const int32_t*)param_registry.valueSearch("ACC_yoffset");
  zoffset   = (const int32_t*)param_registry.valueSearch("ACC_zoffset");

  xpol      = (const int32_t*)param_registry.valueSearch("ACC_xpol");
  ypol      = (const int32_t*)param_registry.valueSearch("ACC_ypol");
  zpol      = (const int32_t*)param_registry.valueSearch("ACC_zpol");

  xsens     = (const uint32_t*)param_registry.valueSearch("ACC_xsens");
  ysens     = (const uint32_t*)param_registry.valueSearch("ACC_ysens");
  zsens     = (const uint32_t*)param_registry.valueSearch("ACC_zsens");

  sortmtrx  = (const uint32_t*)param_registry.valueSearch("ACC_sortmtrx");
  still_thr = (const float*)param_registry.valueSearch("ACC_still_thr");
  still_flen= (const int32_t*)param_registry.valueSearch("ACC_still_flen");

  ready = true;
}

/**
 *
 */
void MMA8451::stop(void) {
  ready = false;
}

/**
 * return true if device was immobile still last call of this function
 */
bool MMA8451::still(void){
  bool tmp;

  chSysLock();
  tmp = immobile;
  immobile = true;
  chSysUnlock();

  return tmp;
}

/**
 *
 */
void MMA8451::update(float *result, uint32_t still_msk){
  chDbgCheck((true == ready), "you must start() this device");
  txbuf[0] = ACCEL_STATUS;
  transmit(txbuf, 1, rxbuf, 7);

  this->pickle(result, still_msk);
  this->update_stillness(result);
}
