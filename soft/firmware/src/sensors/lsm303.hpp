#ifndef LSM303_H_
#define LSM303_H_

#define lsm303_acc_addr     0b0011001
#define lsm303_mag_addr     0b0011110

#define CRA_REG_M           0x00
#define CRB_REG_M           0x01
#define MR_REG_M            0x02

#define OUT_X_H_M           0x03
#define TEMP_OUT_H_M        0x31


void init_lsm303(BinarySemaphore *mag3110_semp);


#endif /* LSM303_H_ */
