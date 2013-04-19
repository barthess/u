#include "uav.h"
#include "global_flags.h"
#include "i2c_local.hpp"

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
extern GlobalFlags_t GlobalFlags;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* interface #2 */
static const I2CConfig i2cfg2 = {
    OPMODE_I2C,
//    350000,
//    FAST_DUTY_CYCLE_2,
    400000,
    FAST_DUTY_CYCLE_2,
//    100000,
//    STD_DUTY_CYCLE
//    320000,
//    FAST_DUTY_CYCLE_16_9,
};

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
  setGlobalFlag(GlobalFlags.i2c_ready);
}

I2CSensor::I2CSensor(I2CDriver *i2cdp, i2caddr_t addr):
  i2cdp(i2cdp),
  addr(addr)
{
  return;
}

/**
 * transaction wrapper
 */
msg_t I2CSensor::transmit(const uint8_t *txbuf, size_t txbytes,
                                 uint8_t *rxbuf, size_t rxbytes){
  msg_t status = RDY_OK;
  i2cflags_t flags;

  i2cAcquireBus(this->i2cdp);
  status = i2cMasterTransmitTimeout(this->i2cdp, this->addr, txbuf, txbytes, rxbuf, rxbytes, MS2ST(6));
  i2cReleaseBus(this->i2cdp);
  flags = i2cGetErrors(this->i2cdp);
  chDbgAssert((status == RDY_OK) && (flags == I2CD_NO_ERROR),
              "i2c_transmit(), #1", "error in driver");
//  if (status == RDY_TIMEOUT){
//    i2cStop(i2cdp);
//    chThdSleepMilliseconds(1);
//    i2cStart(i2cdp, &i2cfg);
//    setGlobalFlag(I2C_RESTARTED_FLAG);
//    return status;
//  }
  return status;
}

/**
 * transaction wrapper
 */
msg_t I2CSensor::receive(uint8_t *rxbuf, size_t rxbytes){
  msg_t status = RDY_OK;
  i2cflags_t flags;

  i2cAcquireBus(this->i2cdp);
  status = i2cMasterReceiveTimeout(this->i2cdp, this->addr, rxbuf, rxbytes, MS2ST(6));
  i2cReleaseBus(this->i2cdp);
  flags = i2cGetErrors(this->i2cdp);
  chDbgAssert((status == RDY_OK) && (flags == I2CD_NO_ERROR),
              "i2c_transmit(), #1", "error in driver");
//  if (status == RDY_TIMEOUT){
//    i2cStop(i2cdp);
//    chThdSleepMilliseconds(1);
//    i2cStart(i2cdp, &i2cfg);
//    setGlobalFlag(I2C_RESTARTED_FLAG);
//    return status;
//  }
  return status;
}
