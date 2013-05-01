#ifndef MAX1236_H_
#define MAX1236_H_

#include "i2c_local.hpp"

#define max1236addr 0b0110100

#define MAX1236_RX_DEPTH 8
#define MAX1236_TX_DEPTH 4


class MAX1236: private I2CSensor{
public:
  MAX1236(I2CDriver *i2cdp, i2caddr_t addr);
  void update(void);
  void start(void);
  void stop(void);

private:
  void pickle(void);
  void hw_init_full(void);
  void hw_init_fast(void);
  uint8_t rxbuf[MAX1236_RX_DEPTH];
  uint8_t txbuf[MAX1236_TX_DEPTH];
  uint32_t const *flen_pres_dyn;
};


#endif /* MAX1236_H_ */
