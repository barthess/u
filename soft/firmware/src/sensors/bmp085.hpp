#ifndef BMP085_H_
#define BMP085_H_

#include "i2c_local.hpp"

#define bmp085addr          0b1110111

#define BMP085_RX_DEPTH     24
#define BMP085_TX_DEPTH     4

#define BOSCH_CTL					  0xF4 // control register address
#define BOSCH_TEMP				  0x2E
#define BOSCH_PRES  			  0xF4 // pressure with OSRS=3 (page 17 in manual)
#define BOSCH_ADC_MSB			  0xF6
#define BOSCH_ADC_LSB			  0xF7
#define BOSCH_ADC_XLSB		  0xF8
#define BOSCH_TYPE				  0xD0


typedef enum {
  MEASURE_NONE = 1, /* nothin measuring currently */
  MEASURE_T = 2,    /* current measurement is temperature */
  MEASURE_P = 3,    /* current measurement is pressure */
} measurement_t;


class BMP085: private I2CSensor{
public:
  BMP085(I2CDriver *i2cdp, i2caddr_t addr);
  void update(float *result, size_t len, uint32_t still_msk);
  void start(void);
  void stop(void);

private:
  void pickle(void);
  uint32_t bmp085_calc_pressure(uint32_t ut, uint32_t up);
  void process_pressure(uint32_t pval);
  void hw_init_full(void);
  void hw_init_fast(void);
  uint8_t rxbuf[BMP085_RX_DEPTH];
  uint8_t txbuf[BMP085_TX_DEPTH];
  /* length of filter */
  uint32_t const *flen_pres_stat;
  uint32_t const *flen_climb;
  measurement_t measure;
  // uncompensated temperature and pressure values
  uint32_t up, ut;
  // bmp085 calibration coefficients
  int16_t  ac1, ac2, ac3, b1, b2, mb, mc, md;
  uint16_t ac4, ac5, ac6;
};


#endif /* BMP085_H_ */
