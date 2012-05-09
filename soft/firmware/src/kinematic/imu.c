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
extern Mailbox tolink_mb;
extern uint64_t TimeUsec;
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern GlobalParam_t global_data[];
extern CompensatedData comp_data;
extern uint32_t itg3200_period;
extern float dcmEst[3][3];

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

static void get_attitude(mavlink_attitude_t *mavlink_attitude_struct){
  mavlink_attitude_struct->time_boot_ms = TIME_BOOT_MS;
  if (Rzz >= 0){
    mavlink_attitude_struct->pitch        = -asin(Rxz);
    mavlink_attitude_struct->roll         = -asin(Ryz);
  }
  else{
    mavlink_attitude_struct->pitch        = PI - (-asin(Rxz));
    mavlink_attitude_struct->roll         = PI - (-asin(Ryz));
  }
  mavlink_attitude_struct->yaw          = atan2(Rxy, Rxx);
  //mavlink_attitude_struct->yaw          = -comp_data.zgyro_angle * PI / 180;

  mavlink_attitude_struct->rollspeed    = -comp_data.xgyro;
  mavlink_attitude_struct->pitchspeed   = -comp_data.ygyro;
  mavlink_attitude_struct->yawspeed     = -comp_data.zgyro;
}

/**
 * Поток обработки инерациальных данных
 */
static WORKING_AREA(waImu, 1024);
static msg_t Imu(void *semp) {

  chRegSetThreadName("IMU");
  msg_t sem_status = RDY_TIMEOUT;
  float interval = 0; /* time between 2 gyro measurements */

  while (itg3200_period == 0){
    /* wait until giro sampling time measured */
    chThdSleepMilliseconds(10);
  }
  interval = (((float)itg3200_period)/1000000.0);

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
    }
  }
  return 0;
}


/**
 * Посылалка телеметрии
 */
static WORKING_AREA(waImuSender, 512);
static msg_t ImuSender(void *arg) {
  (void)arg;
  chRegSetThreadName("IMU_Sender");

  mavlink_attitude_t mavlink_attitude_struct;
  Mail tolink_mail_raw_imu = {NULL, MAVLINK_MSG_ID_RAW_IMU, NULL};
  Mail tolink_mail_scaled_imu = {NULL, MAVLINK_MSG_ID_SCALED_IMU, NULL};
  Mail tolink_mail_attitude = {NULL, MAVLINK_MSG_ID_ATTITUDE, NULL};

  uint32_t i = KeyValueSearch("IMU_send_ms");

  while (TRUE) {
    chThdSleepMilliseconds(global_data[i].value);
    if (tolink_mail_raw_imu.payload == NULL){

      mavlink_raw_imu_struct.time_usec  = TimeUsec;
      tolink_mail_raw_imu.payload = &mavlink_raw_imu_struct;
      chMBPost(&tolink_mb, (msg_t)&tolink_mail_raw_imu, TIME_IMMEDIATE);

      get_attitude(&mavlink_attitude_struct);
      tolink_mail_attitude.payload = &mavlink_attitude_struct;
      chMBPost(&tolink_mb, (msg_t)&tolink_mail_attitude, TIME_IMMEDIATE);

      mavlink_scaled_imu_struct.time_boot_ms = TIME_BOOT_MS;
      tolink_mail_scaled_imu.payload = &mavlink_scaled_imu_struct;
      chMBPost(&tolink_mb, (msg_t)&tolink_mail_scaled_imu, TIME_IMMEDIATE);
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
  chThdCreateStatic(waImuSender, sizeof(waImuSender), NORMALPRIO, ImuSender, NULL);
}

/**
 * Сбрасывает всё рассчитанное инерциалкой в начальное состояние
 */
void ImuReset(void){

}




