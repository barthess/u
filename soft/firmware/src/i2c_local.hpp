#ifndef I2C_LOCAL_H_
#define I2C_LOCAL_H_

class I2CSensor{
public:
  I2CSensor(I2CDriver *i2cdp, const i2caddr_t addr);

protected:
  msg_t transmit(const uint8_t *txbuf, size_t txbytes,
                       uint8_t *rxbuf, size_t rxbytes);
  msg_t receive(uint8_t *rxbuf, size_t rxbytes);
  virtual void start(void) = 0;
  virtual void update(float *result, size_t len, uint32_t still_msk) = 0;
  virtual void stop(void) = 0;
  virtual void hw_init_fast(void) = 0;
  virtual void hw_init_full(void) = 0;
  bool ready;

private:
  I2CDriver *i2cdp;
  const i2caddr_t addr;
};

void I2CInitLocal(void);

#endif /* I2C_LOCAL_H_ */
