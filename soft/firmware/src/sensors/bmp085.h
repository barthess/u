#include "ch.h"

#ifndef BMP085_H_
#define BMP085_H_


#define BMP085_RX_DEPTH 24
#define BMP085_TX_DEPTH 4


#define BOSCH_CTL					0xF4 // control register address
#define BOSCH_TEMP				0x2E
#define BOSCH_PRES  			0xF4 // pressure with OSRS=3 (page 17 in manual)
#define BOSCH_ADC_MSB			0xF6
#define BOSCH_ADC_LSB			0xF7
#define BOSCH_ADC_XLSB		0xF8
#define BOSCH_TYPE				0xD0


void init_bmp085(BinarySemaphore *itg3200_semp);


#endif /* BMP085_H_ */
