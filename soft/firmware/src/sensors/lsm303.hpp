#ifndef LSM303_H_
#define LSM303_H_

#include "i2c_local.hpp"

#define lsm303accaddr       0b0011001
#define lsm303magaddr       0b0011110

#define LSM_RX_DEPTH        8
#define LSM_TX_DEPTH        4

#define CRA_REG_M           0x00
#define CRB_REG_M           0x01
#define MR_REG_M            0x02

#define OUT_X_H_M           0x03
#define TEMP_OUT_H_M        0x31


class LSM303: private I2CSensor{
public:
  LSM303(I2CDriver *i2cdp, i2caddr_t addr);
  void update(void);
  void start(void);
  void stop(void);

private:
  void pickle(void);
  void hw_init_full(void);
  void hw_init_fast(void);
  uint8_t rxbuf[LSM_RX_DEPTH];
  uint8_t txbuf[LSM_TX_DEPTH];
  /* calibration coefficients pointers */
  float    const *xsens,    *ysens,    *zsens;
  float    const *xoffset,  *yoffset,  *zoffset;
  float    const *ellip_00, *ellip_10, *ellip_11, *ellip_20, *ellip_21, *ellip_22;
  int32_t  const *xpol,     *ypol,     *zpol;
  uint32_t const *sortmtrx;
};


#endif /* LSM303_H_ */
