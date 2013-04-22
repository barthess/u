#ifndef IMU_H_
#define IMU_H_

bool IsDeviceStill(void);
void ImuInit(void);

bool ImuTrigCalibrateGyro(void);
bool ImuTrigCalibrateMag(void);

#endif /* IMU_H_ */
