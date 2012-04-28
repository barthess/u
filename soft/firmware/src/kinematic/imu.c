#include <math.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"
#include "imu.h"
#include "link.h"
#include "param.h"
#include "itg3200.h"
#include "dcm.h"

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
extern GlobalParam_t global_data[];
//extern RawData raw_data;
extern CompensatedData comp_data;
extern BinarySemaphore imu_sem;
extern uint32_t itg3200_period;
extern float dcmEst[3][3];

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static TimeMeasurement imu_tmup;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

static void get_attitude(mavlink_attitude_t *attitude_struct){
  attitude_struct->time_boot_ms = TIME_BOOT_MS;
  attitude_struct->pitch = asin(dcmEst[2][0]);
  attitude_struct->roll = asin(dcmEst[2][1]);
  attitude_struct->yaw = comp_data.zgyro_angle * PI / 180;
  attitude_struct->rollspeed = comp_data.xgyro;
  attitude_struct->pitchspeed = comp_data.ygyro;
  attitude_struct->yawspeed = comp_data.zgyro;
}

/**
 * Поток обработки инерациальных данных
 */
static WORKING_AREA(waImu, 1024);
static msg_t Imu(void *arg) {
  (void)arg;
  chRegSetThreadName("IMU");
  msg_t sem_status = RDY_TIMEOUT;
  float interval = 0; /* time between 2 gyro measurements */

  while (itg3200_period == 0){
    /* wait until giro sampling time measured */
    chThdSleepMilliseconds(10);
  }
  interval = (((float)itg3200_period)/1000000.0);

  while (TRUE) {
    sem_status = chBSemWaitTimeout(&imu_sem, MS2ST(100));
    if (sem_status == RDY_OK){
      dcmUpdate(((float)comp_data.xacc) / 1000,
                ((float)comp_data.yacc) / 1000,
                ((float)comp_data.zacc) / 1000,
                comp_data.xgyro,
                comp_data.ygyro,
                comp_data.zgyro,
                interval);
    }
  }
  return 0;
}


/**
 * Посылалка телеметрии
 */
static WORKING_AREA(waImuSender, 256);
static msg_t ImuSender(void *arg) {
  (void)arg;
  chRegSetThreadName("IMU_Sender");

  mavlink_attitude_t attitude_struct;
  Mail tolink_mail_raw_imu = {NULL, MAVLINK_MSG_ID_RAW_IMU, NULL};
  Mail tolink_mail_attitude = {NULL, MAVLINK_MSG_ID_ATTITUDE, NULL};
  uint32_t i = key_value_search("IMU_send_ms");

  while (TRUE) {
    chThdSleepMilliseconds(global_data[i].value);
    if (tolink_mail_raw_imu.payload == NULL){
      mavlink_raw_imu_struct.xgyro = floorf(comp_data.xgyro_angle);
      mavlink_raw_imu_struct.ygyro = floorf(comp_data.ygyro_angle);
      mavlink_raw_imu_struct.zgyro = floorf(comp_data.zgyro_angle);
//      mavlink_raw_imu_struct.xgyro      = raw_data.xgyro;
//      mavlink_raw_imu_struct.ygyro      = raw_data.ygyro;
//      mavlink_raw_imu_struct.zgyro      = raw_data.zgyro;

      mavlink_raw_imu_struct.time_usec  = TimeUsec;

      tolink_mail_raw_imu.payload = &mavlink_raw_imu_struct;
      chMBPost(&tolink_mb, (msg_t)&tolink_mail_raw_imu, TIME_IMMEDIATE);

      get_attitude(&attitude_struct);
      tolink_mail_attitude.payload = &attitude_struct;
      chMBPost(&tolink_mb, (msg_t)&tolink_mail_attitude, TIME_IMMEDIATE);
    }
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ImuInit(void){
  tmObjectInit(&imu_tmup);
  dcmInit();
  chThdCreateStatic(waImu, sizeof(waImu), NORMALPRIO, Imu, NULL);
  chThdCreateStatic(waImuSender, sizeof(waImuSender), NORMALPRIO, ImuSender, NULL);
}

/**
 * Сбрасывает всё рассчитанное инерциалкой в начальное состояние
 */
void ImuReset(void){

}




