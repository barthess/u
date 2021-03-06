#ifndef PID_H_
#define PID_H_


template <typename T>
class PIDControl{
public:
  PIDControl(void){
    iState = 0;
    dState = 0;
  };
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
  void start(T const *iMin,  T const *iMax,
             T const *pGain, T const *iGain, T const *dGain){
    this->iMin = iMin;
    this->iMax = iMax;
    this->pGain = pGain;
    this->iGain = iGain;
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
