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
 * Поток обработки инерациальных данных
 */
static WORKING_AREA(waImu, 256);
static msg_t Imu(void *arg) {
  (void)arg;
  chRegSetThreadName("IMU");
  msg_t sem_status = RDY_TIMEOUT;

  while (TRUE) {
    sem_status = chBSemWaitTimeout(&imu_sem, MS2ST(100));
    if (sem_status == RDY_OK){
      (void)itg3200_period;
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

  Mail tolink_mail = {NULL, MAVLINK_MSG_ID_RAW_IMU, NULL};

  uint32_t i = key_value_search("IMU_send_ms");

  while (TRUE) {
    chThdSleepMilliseconds(global_data[i].value);
    if (tolink_mail.payload == NULL){
      mavlink_raw_imu_struct.xgyro = floorf(comp_data.xgyro_angle);
      mavlink_raw_imu_struct.ygyro = floorf(comp_data.ygyro_angle);
      mavlink_raw_imu_struct.zgyro = floorf(comp_data.zgyro_angle);
//      mavlink_raw_imu_struct.xgyro      = raw_data.xgyro;
//      mavlink_raw_imu_struct.ygyro      = raw_data.ygyro;
//      mavlink_raw_imu_struct.zgyro      = raw_data.zgyro;

      mavlink_raw_imu_struct.time_usec  = TimeUsec;

      tolink_mail.payload = &mavlink_raw_imu_struct;
      chMBPost(&tolink_mb, (msg_t)&tolink_mail, TIME_IMMEDIATE);
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
  //dcmInit();
  chThdCreateStatic(waImu, sizeof(waImu), NORMALPRIO, Imu, NULL);
  chThdCreateStatic(waImuSender, sizeof(waImuSender), NORMALPRIO, ImuSender, NULL);
}

/**
 * Сбрасывает всё рассчитанное инерциалкой в начальное состояние
 */
void ImuReset(void){

}




