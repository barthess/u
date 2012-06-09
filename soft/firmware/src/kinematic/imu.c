#include <math.h>

#include "ch.h"
#include "hal.h"

#include "sensors.h"
#include "message.h"
#include "main.h"
#include "imu.h"
#include "link.h"
#include "logger.h"
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
extern CompensatedData comp_data;
extern mavlink_attitude_t mavlink_attitude_struct;
extern uint32_t imu_update_period;
extern Mailbox logwriter_mb;

uint32_t imu_step = 0;                /* incremented on each call to imu_update */
float dcmEst[3][3] = {{1,0,0},
                      {0,1,0},
                      {0,0,1}};   /* estimated DCM matrix */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static float *magypol, *magxpol;

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
  /* комплексированные данные из DCM */
  //mavlink_attitude_struct->yaw            = atan2f(Rxy, -Rxx);
  mavlink_attitude_struct->yaw = atan2f((*magypol) * Rxy, (*magxpol) * Rxx);

  /* либо данные чисто с гироскопа */
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
 * Поток обработки инерациальных данных
 */
static WORKING_AREA(waImu, 512);
static msg_t Imu(void *semp) {
  chRegSetThreadName("IMU");

  msg_t sem_status = RDY_TIMEOUT;
  float interval = 0; /* time between 2 gyro measurements */

  /* variables for regulate log writing frequency */
  uint32_t i = 0;
  const uint32_t decimator = 0b11;

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

      if (((i & decimator) == decimator) &&
              (chThdSelf()->p_epending & EVENT_MASK(LOGGER_READY_EVID))){
        log_write_schedule(MAVLINK_MSG_ID_ATTITUDE);
      }
      i++;
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
  magxpol = ValueSearch("MAG_xpol");
  magypol = ValueSearch("MAG_ypol");

  dcmInit();
  chThdCreateStatic(waImu, sizeof(waImu), NORMALPRIO, Imu, imu_semp);
}

/**
 *
 */
void ImuReset(void){

}


