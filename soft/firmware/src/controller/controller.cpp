#include <math.h>

#include "uav.h"
#include "message.hpp"
#include "misc_math.hpp"
#include "ground_rover.hpp"
#include "fixed_wing.hpp"

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
extern mavlink_vfr_hud_t  mavlink_out_vfr_hud_struct;

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

  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    putinrange(v, 0.0f, 1.0f);
    mavlink_out_vfr_hud_struct.throttle = roundf(v * 100);
  }
  else{
    putinrange(v, -1.0f, 1.0f);
    mavlink_out_vfr_hud_struct.throttle = roundf((v + 1.0f) * 50);
  }

  return __USAT(tmp, 8);
}

/**
 * Convert from -0.2 .. 0.2 to uint8_t 0..255
 */
uint8_t float2servo(float v){
  int32_t tmp =0;
  tmp = roundf(128 * 5 * (v + 0.2f));
  return __USAT(tmp, 8);
}

/**
 * Set autopilot mode logic.
 */
void set_mode_handler(mavlink_set_mode_t *sm){
  mavlink_system_struct.mode = sm->custom_mode | sm->base_mode;
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

