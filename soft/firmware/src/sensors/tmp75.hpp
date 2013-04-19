#ifndef TMP75_H_
#define TMP75_H_

#include "i2c_local.hpp"

#define tmp75addr 0b1001000

/* buffers depth */
#define TMP75_RX_DEPTH 4
#define TMP75_TX_DEPTH 4


class Tmp75: private I2CSensor{
public:
  Tmp75(I2CDriver *i2cdp, i2caddr_t addr);
  void update(void);
  void start(void);

private:
  void pickle(void);
  void hw_init_full(void);
  void hw_init_fast(void);
  uint8_t rxbuf[TMP75_RX_DEPTH];
  uint8_t txbuf[TMP75_TX_DEPTH];
};



void init_tmp75(void);

#endif /* TMP75_H_ */
