#include <stdlib.h>
#include "i2c_local.hpp"
#include "itg3200_cal.hpp"

#ifndef ITG3200_H_
#define ITG3200_H_

#define itg3200addr         0b1101000

/* buffers depth */
#define GYRO_RX_DEPTH 8
#define GYRO_TX_DEPTH 4

#define GYRO_WHOAMI     0x00
#define GYRO_WHOAMI_VAL 0b110100
#define GYRO_OUT_DATA   0x1B // начиная с термометра
#define GYRO_SMPLRT_DIV 0x15
#define GYRO_INT_CFG    0x17
#define GYRO_DLPF_FS    0x16
  #define GYRO_FS_SEL   (3 << 3) //full scale range
  #define GYRO_DLPF_CFG (5)//low pass filter bandwidth
#define GYRO_PWR_MGMT   0x3E


class ITG3200: private I2CSensor{
public:
  ITG3200(I2CDriver *i2cdp, i2caddr_t addr);
  void update(float *result, uint32_t still_msk);
  void start(void);
  void stop(void);
  bool trigCalibration(void);
  bool isCalibrating(void);
  bool still(void);

private:
  ITG3200calibrator calibrator;
  void update_stillness(const float *result);
  void pickle(float *result, uint32_t still_msk);
  void hw_init_full(void);
  void hw_init_fast(void);
  bool immobile;
  uint8_t rxbuf[GYRO_RX_DEPTH];
  uint8_t txbuf[GYRO_TX_DEPTH];
  /* calibration coefficients pointers */
  float    const *xsens,     *ysens,     *zsens;
  int32_t  const *xpol,      *ypol,      *zpol;
  float          *x_offset,  *y_offset,  *z_offset;
  uint32_t const *sortmtrx,  *sendangle;
  float const    *stillthr;
};



#endif /* ITG3200_H_ */
