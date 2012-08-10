#include <math.h>

#include "uav.h"

#include "ground_rover.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define CONTROLLER_TMO  MS2ST(500)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox mavlink_manual_control_mb;

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
 *
 */
static WORKING_AREA(ControllerThreadWA, 512);
static msg_t ControllerThread(void* arg){
  chRegSetThreadName("Ground_rover");
  (void)arg;

  Mail* mailp = NULL;
  mavlink_manual_control_t *mavlink_manual_control_struct = NULL;
  msg_t tmp = 0;
  msg_t status = 0;
  uint32_t thrust = 0;

  while (TRUE) {
    status = chMBFetch(&mavlink_manual_control_mb, &tmp, CONTROLLER_TMO);
    if (status == RDY_OK){
      mailp = (Mail*)tmp;
      mavlink_manual_control_struct = mailp->payload;

      if (mavlink_manual_control_struct->thrust_manual == 1){
        thrust = float2thrust(mavlink_manual_control_struct->thrust);
        ServoCarThrottleSet(thrust);
      }

      chBSemSignal(mailp->sem);
    }
    else{
    }
  }
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ControllerGroundRoverInit(void){

  Servo4Set(128);
  Servo5Set(128);
  Servo6Set(128);
  Servo7Set(128);
  ServoCarThrottleSet(128);

  chThdCreateStatic(ControllerThreadWA,
        sizeof(ControllerThreadWA),
        NORMALPRIO,
        ControllerThread,
        NULL);
}
