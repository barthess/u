#include <math.h>

#include "uav.h"

#include "fixed_wing.h"
#include "ground_rover.h"

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
extern mavlink_system_t mavlink_system_struct;

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
 * Convert from float -1..1 value to uint8_t 0..255
 */
uint8_t float2thrust(float v){
  return __SSAT(roundf(256 * v), 9);
}

/**
 * Convert from -0.2 .. 0.2 to uint8_t 0..255
 */
uint8_t float2servo(float v){
  return __SSAT((roundf(128 * 5 * v) + 128), 9);
}

/**
 * Set autopilot mode logic.
 */
void set_mode_handler(mavlink_set_mode_t *mavlink_set_mode_struct){
  mavlink_system_struct.mode = mavlink_set_mode_struct->custom_mode |
                               mavlink_set_mode_struct->base_mode;
}

/**
 *
 */
void ControllerInit(void){
  switch (mavlink_system_struct.type){

  case MAV_TYPE_GROUND_ROVER:
    ControllerGroundRoverInit();
    break;

  case MAV_TYPE_FIXED_WING:
    ControllerFixedWingInit();
    break;

  default:
    chDbgPanic("This mode is unsupported");
    break;
  }
}

