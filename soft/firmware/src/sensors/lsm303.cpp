#include <math.h>

#include "uav.h"
#include "lsm303.hpp"
#include "sensors.hpp"
#include "message.hpp"
#include "param_registry.hpp"
#include "misc_math.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
//#define ALPHABETA_LEN   1024

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern CompensatedData comp_data;
extern ParamRegistry param_registry;

extern mavlink_raw_imu_t mavlink_out_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_out_scaled_imu_struct;

extern EventSource event_mavlink_out_raw_imu;

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

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void LSM303::pickle(void){
  int32_t raw[3];
  int32_t Mag[3];
  int16_t t;

  /**/
  raw[0] = complement2signed(rxbuf[0], rxbuf[1]);
  raw[1] = complement2signed(rxbuf[2], rxbuf[3]);
  raw[2] = complement2signed(rxbuf[4], rxbuf[5]);
  t      = complement2signed(rxbuf[6], rxbuf[7]) / 16; // deg * 8
  (void)t;
  sort3(raw, Mag, *sortmtrx);

  Mag[0] *= *xpol;
  Mag[1] *= *ypol;
  Mag[2] *= *zpol;

  /* calibration aid */
  if (calibration){
    mavlink_out_raw_imu_struct.xmag = xalphabeta.update(Mag[0], *filterlen);
    mavlink_out_raw_imu_struct.ymag = yalphabeta.update(Mag[1], *filterlen);
    mavlink_out_raw_imu_struct.zmag = zalphabeta.update(Mag[2], *filterlen);
    sample_cnt++;
    if (*zerocnt <= sample_cnt){
      calibration = false;
      chEvtBroadcastFlags(&event_mavlink_out_raw_imu, EVMSK_MAVLINK_OUT_RAW_IMU);
    }
  }
  else{
    mavlink_out_raw_imu_struct.xmag = Mag[0];
    mavlink_out_raw_imu_struct.ymag = Mag[1];
    mavlink_out_raw_imu_struct.zmag = Mag[2];
  }

  /* soft iron correction */
  comp_data.xmag = Mag[0] * *ellip_00;
  comp_data.ymag = Mag[0] * *ellip_10 + Mag[1] * *ellip_11;
  comp_data.zmag = Mag[0] * *ellip_20 + Mag[1] * *ellip_21 + Mag[2] * *ellip_22;

//  comp_data.xmag = Mag[0] * 0.9143f;
//  comp_data.ymag = Mag[0] * 0.0622f + Mag[1] * 1.0121f;
//  comp_data.zmag = Mag[0] * 0.2726f + Mag[1] * 0.2050f + Mag[2] * 0.5062f;

  /* hard iron correction */
  comp_data.xmag -= *xoffset;
  comp_data.ymag -= *yoffset;
  comp_data.zmag -= *zoffset;

//  comp_data.xmag -= 86.922f;
//  comp_data.ymag -= -3.4023f;
//  comp_data.zmag -= -138.7114f;

  mavlink_out_scaled_imu_struct.xmag = comp_data.xmag;
  mavlink_out_scaled_imu_struct.ymag = comp_data.ymag;
  mavlink_out_scaled_imu_struct.zmag = comp_data.zmag;
}

/**
 *
 */
LSM303::LSM303(I2CDriver *i2cdp, i2caddr_t addr):
I2CSensor(i2cdp, addr),
sample_cnt(0),
calibration(false)
{
  ready = false;
}

void LSM303::stop(void){
  // TODO: power down sensor here
  ready = false;
}

/**
 *
 */
bool LSM303::trigCal(void){
  if (true == calibration)
    return CH_FAILED;
  else{
    xalphabeta.reset(mavlink_out_raw_imu_struct.xmag, *filterlen);
    yalphabeta.reset(mavlink_out_raw_imu_struct.ymag, *filterlen);
    zalphabeta.reset(mavlink_out_raw_imu_struct.zmag, *filterlen);

    sample_cnt = 0;
    calibration = true;
    return CH_SUCCESS;
  }
}

/**
 *
 */
void LSM303::update(void){
  chDbgCheck((true == ready), "not ready");

  if ((sample_cnt % 128) == 0){
    txbuf[0] = TEMP_OUT_H_M;
    transmit(txbuf, 1, rxbuf+6, 2);
  }
  sample_cnt++;

  /* read previose measurement results */
  txbuf[0] = OUT_X_H_M;
  transmit(txbuf, 1, rxbuf, 6);

  /* start new measurement */
  txbuf[0] = MR_REG_M;
  txbuf[1] = 0b00000001;
  transmit(txbuf, 2, NULL, 0);

  this->pickle();
}

/**
 *
 */
void LSM303::hw_init_fast(void){
}

/**
 *
 */
void LSM303::hw_init_full(void){
  txbuf[0] = CRA_REG_M;
  /* enable thermometer and set maximum output rate */
  txbuf[1] = 0b10011100;
  /* set maximum gain. 001 is documented for LSM303 and 000 is for HMC5883.
   * 000 looks working for LSM303 too. */
  txbuf[2] = 0b00100000;
  //txbuf[2] = 0b00000000;
  /* single conversion mode */
  txbuf[3] = 0b00000001;

  transmit(txbuf, 4, NULL, 0);
}

/**
 *
 */
void LSM303::start(void){
  if (need_full_init()){
    hw_init_full();
  }
  else{
    hw_init_fast();
  }

  xoffset   = (const float*)param_registry.valueSearch("MAG_xoffset");
  yoffset   = (const float*)param_registry.valueSearch("MAG_yoffset");
  zoffset   = (const float*)param_registry.valueSearch("MAG_zoffset");

  ellip_00  = (const float*)param_registry.valueSearch("MAG_ellip_00");
  ellip_10  = (const float*)param_registry.valueSearch("MAG_ellip_10");
  ellip_11  = (const float*)param_registry.valueSearch("MAG_ellip_11");
  ellip_20  = (const float*)param_registry.valueSearch("MAG_ellip_20");
  ellip_21  = (const float*)param_registry.valueSearch("MAG_ellip_21");
  ellip_22  = (const float*)param_registry.valueSearch("MAG_ellip_22");

  xpol      = (const int32_t*)param_registry.valueSearch("MAG_xpol");
  ypol      = (const int32_t*)param_registry.valueSearch("MAG_ypol");
  zpol      = (const int32_t*)param_registry.valueSearch("MAG_zpol");

  xsens     = (const float*)param_registry.valueSearch("MAG_xsens");
  ysens     = (const float*)param_registry.valueSearch("MAG_ysens");
  zsens     = (const float*)param_registry.valueSearch("MAG_zsens");

  sortmtrx  = (const uint32_t*)param_registry.valueSearch("MAG_sortmtrx");
  zerocnt   = (const uint32_t*)param_registry.valueSearch("MAG_zerocnt");
  filterlen = (const int32_t*)param_registry.valueSearch("FLEN_magnetom");

  ready = true;
}
