#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_
#include <stdint.h>

class Quaternion{
public:
  Quaternion(void);
  Quaternion(float q0, float q1, float q2, float q3);
  void conSelf(void);
  Quaternion con(void);
  float& operator[](uint32_t i);

private:
  float q[4];
};

Quaternion quatmult(Quaternion *q, Quaternion *r);

#endif /* QUATERNION_HPP_ */
