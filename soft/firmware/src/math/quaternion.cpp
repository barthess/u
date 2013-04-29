#include <cmath>


void Quat2Euler(float *q, float *e){
  float Rlb23, Rlb22, Rlb31, Rlb11, Rlb21;

  Rlb23 = 2 * (q[2] * q[3] - q[0] * q[1]);
  Rlb22 = q[0]*q[0] - q[1]*q[1] + q[2]*q[2] - q[3]*q[3];
  Rlb31 = 2 * (q[1] * q[3] - q[0] * q[2]);
  Rlb11 = q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3]*q[3];
  Rlb21 = 2 * (q[0] * q[3] + q[1] * q[2]);

  e[0] = -atan2f(Rlb23,Rlb22);   //gamma крен
  e[1] = -atan2f(Rlb31,Rlb11);   //psi рыскание
  e[2] =  asinf(Rlb21);          //theta тангаж
}

void Quat2Euler(double *q, double *e){
  float Rlb23, Rlb22, Rlb31, Rlb11, Rlb21;

  Rlb23 = 2 * (q[2] * q[3] - q[0] * q[1]);
  Rlb22 = q[0]*q[0] - q[1]*q[1] + q[2]*q[2] - q[3]*q[3];
  Rlb31 = 2 * (q[1] * q[3] - q[0] * q[2]);
  Rlb11 = q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3]*q[3];
  Rlb21 = 2 * (q[0] * q[3] + q[1] * q[2]);

  e[0] = -atan2(Rlb23,Rlb22);   //gamma крен
  e[1] = -atan2(Rlb31,Rlb11);   //psi рыскание
  e[2] =  asin(Rlb21);          //theta тангаж
}
