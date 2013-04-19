#include <stdlib.h>

#include "uav.h"
#include "sensors.hpp"
#include "message.hpp"
#include "tmp75.hpp"
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
extern RawData raw_data;
extern CompensatedData comp_data;
extern mavlink_scaled_pressure_t  mavlink_out_scaled_pressure_struct;

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
void TMP75::pickle(void){
  raw_data.temp_tmp75 = complement2signed(rxbuf[0], rxbuf[1]);
  comp_data.temp_onboard = (int16_t)((100 * (int32_t)raw_data.temp_tmp75) / 256);
  mavlink_out_scaled_pressure_struct.temperature = comp_data.temp_onboard;
}

/**
 *
 */
void TMP75::hw_init_fast(void){
}

/**
 *
 */
void TMP75::hw_init_full(void){
  txbuf[0] = 0b00000001; // point to Configuration Register
  /* enable autoshutdown, to reduce auto warmup of sensor */
  txbuf[1] = 0b00000001; // OS R1 R0 F1 F0 POL TM SD
  transmit(txbuf, 2, rxbuf, 0);
}

/**
 *
 */
TMP75::TMP75(I2CDriver *i2cdp, i2caddr_t addr):
I2CSensor(i2cdp, addr)
{
  ready = false;
}

/**
 *
 */
void TMP75::start(void){
  if (need_full_init())
    hw_init_full();
  else
    hw_init_fast();

  ready = true;
}

void TMP75::stop(void){
  ready = false;
}

/*
Accessing a particular register on the TMP175 and TMP75
is accomplished by writing the appropriate value to the
Pointer Register. The value for the Pointer Register is the
first byte transferred after the slave address byte with the
R/W bit LOW. Every write operation to the TMP175 and
TMP75 requires a value for the Pointer Register.

When reading from the TMP175 and TMP75, the last value
stored in the Pointer Register by a write operation is used
to determine which register is read by a read operation. To
change the register pointer for a read operation, a new
value must be written to the Pointer Register. This is
accomplished by issuing a slave address byte with the
R/W bit LOW, followed by the Pointer Register Byte. No
additional data is required.
*/
void TMP75::update(void){
  chDbgCheck((true == ready), "you must start() this device");
  txbuf[0] = 1; // point to Configuration Register
  /* single measurement start
   * To reduce autowarmup at low temperature start less accurate measurements
   * to speed up data acquision */
  if (comp_data.temp_onboard < 1000){
    txbuf[1] = 0b10000001; /* OS R1 R0 F1 F0 POL TM SD */
    transmit(txbuf, 2, rxbuf, 0);
    chThdSleepMilliseconds(40);
  }
  else{
    txbuf[1] = 0b11000001;  /* OS R1 R0 F1 F0 POL TM SD */
    transmit(txbuf, 2, rxbuf, 0);
    chThdSleepMilliseconds(150);
  }
  txbuf[0] = 0; // point to temperature register

  transmit(txbuf, 1, rxbuf, 2);

  this->pickle();
}
