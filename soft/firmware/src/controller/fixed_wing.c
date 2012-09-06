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
extern Mailbox controller_mb;
extern MemoryHeap ThdHeap;

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
    status = chMBFetch(&controller_mb, &tmp, CONTROLLER_TMO);
    if (status == RDY_OK){
      mailp = (Mail*)tmp;
      mavlink_manual_control_struct = mailp->payload;
      ReleaseMail(mailp);
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
Thread *ControllerFixedWingInit(void){

  Thread *tp = NULL;

  ServoInit();

  Servo0Set(128);
  Servo1Set(128);
  Servo2Set(128);
  Servo3Set(128);
  Servo4Set(128);
  Servo5Set(128);
  Servo6Set(128);
  Servo7Set(128);

  tp = chThdCreateFromHeap(&ThdHeap, sizeof(ControllerThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            ControllerThread,
                            NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}
