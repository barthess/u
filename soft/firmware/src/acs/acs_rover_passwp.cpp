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
acs_status_t ACSRover::loop_passwp(void){
  chDbgPanic("unrealized");
  switch(mi.frame){
  /***********
   * Local NED
   ***********/
  case MAV_FRAME_LOCAL_NED:
    break;

  /****************
   * Global WGS-84
   ***************/
  case MAV_FRAME_GLOBAL:
    break;
  default:
    return ACS_STATUS_ERROR;
  }
  return ACS_STATUS_OK;
}
