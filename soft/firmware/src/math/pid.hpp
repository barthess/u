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



template <typename T>
class PIDControl{
public:
  /**
   *
   */
  void reset(void){
    iState = 0;
    dState = 0;
  };
  /**
   *
   */
  void start(T const *iMax,  T const *iMin,  T const *iGain,
             T const *pGain, T const *dGain){
    this->iMax = iMax;
    this->iMin = iMin;
    this->iGain = iGain;
    this->pGain = pGain;
    this->dGain = dGain;
  };
  /**
   *
   */
  T update(T error, T position);

private:
  T dState;           /* Last position input */
  T iState;           /* Integrator state */
  T const *iMax;
  T const *iMin;      /* Maximum and minimum allowable integrator state */
  T const *iGain;     /* integral gain */
  T const *pGain;     /* proportional gain */
  T const *dGain;     /* derivative gain */
};

/**
 * normal update
 */
template<typename T>
T PIDControl<T>::update(T error, T position){
  T pTerm, dTerm, iTerm;

  /* calculate the proportional term */
  pTerm = *pGain * error;

  /* calculate the integral state with appropriate limiting */
  iState += error;
  if (iState > *iMax)
      iState = *iMax;
  else if (iState < *iMin)
      iState = *iMin;

  /* calculate the integral term */
  iTerm = *iGain * iState;

  /* calculate the derivative term */
  dTerm = *dGain * (position - dState);
  dState = position;

  return (pTerm + iTerm - dTerm);
};


#endif /* PID_H_ */
