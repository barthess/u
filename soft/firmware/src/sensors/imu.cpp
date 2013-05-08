#include "main.h"
#include "dcm.hpp"
#include "sensors.hpp"
#include "message.hpp"
#include "geometry.hpp"
#include "param_registry.hpp"
#include "logger.hpp"
#include "imu.hpp"
#include "geometry.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define GYRO_TIMEOUT        MS2ST(100)
#define GYRO_RETRY          10

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern CompensatedData comp_data;
extern mavlink_attitude_t mavlink_out_attitude_struct;
extern ParamRegistry param_registry;
extern chibios_rt::BinarySemaphore itg3200_sem;

float dcmEst[3][3] = {{1,0,0},
                      {0,1,0},
                      {0,0,1}};   /* estimated DCM matrix */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Get attitude from DCM
 */
static void dcm2attitude(mavlink_attitude_t *mavlink_attitude_struct,
                        const float *gyro, const float *declination){
  mavlink_attitude_struct->time_boot_ms = TIME_BOOT_MS;
  if (Rzz >= 0){
    mavlink_attitude_struct->pitch  = -asinf(Rxz);
    mavlink_attitude_struct->roll   = -asinf(Ryz);
  }
  else{
    mavlink_attitude_struct->pitch  = PI - (-asinf(Rxz));
    mavlink_attitude_struct->roll   = PI - (-asinf(Ryz));
  }

  /* get yaw from DCM */
  comp_data.heading = atan2f(Rxy, -Rxx) - PI - deg2rad(*declination);
  comp_data.heading = wrap_2pi(comp_data.heading);
  mavlink_attitude_struct->yaw = comp_data.heading;

  /* or from Z gyro for dbug reasons */
  //mavlink_attitude_struct->yaw          = -comp_data.zgyro_angle * PI / 180;

  mavlink_attitude_struct->rollspeed    = -gyro[0];
  mavlink_attitude_struct->pitchspeed   = -gyro[1];
  mavlink_attitude_struct->yawspeed     = -gyro[2];
  mavlink_attitude_struct->time_boot_ms = TIME_BOOT_MS;
}

/**
 *
 */
static void quat2attitude(mavlink_attitude_t *mavlink_attitude_struct,
                          float *gyro, Quaternion<float> *q){
  Vector<float, 3> e;
  mavlink_attitude_struct->time_boot_ms = TIME_BOOT_MS;
  q->euler(&e);

  mavlink_attitude_struct->pitch  = -e(2);
  mavlink_attitude_struct->roll   = -e(0);
  comp_data.heading = -e(1);
  mavlink_attitude_struct->yaw = comp_data.heading;

  mavlink_attitude_struct->rollspeed    = -gyro[0];
  mavlink_attitude_struct->pitchspeed   = -gyro[1];
  mavlink_attitude_struct->yawspeed     = -gyro[2];
  mavlink_attitude_struct->time_boot_ms = TIME_BOOT_MS;
}

/**
 *
 */
void IMU::update_still_msk(void){
  if(lsm303.still())
    still_msk |= STILL_MAG_MSK;
  else
    still_msk &= ~STILL_MAG_MSK;

  if(mma8451.still())
    still_msk |= STILL_ACC_MSK;
  else
    still_msk &= ~STILL_ACC_MSK;

  if(itg3200.still())
    still_msk |= STILL_GYRO_MSK;
  else
    still_msk &= ~STILL_GYRO_MSK;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 *
 */
IMU::IMU(void):
  itg3200(&I2CD2, itg3200addr),
  lsm303(&I2CD2,  lsm303magaddr),
  mma8451(&I2CD2, mma8451addr),
  retry(GYRO_RETRY)
{
  state = IMU_STATE_UNINIT;
  still_msk = 0;
  t0 = 0;
  t1 = 0;
  sem_status = RDY_OK;
  interval = 0.01;
};

/**
 *
 */
void IMU::start(void){
  declination = (const float*)param_registry.valueSearch("MAG_declinate");
  ahrsmode = (const uint32_t*)param_registry.valueSearch("IMU_ahrsmode");

  dcmInit();

  lsm303.start();
  mma8451.start();
  itg3200.start();
  ahrs.start();

  /* calibrate gyros in very first run */
  itg3200.trigCalibration();

  state = IMU_STATE_IDLE;
}

/**
 *
 */
void IMU::stop(void){
  lsm303.stop();
  mma8451.stop();
  itg3200.stop();
}

/**
 *
 */
imu_update_result_t IMU::update(StateVector *state_vector){

  sem_status = itg3200_sem.waitTimeout(GYRO_TIMEOUT);
  if (sem_status != RDY_OK){
    retry--;
    chDbgAssert(retry > 0, "PollGyroThread(), #1", "no interrupts from gyro");
    return IMU_UPDATE_RESULT_EMPTY;
  }

  state = IMU_STATE_UPDATING;

  itg3200.update(gyro, still_msk);
  lsm303.update(mag,   still_msk);
  mma8451.update(acc,  still_msk);

  this->update_still_msk();

  /* pass data to AHRS */
  if (0 == *ahrsmode){
    /* starlino DCM */
    t0 = hal_lld_get_counter_value();
    dcmUpdate(acc, gyro, mag, interval);
    t1 = hal_lld_get_counter_value() - t0;
    dcm2attitude(&mavlink_out_attitude_struct, gyro, declination);
  }
  else if (1 == *ahrsmode){
    /* Madgwick */
    t0 = hal_lld_get_counter_value();
    ahrs.update(gyro, acc, mag, &MadgwickQuat, interval);
    t1 = hal_lld_get_counter_value() - t0;
    quat2attitude(&mavlink_out_attitude_struct, gyro, &MadgwickQuat);
  }


  double dist_d;
  float dist_f;
  #define lat1 53.8946650
  #define lat2 53.8946700
  #define lon1 27.5601690
  #define lon2 27.5601700

  t0 = hal_lld_get_counter_value();
  dist_d = dist_cyrcle(deg2rad((double)lat1), deg2rad((double)lon1), deg2rad((double)lat2), deg2rad((double)lon2));
  dist_f = dist_cyrcle(deg2rad((float)lat1), deg2rad((float)lon1), deg2rad((float)lat2), deg2rad((float)lon2));
  // convert from radians to meters
  dist_d = rad2m(dist_d);
  dist_f = rad2m(dist_f);
  t1 = hal_lld_get_counter_value() - t0;




  state_vector->psi = comp_data.heading;
  log_write_schedule(MAVLINK_MSG_ID_ATTITUDE, NULL, 0);

  state = IMU_STATE_IDLE;
  return IMU_UPDATE_RESULT_OK;
}



