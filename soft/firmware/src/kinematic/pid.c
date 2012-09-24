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

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
float UpdatePID(pid_f32_t *pid, float error, float position){
  float pTerm, dTerm, iTerm;

  /* calculate the proportional term */
  pTerm = *(pid->pGain) * error;

  /* calculate the integral state with appropriate limiting */
  pid->iState += error;
  if (pid->iState > *(pid->iMax))
      pid->iState = *(pid->iMax);
  else if (pid->iState < *(pid->iMin))
      pid->iState = *(pid->iMin);

  /* calculate the integral term */
  iTerm = *(pid->iGain) * pid->iState;

  /* calculate the derivative term */
  dTerm = *(pid->dGain) * (position - pid->dState);
  pid->dState = position;

  return (pTerm + iTerm - dTerm);
}

