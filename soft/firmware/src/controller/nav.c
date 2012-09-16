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

int32_t wrap_180(int32_t error){
  if (error > 180)
    error -= 360;
  if (error < -180)
    error += 360;
  return error;
}

float wrap_pi(float error){
  if (error > PI)
    error -= 2*PI;
  if (error < -PI)
    error += 2*PI;
  return error;
}

int32_t wrap_360(int32_t angle){
  if (angle > 360)
    angle -= 360;
  if (angle < 0)
    angle += 360;
  return angle;
}

float wrap_2pi(float angle){
  if (angle > 2*PI)
    angle -= 2*PI;
  if (angle < 0)
    angle += 2*PI;
  return angle;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

