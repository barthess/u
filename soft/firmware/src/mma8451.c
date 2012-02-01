#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "dsp.h"
#include "mma8451.h"
#include "message.h"
#include "parameters.h"
#include "main.h"

#include "mavlink.h"
#include "common.h"
#include "bart.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define mma8451addr 0b0011100

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern BinarySemaphore mma8451_sem;
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern GlobalParam_t global_data[];

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[ACCEL_RX_DEPTH];
static uint8_t txbuf[ACCEL_TX_DEPTH];

/* индексы в структуре с параметрами */
static uint32_t xoffset_index, yoffset_index, zoffset_index;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/* Поток для запроса акселерометра */
static WORKING_AREA(PollAccelThreadWA, 256);
static msg_t PollAccelThread(void *arg){
  chRegSetThreadName("PollAccel");
  (void)arg;

  msg_t sem_status = RDY_OK;

  while (TRUE) {
    sem_status = chBSemWaitTimeout(&mma8451_sem, MS2ST(20));
    txbuf[0] = ACCEL_STATUS;
    if (i2c_transmit(mma8451addr, txbuf, 1, rxbuf, 6) == RDY_OK &&
                                           sem_status == RDY_OK){
      mavlink_raw_imu_struct.xacc = complement2signed(rxbuf[1], rxbuf[2]);
      mavlink_raw_imu_struct.yacc = complement2signed(rxbuf[3], rxbuf[4]);
      mavlink_raw_imu_struct.zacc = complement2signed(rxbuf[5], rxbuf[6]);
    }
    else{
      mavlink_raw_imu_struct.xacc = -32768;
      mavlink_raw_imu_struct.yacc = -32768;
      mavlink_raw_imu_struct.zacc = -32768;
    }
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void init_mma8451(void){
  int32_t i = -1;

  i = key_value_search("ACC_xoffset", global_data);
  if (i == -1)
    chDbgPanic("key not found");
  else
    xoffset_index = i;

  i = key_value_search("ACC_yoffset", global_data);
  if (i == -1)
    chDbgPanic("key not found");
  else
    yoffset_index = i;

  i = key_value_search("ACC_zoffset", global_data);
  if (i == -1)
    chDbgPanic("key not found");
  else
    zoffset_index = i;

  /* Помни о том, что большинство конфигурационных регистров нельзя менять
   в активном режиме, надо сначала свалить девайс в STANDBY. */

  // TODO: сначала вообще убедиться, что девайс отвечает путем запроса его WHOAMI
  // TODO: запустить в нем самодиагностику

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    i = 0;
    for (i = 0; i < ACCEL_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < ACCEL_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  txbuf[0] = ACCEL_CTRL_REG2;
  txbuf[1] = 0b100000; //Reset
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  txbuf[0] = ACCEL_CTRL_REG1;
  txbuf[1] = 0b0; //set standby to allow configure device
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  txbuf[0] = ACCEL_XYZ_DATA_CFG;
  txbuf[1] = 0b1;// 4g mode
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  txbuf[0] = ACCEL_CTRL_REG2;
  txbuf[1] = 0b10; //High Resolution
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  txbuf[0] = ACCEL_CTRL_REG3;
  txbuf[1] = 0b10; //Interrupt active high
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  txbuf[0] = ACCEL_CTRL_REG4;
  txbuf[1] = 0b01; //Interrupt on data ready
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  txbuf[0] = ACCEL_CTRL_REG1;
  txbuf[1] = 0b11101; //100Hz, low noice, active
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  chThdCreateStatic(PollAccelThreadWA,
          sizeof(PollAccelThreadWA),
          I2C_THREADS_PRIO,
          PollAccelThread,
          NULL);
}


