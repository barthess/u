#include <math.h>

#include "uav.h"
#include "lsm303.h"
#include "i2c_local.h"
#include "sensors.h"
#include "message.h"

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
extern mavlink_raw_imu_t mavlink_out_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_out_scaled_imu_struct;
extern CompensatedData comp_data;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

static void process_lsm_data(uint8_t *rxbuf){
  int32_t raw[3];
  int16_t t;

  /**/
  raw[0] = complement2signed(rxbuf[0], rxbuf[1]);
  raw[1] = complement2signed(rxbuf[2], rxbuf[3]);
  raw[2] = complement2signed(rxbuf[4], rxbuf[5]);
  t      = complement2signed(rxbuf[6], rxbuf[7]) / 16; // deg * 8
  (void)t;

  mavlink_out_raw_imu_struct.xmag = raw[0];
  mavlink_out_raw_imu_struct.ymag = raw[1];
  mavlink_out_raw_imu_struct.zmag = raw[2];

  comp_data.xmag = (float)(mavlink_out_scaled_imu_struct.xmag);
  comp_data.ymag = (float)(mavlink_out_scaled_imu_struct.ymag);
  comp_data.zmag = (float)(mavlink_out_scaled_imu_struct.zmag);
}

/**
 *
 */
static WORKING_AREA(PollLsmThreadWA, 1024);
static msg_t PollLsmThread(void *arg){
  (void)arg;
  chRegSetThreadName("PollLsm");
  uint8_t txbuf[1];
  uint8_t rxbuf[8]; // 6 for mag, 2 for temp
  uint32_t cnt = 0;

  while (!chThdShouldTerminate()){
    txbuf[0] = OUT_X_H_M;
    i2c_transmit(lsm303_mag_addr, txbuf, 1, rxbuf, 6);

    if ((cnt % 128) == 0){
      txbuf[0] = TEMP_OUT_H_M;
      i2c_transmit(lsm303_mag_addr, txbuf, 1, rxbuf+6, 2);
    }
    cnt++;

    process_lsm_data(rxbuf);

    chThdSleepMilliseconds(10);
  }

  chThdExit(0);
  return 0;
}

/**
 *
 */
void HwInit(void){
  uint8_t txbuf[4];

  chDbgCheck(1 == GlobalFlags.i2c_ready, "you must initialize I2C driver first");

  txbuf[0] = CRA_REG_M;
  txbuf[1] = 0b10011100; /* enable thermometer and set maximum output rate */
  txbuf[2] = 0b00100000; /* set maximum gain */
  txbuf[3] = 0b00000000; /* continuouse conversion mode */

  i2c_transmit(lsm303_mag_addr, txbuf, 4, NULL, 0);
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void init_lsm303(void){

  HwInit();

  chThdCreateStatic(PollLsmThreadWA,
        sizeof(PollLsmThreadWA),
        I2C_THREADS_PRIO,
        PollLsmThread,
        NULL);
}


