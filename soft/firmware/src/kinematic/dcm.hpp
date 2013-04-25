#ifndef DCM_H_
#define DCM_H_

void dcmInit(void);
void dcmUpdate(float *acc, float *gyro, float *mag, float imu_interval);

#endif /* DCM_H_ */
