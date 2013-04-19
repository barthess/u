#include "uav.h"
#include "mma8451.hpp"
#include "sensors.hpp"
#include "message.hpp"
#include "param_registry.hpp"
#include "misc_math.hpp"

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
MMA8451::MMA8451(I2CDriver* i2cdp, i2caddr_t addr):
I2CSensor(i2cdp, addr)
{
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
  still_thr = (const uint32_t*)param_registry.valueSearch("IMU_still_thr");

  ready = false;
}


void MMA8451::update(void) {
  chDbgCheck((true == ready), "you must start() this device");
  txbuf[0] = ACCEL_STATUS;
  transmit(txbuf, 1, rxbuf, 7);
  this->pickle();
}

/**
 *
 */
void MMA8451::start(void) {
  if (need_full_init())
    hw_init_full();
  else
    hw_init_fast();

  ready = true;
}

/**
 *
 */
void MMA8451::stop(void) {
  ready = false;
}

/**
 *
 */
void MMA8451::pickle(void) {
  int32_t raw[3];
  int32_t Acc[3];

  raw[0] = complement2signed(rxbuf[1], rxbuf[2]);
  raw[1] = complement2signed(rxbuf[3], rxbuf[4]);
  raw[2] = complement2signed(rxbuf[5], rxbuf[6]);
  sorti_3values(raw, Acc, *sortmtrx);

  mavlink_out_raw_imu_struct.xacc = Acc[0];
  mavlink_out_raw_imu_struct.yacc = Acc[1];
  mavlink_out_raw_imu_struct.zacc = Acc[2];

  Acc[0] *= *xpol;
  Acc[1] *= *ypol;
  Acc[2] *= *zpol;

  comp_data.xacc = (1000 * (Acc[0] + *xoffset)) / *xsens;
  comp_data.yacc = (1000 * (Acc[1] + *yoffset)) / *ysens;
  comp_data.zacc = (1000 * (Acc[2] + *zoffset)) / *zsens;

  mavlink_out_scaled_imu_struct.xacc = comp_data.xacc;
  mavlink_out_scaled_imu_struct.yacc = comp_data.yacc;
  mavlink_out_scaled_imu_struct.zacc = comp_data.zacc;
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
  txbuf[1] = 0b10; //High Resolution
  txbuf[2] = 0b10; //Interrupt active high
  txbuf[3] = 0b01; //Interrupt on data ready
  transmit(txbuf, 4, rxbuf, 0);
  chThdSleepMilliseconds(2);

  txbuf[0] = ACCEL_CTRL_REG1;
  txbuf[1] = 0b11101; //100Hz, low noice, active
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


