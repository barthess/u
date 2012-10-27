#include <math.h>

#include "uav.h"

#include "dcm.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern CompensatedData comp_data;
extern mavlink_attitude_t mavlink_attitude_struct;
extern uint32_t imu_update_period;

float dcmEst[3][3] = {{1,0,0},
                      {0,1,0},
                      {0,0,1}};   /* estimated DCM matrix */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static float const *declinate;

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
static void get_attitude(mavlink_attitude_t *mavlink_attitude_struct){
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
  comp_data.heading = atan2f(Rxy, -Rxx) + PI - fdeg2rad(*declinate);
  comp_data.heading = wrap_2pi(comp_data.heading);
  mavlink_attitude_struct->yaw = comp_data.heading;

  /* or from Z gyro for dbug reasons */
  //mavlink_attitude_struct->yaw          = -comp_data.zgyro_angle * PI / 180;

  mavlink_attitude_struct->rollspeed    = -comp_data.xgyro;
  mavlink_attitude_struct->pitchspeed   = -comp_data.ygyro;
  mavlink_attitude_struct->yawspeed     = -comp_data.zgyro;
  mavlink_attitude_struct->time_boot_ms = TIME_BOOT_MS;
}


/**
 * Get attitude from DCM in quarterion notation
 */
//static void get_attitude_quaternion(mavlink_attitude_quaternion_t *mavlink_attitude_quaternion_struct){
//  // http://en.wikipedia.org/wiki/Rotation_matrix#Quaternion
//  float t = Rxx+Ryy+Rzz;
//  float r = sqrtf(1+t);
//  float s = 0.5 / r;
//  float w = 0.5*r;
//  float x = (Rzy - Ryz) * s;
//  float y = (Rxz - Rzx) * s;
//  float z = (Ryx - Rxy) * s;
//
//  mavlink_attitude_quaternion_struct->q1 = w;
//  mavlink_attitude_quaternion_struct->q2 = x;
//  mavlink_attitude_quaternion_struct->q3 = y;
//  mavlink_attitude_quaternion_struct->q4 = z;
//  mavlink_attitude_quaternion_struct->time_boot_ms = TIME_BOOT_MS;
//  mavlink_attitude_quaternion_struct->rollspeed    = -comp_data.xgyro;
//  mavlink_attitude_quaternion_struct->pitchspeed   = -comp_data.ygyro;
//  mavlink_attitude_quaternion_struct->yawspeed     = -comp_data.zgyro;
//}


/**
 *
 */
static WORKING_AREA(waImu, 400);
static msg_t Imu(void *semp) {
  chRegSetThreadName("IMU");

  msg_t sem_status = RDY_TIMEOUT;
  float interval = 0; /* time between 2 gyro measurements */

  /* variables for regulate log writing frequency */
  uint32_t i = 0;
  const uint32_t decimator = 0b11;

  /* wait until giro sampling time measured */
  while (imu_update_period == 0)
    chThdSleepMilliseconds(10);
  interval = (((float)imu_update_period)/1000000.0);

  while (TRUE) {
    sem_status = chBSemWaitTimeout((BinarySemaphore*)semp, MS2ST(100));
    if (sem_status == RDY_OK){
      dcmUpdate(((float)comp_data.xacc) / 1000,
                ((float)comp_data.yacc) / 1000,
                ((float)comp_data.zacc) / 1000,
                comp_data.xgyro,
                comp_data.ygyro,
                comp_data.zgyro,
                comp_data.xmag,
                comp_data.ymag,
                comp_data.zmag,
                interval);

      get_attitude(&mavlink_attitude_struct);
      log_write_schedule(MAVLINK_MSG_ID_ATTITUDE, &i, decimator);
    }
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ImuInit(BinarySemaphore *imu_semp){
  declinate = ValueSearch("MAG_declinate");

  dcmInit();
  chThdCreateStatic(waImu, sizeof(waImu), NORMALPRIO, Imu, imu_semp);
}

/**
 *
 */
void ImuReset(void){

}


