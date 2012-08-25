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
 *
 */
float UpdatePID(pid_f32 *pid, float error, float position){
  float pTerm, dTerm, iTerm;

  /* calculate the proportional term */
  pTerm = *(pid->pGain) * error;

  /* calculate the integral state with appropriate limiting */
  pid->iState += error;
  if (pid->iState > pid->iMax)
      pid->iState = pid->iMax;
  else if (pid->iState < pid->iMin)
      pid->iState = pid->iMin;

  /* calculate the integral term */
  iTerm = *(pid->iGain) * pid->iState;

  /* calculate the derivative term */
  dTerm = *(pid->dGain) * (position - pid->dState);
  pid->dState = position;

  return (pTerm + iTerm - dTerm);
}

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
    if (ControllerGroundRoverInit() == NULL)
      chDbgPanic("Can not allocate memory");
    break;

  case MAV_TYPE_FIXED_WING:
    if (ControllerFixedWingInit() == NULL)
      chDbgPanic("Can not allocate memory");
    break;

  default:
    chDbgPanic("This mode is unsupported");
    break;
  }
}

