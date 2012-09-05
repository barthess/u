#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/**
 * Set the mission item with sequence number seq as current item.
 * This means that the MAV will continue to this mission item on the
 * shortest path (not following the mission items in-between)
 */
bool_t nav_set_current_wp(uint16_t seq){
  (void)seq;
  return WP_FAILED;//stub
}

/**
 * 1) decide if task complete or not
 * 2) take new task from EEPROM
 * 3) place new task in message_box[1] for stabilization thread
 */
static WORKING_AREA(NavThreadWA, 256);
static msg_t NavThread(void* arg){
  chRegSetThreadName("Nav");
  (void)arg;
//  msg_t status = RDY_RESET;
//  msg_t msg = 0;

  while (TRUE) {
    chThdSleepMilliseconds(20);
  }
  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

Thread* NavInit(void){

  Thread *tp = NULL;
  tp = chThdCreateStatic(NavThreadWA,
                        sizeof(NavThreadWA),
                        CONTROLLER_THREADS_PRIO,
                        NavThread,
                        NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}
