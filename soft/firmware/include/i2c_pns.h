#ifndef I2C_PNS_H_
#define I2C_PNS_H_

void I2CInit_pns(void);
msg_t i2c_transmit(I2CDriver *i2cp,
                  i2caddr_t addr,
                  const uint8_t *txbuf,
                  size_t txbytes,
                  uint8_t *rxbuf,
                  size_t rxbytes);
msg_t i2c_receive(I2CDriver *i2cp,
                  i2caddr_t addr,
                  uint8_t *rxbuf,
                  size_t rxbytes);

#endif /* I2C_PNS_H_ */
