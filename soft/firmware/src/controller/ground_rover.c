#include <math.h>

#include "uav.h"

#include "ground_rover.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define CONTROLLER_TMO    MS2ST(500)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
//extern RawData raw_data;
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
void manual_control_handler(mavlink_manual_control_t *mavlink_manual_control_struct){
  uint32_t v = 0;

  if (mavlink_manual_control_struct->thrust_manual == 1){
    v = float2thrust(mavlink_manual_control_struct->thrust);
    ServoCarThrustSet(v);
  }
  if (mavlink_manual_control_struct->yaw_manual == 1){
    v = float2servo(mavlink_manual_control_struct->yaw);
    Servo7Set(v);
  }
}

/**
 *
 */
static WORKING_AREA(ControllerThreadWA, 512);
static msg_t ControllerThread(void* arg){
  chRegSetThreadName("Ground_rover");
  (void)arg;

  Mail* mailp = NULL;
  msg_t tmp = 0;
  msg_t status = 0;

  while (TRUE) {
    status = chMBFetch(&controller_mb, &tmp, CONTROLLER_TMO);
    if (status == RDY_OK){
      mailp = (Mail*)tmp;

      switch(mailp->invoice){
      case MAVLINK_MSG_ID_MANUAL_CONTROL:
        manual_control_handler(mailp->payload);
        break;

      case MAVLINK_MSG_ID_SET_MODE:
        set_mode_handler(mailp->payload);
        break;
      }

      chBSemSignal(mailp->semp);
    }
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
Thread *ControllerGroundRoverInit(void){
  ServoInit();
  SpeedControlInit();

  Servo4Set(128);
  Servo5Set(128);
  Servo6Set(128);
  Servo7Set(128);
  ServoCarThrustSet(128);

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap, sizeof(ControllerThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            ControllerThread,
                            NULL);

  return tp;
}

