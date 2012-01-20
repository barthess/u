#ifndef DSP_H_
#define DSP_H_

#include <stdlib.h>
#include "ch.h"
#include "hal.h"


int32_t  pack8to32(uint8_t *buf);
uint32_t upack8to32(uint8_t *buf);
int16_t  pack8to16(uint8_t *buf);
uint16_t upack8to16(uint8_t *buf);

uint32_t Simpson(uint32_t a, uint32_t b, uint32_t c);
uint32_t Simpson38(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

int16_t complement2signed(uint8_t msb, uint8_t lsb);


#endif /* DSP_H_ */
