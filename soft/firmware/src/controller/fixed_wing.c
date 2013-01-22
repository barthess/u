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
extern MemoryHeap ThdHeap;
extern EventSource event_mavlink_in_manual_control;
extern mavlink_manual_control_t mavlink_manual_control;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static Thread *fixedwing_tp = NULL;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

static void manual_control_handler(mavlink_manual_control_t *mavlink_manual_control){
  (void)mavlink_manual_control;
}

/**
 *
 */
static WORKING_AREA(ControllerThreadWA, 512);
static msg_t ControllerThread(void* arg){
  chRegSetThreadName("Fixed_wing");
  (void)arg;

  eventmask_t evt = 0;
  struct EventListener el_manual_control;
  chEvtRegisterMask(&event_mavlink_in_manual_control, &el_manual_control, EVMSK_MAVLINK_IN_MANUAL_CONTROL);

  while (!chThdShouldTerminate()) {
    evt = chEvtWaitOne(EVMSK_MAVLINK_IN_MANUAL_CONTROL);

    switch (evt){
      case EVMSK_MAVLINK_IN_MANUAL_CONTROL:
        manual_control_handler(&mavlink_manual_control);
        break;
      default:
        break;
    }
  }

  chEvtUnregister(&event_mavlink_in_manual_control,       &el_manual_control);

  chThdExit(0);
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
Thread *ControllerFixedWingInit(void){

  ServoInit();

  Servo0Set(128);
  Servo1Set(128);
  Servo2Set(128);
  Servo3Set(128);
  Servo4Set(128);
  Servo5Set(128);
  Servo6Set(128);
  Servo7Set(128);

  fixedwing_tp = chThdCreateFromHeap(&ThdHeap, sizeof(ControllerThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            ControllerThread,
                            NULL);
  if (fixedwing_tp == NULL)
    chDbgPanic("can not allocate memory");

  return NULL;
}
