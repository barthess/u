#ifndef IMU_H_
#define IMU_H_

#include "madgwick.hpp"
#include "quaternion.hpp"
#include "sensors.hpp"

#include "itg3200.hpp"
#include "lsm303.hpp"
#include "mma8451.hpp"
#include "max1236.hpp"


typedef enum {
  IMU_STATE_UNINIT,
  IMU_STATE_IDLE,
  IMU_STATE_UPDATING,
}imu_state_t;


typedef enum {
  IMU_UPDATE_RESULT_OK,
  IMU_UPDATE_RESULT_EMPTY,
  IMU_UPDATE_RESULT_ERROR,
}imu_update_result_t;


class IMU{
public:
  IMU(void);
  void start(void);
  void stop(void);
  imu_update_result_t update(StateVector *attitude);
  bool trigCalibrateGyro(void){return itg3200.trigCalibration();};
  bool trigCalibrateMag(void){return lsm303.trigCalibration();};

private:
  void update_still_msk(void);

private:
  ITG3200  itg3200;
  LSM303   lsm303;
  MMA8451  mma8451;
  imu_state_t state;
  uint32_t still_msk;
  int32_t t0, t1;
  msg_t sem_status;
  int32_t retry;
  float interval;       /* time between 2 gyro measurements, S */
  float acc[3];         /* acceleration in G */
  float gyro[3];        /* angular rates in rad/s */
  float mag[3];         /* magnetic flux in uT */

  MadgwickAHRS ahrs;
  Quaternion<float> MadgwickQuat;

  float const     *declination;
  uint32_t const  *ahrsmode;
};

#endif /* IMU_H_ */
