#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "dsp.h"
#include "itg3200.h"
#include "message.h"
#include "main.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define I2CD_itg3200 I2CD2
#define itg3200_addr 0b1101000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern BinarySemaphore itg3200_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[GYRO_RX_DEPTH];
static uint8_t txbuf[GYRO_TX_DEPTH];

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/* ѕоток дл€ запроса акселерометра */
static WORKING_AREA(PollGyroThreadWA, 256);
static msg_t PollGyroThread(void *arg){

  chRegSetThreadName("PollGyro");
  (void)arg;
  msg_t sem_status = RDY_OK;

  while (TRUE) {
    sem_status = chBSemWaitTimeout(&itg3200_sem, MS2ST(20));

    txbuf[0] = GYRO_OUT_DATA;     // register address
    if (i2c_transmit(&I2CD_itg3200, itg3200_addr, txbuf, 1, rxbuf, 8) == RDY_OK &&
                                                           sem_status == RDY_OK){
      raw_data.gyro_temp = complement2signed(rxbuf[0], rxbuf[1]);
      raw_data.gyro_x    = complement2signed(rxbuf[2], rxbuf[3]);
      raw_data.gyro_y    = complement2signed(rxbuf[4], rxbuf[5]);
      raw_data.gyro_z    = complement2signed(rxbuf[6], rxbuf[7]);
    }
    else{
      raw_data.gyro_temp = 0;
      raw_data.gyro_x    = -32000;
      raw_data.gyro_y    = -32000;
      raw_data.gyro_z    = -32000;
    }
  }
  return 0;
}


void init_itg3200(void){

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint8_t i = 0;
    for (i = 0; i < GYRO_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < GYRO_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  txbuf[0] = GYRO_PWR_MGMT;
  txbuf[1] = 0b1000000; /* soft reset */
  while (i2c_transmit(&I2CD_itg3200, itg3200_addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  txbuf[0] = GYRO_PWR_MGMT;
  txbuf[1] = 1; /* select clock source */
  while (i2c_transmit(&I2CD_itg3200, itg3200_addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  txbuf[0] = GYRO_SMPLRT_DIV;
  txbuf[1] = 9; /* sample rate (1000 / (9 +1)) = 100Hz*/
  txbuf[2] = GYRO_DLPF_CFG | GYRO_FS_SEL; /* диапазон измерений и частота внутреннего фильтра */
  txbuf[3] = 1; /* enable interrupts */
  while (i2c_transmit(&I2CD_itg3200, itg3200_addr, txbuf, 4, rxbuf, 0) != RDY_OK)
    ;

  chThdCreateStatic(PollGyroThreadWA,
          sizeof(PollGyroThreadWA),
          NORMALPRIO,
          PollGyroThread,
          NULL);
}
