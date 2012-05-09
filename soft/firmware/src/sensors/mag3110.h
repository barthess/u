#include <stdlib.h>
#include "ch.h"

#ifndef MAG3110_H_
#define MAG3110_H_



/* buffers depth */
#define MAG_RX_DEPTH 8
#define MAG_TX_DEPTH 4


/* slave specific addresses */
#define MAG_OUT_DATA    0x01
#define MAG_CTRL_REG1   0x10
#define MAG_CTRL_REG2   0x11
  #define MAG_RST       (1 << 4)


void init_mag3110(BinarySemaphore *mag3110_semp);

#endif /* MAG3110_H_ */
