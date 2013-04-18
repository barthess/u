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
static float    const *xsens,   *ysens,   *zsens;
static int32_t  const *xoffset, *yoffset, *zoffset;
static int32_t  const *xpol,    *ypol,    *zpol;
static uint32_t const *sortmtrx;


//static float m[9] = {
//   0.9143        0        0
//   0.0622   1.0121        0
//   0.2726   0.2050   0.5062}
//
//  -86.9220
//    3.4023
//  138.7114
/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

static void process_lsm_data(uint8_t *rxbuf){
  int32_t raw[3];
  int32_t Mag[3];
  int16_t t;

  /**/
  raw[0] = complement2signed(rxbuf[0], rxbuf[1]);
  raw[1] = complement2signed(rxbuf[2], rxbuf[3]);
  raw[2] = complement2signed(rxbuf[4], rxbuf[5]);
  t      = complement2signed(rxbuf[6], rxbuf[7]) / 16; // deg * 8
  (void)t;
  sorti_3values(raw, Mag, *sortmtrx);

  mavlink_out_raw_imu_struct.xmag = Mag[0];
  mavlink_out_raw_imu_struct.ymag = Mag[1];
  mavlink_out_raw_imu_struct.zmag = Mag[2];

//  /**/
//  mag_stat_update(Mag);
//
//  /* Sensitivity is 0.1uT/LSB */
//  mavlink_out_scaled_imu_struct.xmag = (Mag[0] - *xoffset) * *xpol * roundf(*xsens * 100.0f);
//  mavlink_out_scaled_imu_struct.ymag = (Mag[1] - *yoffset) * *ypol * roundf(*ysens * 100.0f);
//  mavlink_out_scaled_imu_struct.zmag = (Mag[2] - *zoffset) * *zpol * roundf(*zsens * 100.0f);
//  comp_data.xmag = (float)(mavlink_out_scaled_imu_struct.xmag);
//  comp_data.ymag = (float)(mavlink_out_scaled_imu_struct.ymag);
//  comp_data.zmag = (float)(mavlink_out_scaled_imu_struct.zmag);

  comp_data.xmag = Mag[0] * 0.9143f;
  comp_data.ymag = Mag[0] * 0.0622f + Mag[1] * 1.0121f;
  comp_data.zmag = Mag[0] * 0.2726f + Mag[1] * 0.2050f + Mag[2] * 0.5062f;

  comp_data.xmag -= 86.922f;
  comp_data.ymag -= -3.4023f;
  comp_data.zmag -= -138.7114f;

  comp_data.xmag *= *xpol;
  comp_data.ymag *= *ypol;
  comp_data.zmag *= *zpol;

  mavlink_out_scaled_imu_struct.xmag = comp_data.xmag;
  mavlink_out_scaled_imu_struct.ymag = comp_data.ymag;
  mavlink_out_scaled_imu_struct.zmag = comp_data.zmag;
}

/**
 *
 */
static WORKING_AREA(PollLsmThreadWA, 512); /* large stack need for sphere calc */
static msg_t PollLsmThread(void *semp){
  chRegSetThreadName("PollLsm303");
  uint8_t txbuf[2];
  uint8_t rxbuf[8]; // 6 for mag, 2 for temp
  uint32_t cnt = 0;

  while (!chThdShouldTerminate()){
    if ((cnt % 128) == 0){
      txbuf[0] = TEMP_OUT_H_M;
      i2c_transmit(lsm303_mag_addr, txbuf, 1, rxbuf+6, 2);
    }
    cnt++;

    /* read previose measurement results */
    txbuf[0] = OUT_X_H_M;
    i2c_transmit(lsm303_mag_addr, txbuf, 1, rxbuf, 6);

    /* start new measurement */
    txbuf[0] = MR_REG_M;
    txbuf[1] = 0b00000001;
    i2c_transmit(lsm303_mag_addr, txbuf, 2, NULL, 0);

    process_lsm_data(rxbuf);
    setGlobalFlag(GlobalFlags.mag_data_fresh);
    chBSemWaitTimeout((BinarySemaphore*)semp, MS2ST(200));
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
  /* enable thermometer and set maximum output rate */
  txbuf[1] = 0b10011100;
  /* set maximum gain. 001 is documented for LSM303 and 000 is for HMC5883.
   * 000 looks working for LSM303 too. */
  txbuf[2] = 0b00100000;
  //txbuf[2] = 0b00000000;
  /* single conversion mode */
  txbuf[3] = 0b00000001;

  i2c_transmit(lsm303_mag_addr, txbuf, 4, NULL, 0);
}

/**
 *
 */
static void __search_indexes(void){
  xoffset   = ValueSearch("MAG_xoffset");
  yoffset   = ValueSearch("MAG_yoffset");
  zoffset   = ValueSearch("MAG_zoffset");

  xpol      = ValueSearch("MAG_xpol");
  ypol      = ValueSearch("MAG_ypol");
  zpol      = ValueSearch("MAG_zpol");

  xsens     = ValueSearch("MAG_xsens");
  ysens     = ValueSearch("MAG_ysens");
  zsens     = ValueSearch("MAG_zsens");

  sortmtrx  = ValueSearch("MAG_sortmtrx");
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void init_lsm303(BinarySemaphore *mag3110_semp){

  __search_indexes();

  HwInit();

  MagCalInit();

  chThdCreateStatic(PollLsmThreadWA,
        sizeof(PollLsmThreadWA),
        I2C_THREADS_PRIO,
        PollLsmThread,
        mag3110_semp);
}


