#ifndef GYRO_CAL_H_
#define GYRO_CAL_H_


#define GYRO_STAT_UPDATED     TRUE
#define GYRO_STAT_UNCHANGED   FALSE


bool_t gyro_stat_update(int32_t x, int32_t y, int32_t z);
void GyroCalInit(void);


#endif /* GYRO_CAL_H_ */
