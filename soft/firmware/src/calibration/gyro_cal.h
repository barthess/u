#ifndef GYRO_CAL_H_
#define GYRO_CAL_H_


#define GYRO_STAT_UPDATED     TRUE
#define GYRO_STAT_UNCHANGED   FALSE


bool_t GyroZeroUpdate(int32_t *data);
void GyroCalInit(void);


#endif /* GYRO_CAL_H_ */
