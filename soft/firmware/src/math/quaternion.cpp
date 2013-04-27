#include "quaternion.hpp"
#include "matrix.hpp"

Quaternion::Quaternion(void){
  for (uint32_t i=0; i<sizeof(q)/sizeof(q[0]); i++)
    q[i] = 0;
}

Quaternion::Quaternion(float q0, float q1, float q2, float q3){
  q[0] = q0;
  q[1] = q1;
  q[2] = q2;
  q[3] = q3;
}

/* complex conjugate */
void Quaternion::ccon(void){
  q[1] = -q[1];
  q[2] = -q[2];
  q[3] = -q[3];
}

float& Quaternion::operator[](uint32_t i){
  return q[i];
}

/* complex conjugate */
void Quaternion::ccon(Quaternion *result){
  result[0] =  q[0];
  result[1] = -q[1];
  result[2] = -q[2];
  result[3] = -q[3];
}

/* quaternion multiplication in right handled coordinate system */
void QuatMult(float *q, float *r, float *result){
  result[0] = q[0]*r[0] - q[1]*r[1] - q[2]*r[2] - q[3]*r[3];
  result[1] = q[1]*r[0] + q[0]*r[1] - q[3]*r[2] + q[2]*r[3];
  result[2] = q[2]*r[0] + q[3]*r[1] + q[0]*r[2] - q[1]*r[3];
  result[3] = q[3]*r[0] - q[2]*r[1] + q[1]*r[2] + q[0]*r[3];
}

