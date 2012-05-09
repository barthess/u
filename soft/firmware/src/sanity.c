
/* Следит за состоянием здоровья органов.*/

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"
#include "link.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;
extern mavlink_sys_status_t mavlink_sys_status_struct;
extern uint32_t GlobalFlags;
extern EventSource pwrmgmt_event;
extern mavlink_system_t mavlink_system_struct;

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
/* for debugging purpose */
static Thread *tp = NULL;

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

  struct EventListener self_el;
  chEvtRegister(&pwrmgmt_event, &self_el, PWRMGMT_SIGHALT_EVID);

  mavlink_heartbeat_t mavlink_heartbeat_struct;
  Mail heartbeat_mail = {NULL, MAVLINK_MSG_ID_HEARTBEAT, NULL};

  mavlink_heartbeat_struct.autopilot = MAV_AUTOPILOT_GENERIC;
  mavlink_heartbeat_struct.type = mavlink_system_struct.type;
  mavlink_heartbeat_struct.custom_mode = 0;

  mavlink_sys_status_struct.onboard_control_sensors_enabled = mavlink_sys_status_struct.onboard_control_sensors_present;
  mavlink_sys_status_struct.onboard_control_sensors_health  = mavlink_sys_status_struct.onboard_control_sensors_present;
  mavlink_sys_status_struct.load = 231;

  while (TRUE) {
    palSetPad(GPIOB, GPIOB_LED_B);
    chThdSleepMilliseconds(950);

    if (heartbeat_mail.payload == NULL){
      mavlink_heartbeat_struct.base_mode = mavlink_system_struct.mode;
      mavlink_heartbeat_struct.system_status = mavlink_system_struct.state;
      heartbeat_mail.payload = &mavlink_heartbeat_struct;
      chMBPost(&tolink_mb, (msg_t)&heartbeat_mail, TIME_IMMEDIATE);

      palClearPad(GPIOB, GPIOB_LED_B); /* blink*/
      chThdSleepMilliseconds(50);
    }

    /* этим светодиодом будем обозначать процесс выставки гироскопов */
    if (GlobalFlags & GYRO_CAL_FLAG)
      palClearPad(GPIOB, GPIOB_LED_R);
    else
      palSetPad(GPIOB, GPIOB_LED_R);

    if (chThdSelf()->p_epending & EVENT_MASK(PWRMGMT_SIGHALT_EVID)){
      palClearPad(GPIOB, GPIOB_LED_B);
      palClearPad(GPIOB, GPIOB_LED_R);
      xbee_reset_assert();
      chThdExit(RDY_OK);
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

  tp = chThdCreateStatic(SanityControlThreadWA,
          sizeof(SanityControlThreadWA),
          NORMALPRIO,
          SanityControlThread,
          NULL);
}

