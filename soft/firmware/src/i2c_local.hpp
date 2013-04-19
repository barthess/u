#ifndef I2C_LOCAL_H_
#define I2C_LOCAL_H_

class I2CSensor{
public:
  I2CSensor(I2CDriver *i2cdp, i2caddr_t addr);

protected:
  msg_t transmit(const uint8_t *txbuf, size_t txbytes,
                       uint8_t *rxbuf, size_t rxbytes);
  msg_t receive(uint8_t *rxbuf, size_t rxbytes);
  virtual void start(void) = 0;
  virtual void update(void) = 0;
  virtual void pickle(void) = 0;
  virtual void stop(void) = 0;
  virtual void hw_init_fast(void) = 0;
  virtual void hw_init_full(void) = 0;
  bool ready;

private:
  I2CDriver *i2cdp;
  i2caddr_t addr;
};

void I2CInitLocal(void);

#endif /* I2C_LOCAL_H_ */


//void TMP75::pickle(void){
//}
//void TMP75::hw_init_fast(void){
//}
//void TMP75::hw_init_full(void){
//}
//TMP75::TMP75(I2CDriver *i2cdp, i2caddr_t addr):
//I2CSensor(i2cdp, addr)
//{
//  ready = false;
//}
//void TMP75::start(void){
//  if (need_full_init())
//    hw_init_full();
//  else
//    hw_init_fast();
//
//  ready = true;
//}
//void TMP75::stop(void){
//  ready = false;
//}
//void TMP75::update(void){
//  chDbgCheck((true == ready), "you must start() this device");
//}
