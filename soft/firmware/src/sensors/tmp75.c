#include <stdlib.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define tmp75addr 0b1001000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern CompensatedData comp_data;
extern mavlink_scaled_pressure_t  mavlink_scaled_pressure_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[TMP75_RX_DEPTH] = {0x55, 0x55};
static uint8_t txbuf[TMP75_TX_DEPTH] = {0,0};
extern EventSource init_event;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
static WORKING_AREA(PollTmp75ThreadWA, 256);
static msg_t PollTmp75Thread(void *arg){
  chRegSetThreadName("PollTmp75");
  (void)arg;

  struct EventListener self_el;
  chEvtRegister(&init_event, &self_el, INIT_FAKE_EVID);

  while (TRUE) {
    txbuf[0] = 0b00000001; // point to Configuration Register
    /* single measurement start */
    txbuf[1] = 0b10000001; // OS R1 R0 F1 F0 POL TM SD
    i2c_transmit(tmp75addr, txbuf, 2, rxbuf, 0);
    chThdSleepMilliseconds(40); /* wait until measured (datasheet says 37.5ms)*/

    txbuf[0] = 0; // point to temperature register

    if (i2c_transmit(tmp75addr, txbuf, 1, rxbuf, 2) == RDY_OK){
      raw_data.temp_tmp75 = complement2signed(rxbuf[0], rxbuf[1]);
      comp_data.temp_onboard = raw_data.temp_tmp75 / 256;
      mavlink_scaled_pressure_struct.temperature = (int16_t)((100 * (int32_t)raw_data.temp_tmp75) / 256);
    }
    chThdSleepMilliseconds(1000);

    if (chThdSelf()->p_epending & EVENT_MASK(SIGHALT_EVID))
      chThdExit(RDY_OK);
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/*Accessing a particular register on the TMP175 and TMP75
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
additional data is required.*/

void init_tmp75(void){
  txbuf[0] = 0b00000001; // point to Configuration Register
  /* enable autoshutdown, to reduce auto warmup of sensor */
  txbuf[1] = 0b00000001; // OS R1 R0 F1 F0 POL TM SD
  while(i2c_transmit(tmp75addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdCreateStatic(PollTmp75ThreadWA,
          sizeof(PollTmp75ThreadWA),
          I2C_THREADS_PRIO,
          PollTmp75Thread,
          NULL);
  chThdSleepMilliseconds(1);
}

#undef I2CDtmp75
