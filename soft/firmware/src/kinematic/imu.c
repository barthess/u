#include <math.h>

#include "ch.h"
#include "hal.h"

#include "sensors.h"
#include "message.h"
#include "main.h"
#include "imu.h"
#include "link.h"
#include "param.h"
#include "itg3200.h"
#include "dcm.h"
#include "vector3d.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define PI          3.14159265f

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
//extern GlobalParam_t global_data[];
extern CompensatedData comp_data;
extern float dcmEst[3][3];
extern mavlink_attitude_t            mavlink_attitude_struct;

extern uint32_t imu_update_period;
uint32_t imu_step = 0;                /* incremented on each call to imu_update */
float dcmEst[3][3] = {{1,0,0},{0,1,0},{0,0,1}};   /* estimated DCM matrix */

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
void get_attitude(mavlink_attitude_t *mavlink_attitude_struct){
  mavlink_attitude_struct->time_boot_ms = TIME_BOOT_MS;
  if (Rzz >= 0){
    mavlink_attitude_struct->pitch        = -asinf(Rxz);
    mavlink_attitude_struct->roll         = -asinf(Ryz);
  }
  else{
    mavlink_attitude_struct->pitch        = PI - (-asinf(Rxz));
    mavlink_attitude_struct->roll         = PI - (-asinf(Ryz));
  }
  mavlink_attitude_struct->yaw            = atan2f(Rxy, -Rxx);
  //mavlink_attitude_struct->yaw          = -comp_data.zgyro_angle * PI / 180;

  mavlink_attitude_struct->rollspeed    = -comp_data.xgyro;
  mavlink_attitude_struct->pitchspeed   = -comp_data.ygyro;
  mavlink_attitude_struct->yawspeed     = -comp_data.zgyro;
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
 * Поток обработки инерациальных данных
 */
static WORKING_AREA(waImu, 1024);
static msg_t Imu(void *semp) {

  chRegSetThreadName("IMU");
  msg_t sem_status = RDY_TIMEOUT;
  float interval = 0; /* time between 2 gyro measurements */

  while (imu_update_period == 0){
    /* wait until giro sampling time measured */
    chThdSleepMilliseconds(10);
  }
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
  dcmInit();
  chThdCreateStatic(waImu, sizeof(waImu), NORMALPRIO, Imu, imu_semp);
}

/**
 * Сбрасывает всё рассчитанное инерциалкой в начальное состояние
 */
void ImuReset(void){

}


