#ifndef CONTROLLER_H_
#define CONTROLLER_H_

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
uint8_t float2thrust(float v);
uint8_t float2servo(float v);
void set_mode_handler(mavlink_set_mode_t *mavlink_set_mode_struct);

void ControllerInit(void);


#endif /* CONTROLLER_H_ */
