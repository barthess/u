#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h

#include "quaternion.hpp"

class MadgwickAHRS{
public:
  MadgwickAHRS(void);
  void update(const float *gyro, const float *acc, const float *mag,
      Quaternion<float> *result, const float interval);
  void start(void);

private:
  bool ready;
  float const *beta, *zeta;
};


#endif /* MadgwickAHRS_h */
