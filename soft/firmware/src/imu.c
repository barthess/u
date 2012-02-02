#include <math.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"
#include "imu.h"
#include "link.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;
extern uint64_t TimeUsec;
extern mavlink_raw_imu_t mavlink_raw_imu_struct;

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
  Mail tolink_mail = {NULL, MAVLINK_MSG_ID_RAW_IMU, NULL};

  while (TRUE) {
    chThdSleepMilliseconds(100);
    if (tolink_mail.payload == NULL){
      mavlink_raw_imu_struct.time_usec = TimeUsec;
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
  chThdCreateStatic(waImu, sizeof(waImu), NORMALPRIO, Imu, NULL);
}

/**
 * Сбрасывает всё рассчитанное инерциалкой в начальное состояние
 */
void ImuReset(void){

}




