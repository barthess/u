#ifndef PID_H_
#define PID_H_

/**
 * Float PID controller structure.
 */
typedef struct{
  float dState;           /* Last position input */
  float iState;           /* Integrator state */
  float const *iMax;
  float const *iMin;      /* Maximum and minimum allowable integrator state */
  float const *iGain;     /* integral gain */
  float const *pGain;     /* proportional gain */
  float const *dGain;     /* derivative gain */
}pid_f32_t;


#define reset_pid(pid){ (pid)->iState = 0; (pid)->dState = 0; }

float UpdatePID(pid_f32_t *pid, float error, float position);


#endif /* PID_H_ */
