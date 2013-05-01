#ifndef IMU_H_
#define IMU_H_

void ImuInit(void);

bool TrigCalibrateGyro(void);
bool TrigCalibrateMag(void);

#endif /* IMU_H_ */
