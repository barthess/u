#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_

#include "matrix.hpp"

inline void Quat2Euler(float *q, float *e){
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

inline void Quat2Euler(double *q, double *e){
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

/**
 * Quaternion.
 *
 */
template<typename T>
class Quaternion : public Vector<T, 4>{

public:
  Quaternion(void) :
    Vector<T, 4>()
  {
  };

  Quaternion(T q0, T q1, T q2, T q3) :
    Vector<T, 4>()
  {
    this->m[0] = q0;
    this->m[1] = q1;
    this->m[2] = q2;
    this->m[3] = q3;
  };

  Quaternion(const T *initvector) :
    Vector<T, 4>(initvector)
  {
  };

  Quaternion(T pattern) :
    Vector<T, 4>(pattern)
  {
  };

  /**
   * @brief   complex conjugate. Modify data inplace
   */
  void ccon(void){
    this->m[1] = -this->m[1];
    this->m[2] = -this->m[1];
    this->m[3] = -this->m[1];
  };

  /**
   * @brief   complex conjugate.
   */
  void ccon(Quaternion *result){
    result->m[0] =  this->m[0];
    result->m[1] = -this->m[1];
    result->m[2] = -this->m[2];
    result->m[3] = -this->m[3];
  };

  /**
   * @brief   Convert quaternion to euler angles.
   */
  void euler(Vector<T, 3> *e){
    Quat2Euler(this->m, e->getArray());
  };

  /**
   * @brief Quaternion multiplications
   */
  void mul(const Quaternion<T> *right, Quaternion<T> *result){
    chDbgCheck(((this != right) && (this != result) && (result != right)),
        "this function can not work inplace");

    const T *r = right->m;
    T *res = result->m;
    T *m = this->m;

    res[0] = m[0]*r[0] - m[1]*r[1] - m[2]*r[2] - m[3]*r[3];
    res[1] = m[1]*r[0] + m[0]*r[1] - m[3]*r[2] + m[2]*r[3];
    res[2] = m[2]*r[0] + m[3]*r[1] + m[0]*r[2] - m[1]*r[3];
    res[3] = m[3]*r[0] - m[2]*r[1] + m[1]*r[2] + m[0]*r[3];
  };
};

#endif /* QUATERNION_HPP_ */
