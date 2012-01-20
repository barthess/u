#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "i2c_pns.h"
#include "tmp75.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define I2CDtmp75 I2CD2
#define tmp75addr 0b1001000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern LogItem log_item;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[TMP75_RX_DEPTH] = {0x55, 0x55};
static uint8_t txbuf[TMP75_TX_DEPTH] = {0,0};

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

  int16_t t_int = 0;
  int16_t t_frac = 0;

  while (TRUE) {
    /* скорость опроса термодатчика надо подбирать в зависимости от разрешения
     * при 12 Bits (0.0625°C) данные обновляются каждые 220 мс*/

    if (i2c_receive(&I2CDtmp75, tmp75addr, rxbuf, 2) == RDY_OK){
      /* Целая часть будет записана в лог и отправлена телеметрией */
      log_item.temp_onboard = rxbuf[0];

      /* Более точное значение (сотые доли градуса) */
      t_int = rxbuf[0] * 100;
      t_frac = (rxbuf[1] * 100) >> 8;
      raw_data.temp_tmp75 = t_int + t_frac;
    }
    chThdSleepMilliseconds(250);
  }
  return 0;
}


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

/**
 * настроить разрешение на 12 бит
 * - записать в указательный регистр адрес конфигурационного регистра,
 * в этой же последовательности отправить байт настроек
 * - записать в указательный регистр адрес температурного регистра
 * */
void init_tmp75(void){
  txbuf[0] = 0b00000001; // point to Configuration Register
  txbuf[1] = 0b01100000; // OS R1 R0 F1 F0 POL TM SD
  while(i2c_transmit(&I2CDtmp75, tmp75addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  txbuf[0] = 0; // point to temperature register
  while(i2c_transmit(&I2CDtmp75, tmp75addr, txbuf, 1, rxbuf, 0) != RDY_OK)
    ;

  chThdCreateStatic(PollTmp75ThreadWA,
          sizeof(PollTmp75ThreadWA),
          NORMALPRIO,
          PollTmp75Thread,
          NULL);
  chThdSleepMilliseconds(1);
}

#undef I2CDtmp75
