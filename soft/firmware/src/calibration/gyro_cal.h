#ifndef GYRO_CAL_H_
#define GYRO_CAL_H_


#define GYRO_STAT_UPDATED     TRUE
#define GYRO_STAT_UNCHANGED   FALSE


/**
 * @brief   State machine possible states.
 */
typedef enum {
  GYROCAL_UNINIT = 0,         /**< Not initialized.           */
  GYROCAL_WAIT_FOR_STILL = 1, /**< Wait device stillness.                     */
  GYROCAL_COLLECTING = 2,     /**< Collecting statistic.      */
  GYROCAL_READY = 3,          /**< Statistic collected. Ready for new run.     */
} gyrocalstate_t;


bool_t gyro_stat_update(int32_t x, int32_t y, int32_t z);
void GyroCalInit(void);


#endif /* GYRO_CAL_H_ */
