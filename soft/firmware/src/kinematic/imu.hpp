#ifndef IMU_H_
#define IMU_H_

bool IsDeviceStill(void);
void ImuInit(chibios_rt::BinarySemaphore *imu_semp);


#endif /* IMU_H_ */
