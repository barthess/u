#ifndef MMA8451_H_
#define MMA8451_H_

#include "i2c_local.hpp"
#include "dsp.hpp"

#define mma8451addr         0b0011100

#define ACCEL_WHOAMI_VALUE  0b00011010

/* full scale sensitivity in g. 8g works only in hi noise mode */
#define ACCEL_SENS        4

/* buffers depth */
#define ACCEL_RX_DEPTH    8
#define ACCEL_TX_DEPTH    8

/* slave specific addresses */
#define ACCEL_STATUS      0x00
#define ACCEL_OUT_DATA    0x01
#define ACCEL_INT_SOURCE  0x0C
#define ACCEL_WHOAMI      0x0D
#define ACCEL_CTRL_REG1   0x2A
#define ACCEL_CTRL_REG2   0x2B
#define ACCEL_CTRL_REG3   0x2C
#define ACCEL_CTRL_REG4   0x2D
#define ACCEL_CTRL_REG5   0x2E

#define ACCEL_XYZ_DATA_CFG 0x0E


class MMA8451: private I2CSensor{
public:
  MMA8451(I2CDriver *i2cdp, i2caddr_t addr);
  void update(float *result, uint32_t still_msk);
  void start(void);
  void stop(void);
  bool still(void);

private:
  void pickle(float *result, uint32_t still_msk);
  void update_stillness(const float *result);
  void hw_init_full(void);
  void hw_init_fast(void);
  bool immobile;
  AlphaBeta<float> abeta[3];
  uint8_t rxbuf[ACCEL_RX_DEPTH];
  uint8_t txbuf[ACCEL_TX_DEPTH];
  /*  */
  int32_t  const *xoffset,   *yoffset,   *zoffset;
  int32_t  const *xpol,      *ypol,      *zpol;
  uint32_t const *xsens,     *ysens,     *zsens;
  uint32_t const *sortmtrx;
  float    const *still_thr;
  int32_t  const *still_flen;
};


#endif /* MMA8451_H_ */
