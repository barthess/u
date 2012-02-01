
/* Следит за состоянием здоровья органов.*/

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"

#include "mavlink.h"
#include "common.h"
#include "bart.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;
extern mavlink_sys_status_t mavlink_sys_status_struct;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SYS_STATUS_3D_GYRO   ((uint32_t)1 << 0)
#define SYS_STATUS_3D_ACCEL  ((uint32_t)1 << 1)
#define SYS_STATUS_3D_MAG    ((uint32_t)1 << 2)
#define SYS_STATUS_ABS_PRES  ((uint32_t)1 << 3)
#define SYS_STATUS_DIFF_PRES ((uint32_t)1 << 4)
#define SYS_STATUS_GPS       ((uint32_t)1 << 5)
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
static WORKING_AREA(SanityControlThreadWA, 256);
static msg_t SanityControlThread(void *arg) {
  chRegSetThreadName("Sanity");
  (void)arg;
  mavlink_heartbeat_t mavlink_heartbeat_struct;
  Mail heartbeat_mail = {NULL, MAVLINK_MSG_ID_HEARTBEAT, NULL};
  Mail sys_status_mail = {NULL, MAVLINK_MSG_ID_SYS_STATUS, NULL};

  mavlink_heartbeat_struct.autopilot = MAV_TYPE_FIXED_WING;
  mavlink_heartbeat_struct.base_mode = MAV_MODE_MANUAL_DISARMED;
  mavlink_heartbeat_struct.system_status = MAV_STATE_STANDBY;

  mavlink_sys_status_struct.onboard_control_sensors_enabled = mavlink_sys_status_struct.onboard_control_sensors_present;
  mavlink_sys_status_struct.onboard_control_sensors_health  = mavlink_sys_status_struct.onboard_control_sensors_present;

  while (TRUE) {
    palSetPad(GPIOB, GPIOB_LED_R);
    chThdSleepMilliseconds(950);

    if (sys_status_mail.payload == NULL){
      mavlink_sys_status_struct.load = 231;
      sys_status_mail.payload = &mavlink_sys_status_struct;
      chMBPost(&tolink_mb, (msg_t)&sys_status_mail, TIME_IMMEDIATE);
    }

    if (heartbeat_mail.payload == NULL){
      heartbeat_mail.payload = &mavlink_heartbeat_struct;
      chMBPost(&tolink_mb, (msg_t)&heartbeat_mail, TIME_IMMEDIATE);

      palClearPad(GPIOB, GPIOB_LED_R); /* blink*/
      chThdSleepMilliseconds(50);
    }

  }
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void SanityControlInit(void){

  mavlink_sys_status_struct.onboard_control_sensors_present = (
      SYS_STATUS_3D_GYRO | SYS_STATUS_3D_ACCEL | SYS_STATUS_3D_MAG |
      SYS_STATUS_ABS_PRES | SYS_STATUS_DIFF_PRES | SYS_STATUS_GPS);

  chThdCreateStatic(SanityControlThreadWA,
          sizeof(SanityControlThreadWA),
          NORMALPRIO,
          SanityControlThread,
          NULL);
}

