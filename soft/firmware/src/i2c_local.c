#include "uav.h"

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
//extern uint32_t GlobalFlags;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* interface #2 */
static const I2CConfig i2cfg2 = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
//    100000,
//    STD_DUTY_CYCLE
//    320000,
//    FAST_DUTY_CYCLE_16_9,
};

static i2cflags_t flags;

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
void I2CInitLocal(void){
  i2cStart(&I2CD2, &i2cfg2);
  ParametersInit(); /* read parameters from EEPROM via I2C*/
}

/**
 * transaction wrapper
 */
msg_t i2c_transmit(i2caddr_t addr, const uint8_t *txbuf, size_t txbytes,
                   uint8_t *rxbuf, size_t rxbytes){
  msg_t status = RDY_OK;

  i2cAcquireBus(&I2CD2);
  status = i2cMasterTransmitTimeout(&I2CD2, addr, txbuf, txbytes, rxbuf, rxbytes, MS2ST(6));
  i2cReleaseBus(&I2CD2);
  flags = i2cGetErrors(&I2CD2);
  chDbgAssert(status == RDY_OK, "i2c_transmit(), #1", "error in driver");
//  if (status == RDY_TIMEOUT){
//    i2cStop(&I2CD2);
//    chThdSleepMilliseconds(1);
//    i2cStart(&I2CD2, &i2cfg2);
//    setGlobalFlag(I2C_RESTARTED_FLAG);
//    return status;
//  }
  return status;
}

/**
 * transaction wrapper
 */
msg_t i2c_receive(i2caddr_t addr, uint8_t *rxbuf, size_t rxbytes){
  msg_t status = RDY_OK;

  i2cAcquireBus(&I2CD2);
  status = i2cMasterReceiveTimeout(&I2CD2, addr, rxbuf, rxbytes, MS2ST(6));
  i2cReleaseBus(&I2CD2);
  flags = i2cGetErrors(&I2CD2);
  chDbgAssert(status == RDY_OK, "i2c_transmit(), #1", "error in driver");
//  if (status == RDY_TIMEOUT){
//    i2cStop(&I2CD2);
//    chThdSleepMilliseconds(1);
//    i2cStart(&I2CD2, &i2cfg2);
//    setGlobalFlag(I2C_RESTARTED_FLAG);
//    return status;
//  }
  return status;
}
