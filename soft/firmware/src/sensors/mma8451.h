#include <stdlib.h>
#include "ch.h"

#ifndef MMA8451_H_
#define MMA8451_H_

#define ACCEL_WHOAMI_VALUE  0b00011010

/* full scale sensitivity in g. 8g works only in hi noise mode */
#define ACCEL_SENS        4

/* buffers depth */
#define ACCEL_RX_DEPTH    8
#define ACCEL_TX_DEPTH    8

/* slave specific addresses */
#define ACCEL_STATUS      0x00
#define ACCEL_OUT_DATA    0x01
#define ACCEL_INT_SOURCE  0x0C
#define ACCEL_WHOAMI      0x0D
#define ACCEL_CTRL_REG1   0x2A
#define ACCEL_CTRL_REG2   0x2B
#define ACCEL_CTRL_REG3   0x2C
#define ACCEL_CTRL_REG4   0x2D
#define ACCEL_CTRL_REG5   0x2E

#define ACCEL_XYZ_DATA_CFG 0x0E


bool_t is_device_still(void);
void device_still_clear(void);
void init_mma8451(BinarySemaphore *mma8451_semp);


#endif /* MMA8451_H_ */
