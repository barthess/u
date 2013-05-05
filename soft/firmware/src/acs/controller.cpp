#include "main.h"
#include "message.hpp"
#include "mission_planner.hpp"
#include "speedometer.hpp"

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
extern mavlink_system_t   mavlink_system_struct;
extern MissionPlanner     mav_executor;

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

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 *
 */
void ControllerInit(void){
  switch (mavlink_system_struct.type){

  case MAV_TYPE_GROUND_ROVER:
    /* create thread handling all commands from ground */
    mav_executor.start(NORMALPRIO);
    SpeedometerInit();
    break;

  case MAV_TYPE_FIXED_WING:
    chDbgPanic("Fixed wing mode not implemented yet");
    break;

  default:
    chDbgPanic("This mode is unsupported");
    break;
  }
}

