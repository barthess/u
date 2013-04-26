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

void Quaternion::conSelf(void){
  q[1] = -q[1];
  q[2] = -q[2];
  q[3] = -q[3];
}

float& Quaternion::operator[](uint32_t i){
  return q[i];
}

Quaternion Quaternion::con(void){
  Quaternion res;
  res[0] =  q[0];
  res[1] = -q[1];
  res[2] = -q[2];
  res[3] = -q[3];
  return res;
}

// function res = quatmult(q,r)
//      M = [q(1) -q(2) -q(3) -q(4);
//           q(2)  q(1) -q(4)  q(3);
//           q(3)  q(4)  q(1) -q(2);
//           q(4) -q(3)  q(2)  q(1)];
//      res = M*r;
//    end

Quaternion quatmult(Quaternion *q, Quaternion *r){
  Quaternion res;
  float m[16] = {q[0], -q[1], -q[2], -q[3],
                 q[1],  q[0], -q[3],  q[2],
                 q[2],  q[3],  q[0], -q[1],
                 q[3], -q[2],  q[1],  q[0]};
  //multiply matrix A (m x p) by  B(p x n) , put result in C (m x n)
//template <typename T>
//void matrix_multiply(const uint32_t m, const uint32_t p, const uint32_t n ,
//                     const T *A, const T *B, T *C){
  matrix_multiply(4,4,1, m, r, res);

  return res;
}


