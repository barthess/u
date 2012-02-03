#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "main.h"

#include "eeprom.h"
#include "itg3200.h"
#include "mma8451.h"
#include "tmp75.h"
#include "max1236.h"
#include "bmp085.h"
#include "mag3110.h"

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
extern uint32_t GlobalFlags;
extern EepromFileStream* EepromFile_p;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* interface #2 */
static const I2CConfig i2cfg2 = {
    OPMODE_I2C,
    400000, //100000, //
    FAST_DUTY_CYCLE_16_9, //STD_DUTY_CYCLE, //
};

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void I2CInit_pns(void){

  i2cStart(&I2CD2, &i2cfg2);

  chThdSleepMilliseconds(25); /* wait untill all devices ready */

  /* startups */
  EepromFile_p = EepromOpen();
  init_tmp75();
  init_max1236();
  init_mag3110();
  init_itg3200();
  init_mma8451();
  init_bmp085();
}


/* обертка запускатор транзакции */
msg_t i2c_transmit(i2caddr_t addr, const uint8_t *txbuf, size_t txbytes,
                   uint8_t *rxbuf, size_t rxbytes){
  msg_t status = RDY_OK;
//  i2cflags_t flags = I2CD_NO_ERROR;

  i2cAcquireBus(&I2CD2);
  status = i2cMasterTransmitTimeout(&I2CD2, addr, txbuf, txbytes, rxbuf, rxbytes, MS2ST(6));
  i2cReleaseBus(&I2CD2);
  //chDbgAssert(status == RDY_OK, "i2c_transmit(), #1", "error in driver");
  if (status == RDY_TIMEOUT){
    /* в случае таймаута необходимо перезапустить драйвер */
    i2cStart(&I2CD2, &i2cfg2);
    setGlobalFlag(I2C_RESTARTED);
    return status;
  }
//  if (status == RDY_RESET){
//    flags = I2CD2.errors;
//  }
  return status;
}

/* обертка запускатор транзакции */
msg_t i2c_receive(i2caddr_t addr, uint8_t *rxbuf, size_t rxbytes){
  msg_t status = RDY_OK;
//  i2cflags_t flags = I2CD_NO_ERROR;

  i2cAcquireBus(&I2CD2);
  status = i2cMasterReceiveTimeout(&I2CD2, addr, rxbuf, rxbytes, MS2ST(6));
  i2cReleaseBus(&I2CD2);
  chDbgAssert(status == RDY_OK, "i2c_transmit(), #1", "error in driver");
  if (status == RDY_TIMEOUT){
    /* в случае таймаута необходимо перезапустить драйвер */
    i2cStart(&I2CD2, &i2cfg2);
    setGlobalFlag(I2C_RESTARTED);
    return status;
  }
//  if (status == RDY_RESET){
//    flags = I2CD2.errors;
//  }
  return status;
}
