#ifndef I2C_LOCAL_H_
#define I2C_LOCAL_H_

class I2CSlave{
public:
  I2CSlave(I2CDriver *i2cdp, i2caddr_t addr);
  msg_t transmit(const uint8_t *txbuf, size_t txbytes,
                       uint8_t *rxbuf, size_t rxbytes);
  msg_t receive(uint8_t *rxbuf, size_t rxbytes);

private:
  I2CDriver *i2cdp;
  i2caddr_t addr;
};

void I2CInitLocal(void);
msg_t i2c_transmit(i2caddr_t addr, const uint8_t *txbuf,
                  size_t txbytes, uint8_t *rxbuf, size_t rxbytes);
msg_t i2c_receive(i2caddr_t addr, uint8_t *rxbuf, size_t rxbytes);


#endif /* I2C_LOCAL_H_ */
