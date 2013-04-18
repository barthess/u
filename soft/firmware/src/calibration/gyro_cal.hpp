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

/**
 *
 */
typedef struct GyroCalContext GyroCalContext;
struct GyroCalContext{
  gyrocalstate_t gyrocalstate;

  /* collected sums for zero offset correction */
  int32_t ZeroSum[3];

  float *x_offset;
  float *y_offset;
  float *z_offset;
  int32_t const *zerocount;

  /* how many points remains to collect for full statistic */
  uint32_t SamplesCnt;
};

bool_t GyroZeroUpdate(int32_t *data);
void GyroCalInit(void);


#endif /* GYRO_CAL_H_ */
