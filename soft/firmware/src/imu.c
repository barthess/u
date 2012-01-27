#include <math.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"
#include "imu.h"

#include <mavlink.h>
#include <common.h>
#include <bart.h>

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

extern uint32_t GlobalFlags;
extern Mailbox tolink_mb;
extern RawData raw_data;
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
      clearGlobalFlag(POSTAGE_FAILED);

      mavlink_raw_imu_struct.time_usec = 0;
      mavlink_raw_imu_struct.xacc = raw_data.acceleration_x;
      mavlink_raw_imu_struct.yacc = raw_data.acceleration_y;
      mavlink_raw_imu_struct.zacc = raw_data.acceleration_z;
      mavlink_raw_imu_struct.xgyro = raw_data.gyro_x;
      mavlink_raw_imu_struct.ygyro = raw_data.gyro_y;
      mavlink_raw_imu_struct.zgyro = raw_data.gyro_z;
      mavlink_raw_imu_struct.xmag = raw_data.magnetic_x;
      mavlink_raw_imu_struct.ymag = raw_data.magnetic_y;
      mavlink_raw_imu_struct.zmag = raw_data.magnetic_z;

      tolink_mail.payload = &mavlink_raw_imu_struct;
      chMBPost(&tolink_mb, (msg_t)&tolink_mail, TIME_IMMEDIATE);
    }
    else
      setGlobalFlag(POSTAGE_FAILED);

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




