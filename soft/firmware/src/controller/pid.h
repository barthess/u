#ifndef PID_H_
#define PID_H_

/**
 * Float PID controller structure.
 */
typedef struct
{
  float dState;         /* Last position input */
  float iState;         /* Integrator state */
  float *iMax, *iMin;   /* Maximum and minimum allowable integrator state */
  float *iGain;         /* integral gain */
  float *pGain;         /* proportional gain */
  float *dGain;         /* derivative gain */
}pid_f32;

float UpdatePID(pid_f32 *pid, float error, float position);


#endif /* PID_H_ */
