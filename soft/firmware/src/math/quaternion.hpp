#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_

#include "matrix.hpp"

void Quat2Euler(double *q, double *e);
void Quat2Euler(float *q, float *e);

/**
 * Quaternion.
 *
 */
template<typename T>
class Quaternion : public Vector<T, 4>{

private:
  T m[4];

public:
  Quaternion(void) :
    Vector<T, 4>()
  {
  };

  Quaternion(T q0, T q1, T q2, T q3) :
    Vector<T, 4>()
  {
    m[0] = q0;
    m[1] = q1;
    m[2] = q2;
    m[3] = q3;
  };

  Quaternion(const T *initvector) :
    Vector<T, 4>(initvector)
  {
  };

  /**
   * @brief   complex conjugate. Modify data inplace
   */
  void ccon(void){
    m[1] = -m[1];
    m[2] = -m[2];
    m[3] = -m[3];
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
    const T *r = right->m;
    T *res = result->getArray();

    res[0] = m[0]*r[0] - m[1]*r[1] - m[2]*r[2] - m[3]*r[3];
    res[1] = m[1]*r[0] + m[0]*r[1] - m[3]*r[2] + m[2]*r[3];
    res[2] = m[2]*r[0] + m[3]*r[1] + m[0]*r[2] - m[1]*r[3];
    res[3] = m[3]*r[0] - m[2]*r[1] + m[1]*r[2] + m[0]*r[3];
  };
};

#endif /* QUATERNION_HPP_ */
