#include "main.h"
#include "message.hpp"
#include "mission_planner.hpp"

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
extern MissionPlanner     mission_planner;

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
    mission_planner.start(NORMALPRIO);
    break;

  case MAV_TYPE_FIXED_WING:
    chDbgPanic("Fixed wing mode not implemented yet");
    break;

  default:
    chDbgPanic("This mode is unsupported");
    break;
  }
}
