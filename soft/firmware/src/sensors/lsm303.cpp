#include <math.h>

#include "main.h"
#include "lsm303.hpp"
#include "sensors.hpp"
#include "message.hpp"
#include "param_registry.hpp"
#include "misc_math.hpp"
#include "matrix.hpp"
#include "vector3d.hpp"

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
extern ParamRegistry param_registry;

extern mavlink_raw_imu_t mavlink_out_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_out_scaled_imu_struct;

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
/**
 *
 */
void LSM303::update_stillness(const float *result){
  float cross[3];
  float filtered[3];
  float modulus_cross;
  float modulus_delta;
  uint32_t i = 0;

  /* update array of filters */
  for (i=0; i<3; i++)
    filtered[i] = abeta[i].update(result[i], *still_flen);

  /* calculate differences between vectors */
  vector3d_cross(result, filtered, cross);
  modulus_cross = vector3d_modulus(cross);
  modulus_delta = vector3d_modulus(result) - vector3d_modulus(filtered);

  if ((fabsf(modulus_delta) > *still_thr) ||
      (fabsf(modulus_cross / 100.0f) > *still_thr))
    immobile = false;
}

/**
 *
 */
inline void LSM303::pickle(float *result, uint32_t still_msk){
  (void)still_msk;

  int32_t raw[3];
  int16_t t;

  /**/
  raw[0] = complement2signed(rxbuf[0], rxbuf[1]);
  raw[1] = complement2signed(rxbuf[2], rxbuf[3]);
  raw[2] = complement2signed(rxbuf[4], rxbuf[5]);
  t      = complement2signed(rxbuf[6], rxbuf[7]) / 16; // deg * 8
  (void)t;

  /* convert to NUE coordinate system */
  sort3(raw, *sortmtrx);
  raw[0] *= *xpol;
  raw[1] *= *ypol;
  raw[2] *= *zpol;

  mavlink_out_raw_imu_struct.xmag = raw[0];
  mavlink_out_raw_imu_struct.ymag = raw[1];
  mavlink_out_raw_imu_struct.zmag = raw[2];

  result[0] = raw[0];
  result[1] = raw[1];
  result[2] = raw[2];

  /* obtain uT from parrots */
  result[0] /= *xsens;
  result[1] /= *ysens;
  result[2] /= *zsens;

  /* */
  calibrator.update(result, still_msk);

  /* soft iron correction */
  //result[0] = raw[0] * *ellip_00;
  //result[1] = raw[0] * *ellip_10 + raw[1] * *ellip_11;
  //result[2] = raw[0] * *ellip_20 + raw[1] * *ellip_21 + raw[2] * *ellip_22;

  /* hard iron correction */
  result[0] -= *xoffset;
  result[1] -= *yoffset;
  result[2] -= *zoffset;

  /* fill debugging message with nT */
  mavlink_out_scaled_imu_struct.xmag = result[0];
  mavlink_out_scaled_imu_struct.ymag = result[1];
  mavlink_out_scaled_imu_struct.zmag = result[2];
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
bool LSM303::trigCalibration(void){
  return calibrator.trig();
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 *
 */
LSM303::LSM303(I2CDriver *i2cdp, i2caddr_t addr):
I2CSensor(i2cdp, addr),
sample_cnt(0)
{
  ready = false;
}

/**
 *
 */
void LSM303::stop(void){
  // TODO: power down sensor here
  ready = false;
}

/**
 *
 */
void LSM303::update(float *result, uint32_t still_msk){
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

  this->pickle(result, still_msk);
  this->update_stillness(result);
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

  dcm[0]    = (const float*)param_registry.valueSearch("MAG_dcm_00");
  dcm[1]    = (const float*)param_registry.valueSearch("MAG_dcm_01");
  dcm[2]    = (const float*)param_registry.valueSearch("MAG_dcm_02");
  dcm[3]    = (const float*)param_registry.valueSearch("MAG_dcm_10");
  dcm[4]    = (const float*)param_registry.valueSearch("MAG_dcm_11");
  dcm[5]    = (const float*)param_registry.valueSearch("MAG_dcm_12");
  dcm[6]    = (const float*)param_registry.valueSearch("MAG_dcm_20");
  dcm[7]    = (const float*)param_registry.valueSearch("MAG_dcm_21");
  dcm[8]    = (const float*)param_registry.valueSearch("MAG_dcm_22");

  xpol      = (const int32_t*)param_registry.valueSearch("MAG_xpol");
  ypol      = (const int32_t*)param_registry.valueSearch("MAG_ypol");
  zpol      = (const int32_t*)param_registry.valueSearch("MAG_zpol");

  xsens     = (const float*)param_registry.valueSearch("MAG_xsens");
  ysens     = (const float*)param_registry.valueSearch("MAG_ysens");
  zsens     = (const float*)param_registry.valueSearch("MAG_zsens");

  sortmtrx  = (const uint32_t*)param_registry.valueSearch("MAG_sortmtrx");
  zerocnt   = (const uint32_t*)param_registry.valueSearch("MAG_zerocnt");

  still_thr = (const float*)param_registry.valueSearch("MAG_still_thr");
  still_flen= (const int32_t*)param_registry.valueSearch("MAG_still_flen");

  calibrator.start();
  ready = true;
}


/**
 * return true if device was immobile still last call of this function
 */
bool LSM303::still(void){
  bool tmp;

  chSysLock();
  tmp = immobile;
  immobile = true;
  chSysUnlock();

  return tmp;
}
