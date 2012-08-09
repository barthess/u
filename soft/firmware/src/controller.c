#include <math.h>

#include "uav.h"

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
Thread *autopilot_tp = NULL;
static msg_t ControllerThread(void* arg){
  chRegSetThreadName("Controller");
  (void)arg;

  uint32_t i = 0;
  Mail* mailp = NULL;
  mavlink_manual_control_t *mavlink_manual_control_struct = NULL;
  msg_t tmp = 0;
  msg_t status = 0;
  uint32_t trust = 0;

  while (TRUE) {
    status = chMBFetch(&mavlink_manual_control_mb, &tmp, CONTROLLER_TMO);
    if (status == RDY_OK){
      mailp = (Mail*)tmp;
      mavlink_manual_control_struct = mailp->payload;

      if (mavlink_manual_control_struct->thrust_manual == 1)
        trust = __SSAT((roundf(128 * mavlink_manual_control_struct->thrust) + 128), 7);
      ServoCarThrottleSet(trust);

      chBSemSignal(mailp->sem);
    }
    else{
      /* testing values */
      Servo4Set(0);
      Servo5Set(64);
      Servo6Set(128);
      Servo7Set(255);
      ServoCarThrottleSet((i >> 2) & 0xFF);
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
void ControllerInit(void){

  chThdCreateStatic(ControllerThreadWA,
        sizeof(ControllerThreadWA),
        NORMALPRIO,
        ControllerThread,
        NULL);
}
