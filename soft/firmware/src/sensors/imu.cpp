#include <math.h>

#include "uav.h"
#include "dcm.hpp"
#include "sensors.hpp"
#include "message.hpp"
#include "geometry.hpp"
#include "param_registry.hpp"
#include "logger.hpp"
#include "madgwick.hpp"

#include "itg3200.hpp"
#include "lsm303.hpp"
#include "mma8451.hpp"
#include "max1236.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define GYRO_TIMEOUT        MS2ST(100)

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
static float const *declination;
static ITG3200  itg3200(&I2CD2, itg3200addr);
static LSM303   lsm303(&I2CD2,  lsm303magaddr);
static MMA8451  mma8451(&I2CD2, mma8451addr);
static MyAHRS   my_ahrs;

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
static void calc_attitude(mavlink_attitude_t *mavlink_attitude_struct, float *gyro){
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
  comp_data.heading = atan2f(Rxy, -Rxx) + PI - fdeg2rad(*declination);
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
static WORKING_AREA(waImu, 512);
static msg_t Imu(void *arg) {
  (void)arg;
  chRegSetThreadName("IMU");

  msg_t sem_status = RDY_OK;
  int32_t retry = 10;

  float interval = 0.01;  /* time between 2 gyro measurements, S */
  float acc[3];           /* acceleration in G */
  float gyro[3];          /* angular rates in rad/s */
  float mag[3];           /* magnetic flux in T */

  lsm303.start();
  mma8451.start();
  itg3200.start();

  /* calibrate gyros in very first run */
  itg3200.startCalibration();

  while (!chThdShouldTerminate()) {
    sem_status = itg3200_sem.waitTimeout(GYRO_TIMEOUT);
    if (sem_status != RDY_OK){
      retry--;
      chDbgAssert(retry > 0, "PollGyroThread(), #1", "no interrupts from gyro");
    }

    itg3200.update(gyro, 3);
    lsm303.update(mag, 3);
    mma8451.update(acc, 3);

    /* if gyro calibration in process */
    if (itg3200.isCalibrating()){
      /* check immobility and restart if needed */
      if (!(lsm303.still() && mma8451.still())){
        itg3200.startCalibration();
      }
    }

    dcmUpdate(acc, gyro, mag, interval);
    MadgwickAHRSupdate(gyro[0],gyro[1],gyro[2],acc[0],acc[1],acc[2],mag[0],mag[1],mag[2]);
    my_ahrs.update(acc, gyro, mag);

    calc_attitude(&mavlink_out_attitude_struct, gyro);
    log_write_schedule(MAVLINK_MSG_ID_ATTITUDE, NULL, 0);
  }

  lsm303.stop();
  mma8451.stop();
  itg3200.stop();

  chThdExit(0);
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ImuInit(void){
  declination = (const float*)param_registry.valueSearch("MAG_declinate");

  dcmInit();
  chThdCreateStatic(waImu, sizeof(waImu), NORMALPRIO, Imu, NULL);
}

/**
 *
 */
bool ImuTrigCalibrateGyro(void){
  return CH_FAILED;
}

/**
 *
 */
bool ImuTrigCalibrateMag(void){
  return lsm303.trigCal();
}

/**
 *
 */
bool IsDeviceStill(void){
  return true;
}

/**
 *
 */
void ImuReset(void){

}


