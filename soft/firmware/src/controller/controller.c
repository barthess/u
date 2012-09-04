#include <math.h>

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
  int32_t tmp = 0;
  tmp = roundf((v + 1) * 128);
  return __USAT(tmp, 8);
}

/**
 * Convert from -0.2 .. 0.2 to uint8_t 0..255
 */
uint8_t float2servo(float v){
  int32_t tmp =0;
  tmp = roundf(128 * 5 * (v + 0.2));
  return __USAT(tmp, 8);
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
    if (ControllerGroundRoverInit() == NULL)
      chDbgPanic("Can not allocate memory");
    break;

  case MAV_TYPE_FIXED_WING:
    chDbgPanic("Fixed wing mode not implemented yet");
    if (ControllerFixedWingInit() == NULL)
      chDbgPanic("Can not allocate memory");
    break;

  default:
    chDbgPanic("This mode is unsupported");
    break;
  }
}

