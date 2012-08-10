#include <math.h>

#include "uav.h"

#include "fixed_wing.h"

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
  chRegSetThreadName("Fixed_wing");
  (void)arg;

  msg_t tmp = 0;
  msg_t status = 0;
  Mail* mailp = NULL;
  mavlink_manual_control_t *mavlink_manual_control_struct = NULL;

  while (TRUE) {
    status = chMBFetch(&mavlink_manual_control_mb, &tmp, CONTROLLER_TMO);
    if (status == RDY_OK){
      mailp = (Mail*)tmp;
      mavlink_manual_control_struct = mailp->payload;
      chBSemSignal(mailp->sem);
    }
    else{
      /* testing values */
      Servo4Set(0);
      Servo5Set(64);
      Servo6Set(128);
      Servo7Set(255);
    }
  }
  (void)mavlink_manual_control_struct;
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void ControllerFixedWingInit(void){

  chThdCreateStatic(ControllerThreadWA,
        sizeof(ControllerThreadWA),
        NORMALPRIO,
        ControllerThread,
        NULL);
}
