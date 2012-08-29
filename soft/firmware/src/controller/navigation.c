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
//extern RawData raw_data;
extern MemoryHeap ThdHeap;
//extern CompensatedData comp_data;
//extern mavlink_vfr_hud_t mavlink_vfr_hud_struct;
//extern Mailbox speedometer_mb;
//extern BinarySemaphore servo_updated_sem;
//extern Mailbox testpoint_mb;

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
 * Navigation thread.
 * 1) decide is task complete or not
 * 2) take new task from EEPROM
 * 3) place new task in message_box[1] for stabilization thread
 */
static WORKING_AREA(NavigationThreadWA, 256);
static msg_t NavigationThread(void* arg){
  chRegSetThreadName("Navigation");
  (void)arg;

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

Thread* NavigationInit(void){

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap, sizeof(NavigationThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            NavigationThread,
                            NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}
