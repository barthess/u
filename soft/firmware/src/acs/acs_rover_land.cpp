#include <math.h>

#include "main.h"
#include "acs_rover.hpp"

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
 *
 */
acs_status_t ACSRover::loop_land(void){
  /* there is nothing special landing procedures for rover. Just navigate
   * to landing waypoint */
  state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
  return ACS_STATUS_OK;
}

