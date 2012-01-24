#ifndef IMU_H_
#define IMU_H_

/* сколько взять сэмплов для определения нуля гироскопов */
#define GYRO_AVG_SAMPLES_CNT 8192


void ImuInit(void);


#endif /* IMU_H_ */
