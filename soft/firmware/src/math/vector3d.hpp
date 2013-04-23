#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include "misc_math.hpp"

//get modulus of a 3d vector sqrt(x^2+y^2+z^2)
inline double vector3d_modulus(double *v){
  return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

inline float vector3d_modulus(float *v){
  return sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

inline int32_t vector3d_modulus(int32_t *v){
  return sqrti(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

//convert vector to a vector with same direction and modulus 1
template <typename T>
void vector3d_normalize(T* v){
  T R;
  R = vector3d_modulus(v);
  v[0] /= R;
  v[1] /= R;
  v[2] /= R;
}

//calcuate vector dot-product  c = a . b
template <typename T>
T vector3d_dot(const T *a, T *b) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

//calcuate vector cross-product  c = a x b
template <typename T>
void vector3d_cross(const T *a, const T *b, T *c){
  c[0] = a[1]*b[2] - a[2]*b[1];
  c[1] = a[2]*b[0] - a[0]*b[2];
  c[2] = a[0]*b[1] - a[1]*b[0];
}

//calcuate vector scalar-product  b = s x a
template <typename T>
void vector3d_scale(const T s, const T *a, T *b){
  b[0] = s*a[0];
  b[1] = s*a[1];
  b[2] = s*a[2];
}

//calcuate vector sum   c = a + b
template <typename T>
void vector3d_add(const T *a, const T *b, T *c){
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
}

//calcuate vector substraction c = a - b
template <typename T>
void vector3d_sub(const T *a, const T *b, T *c){
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
}

#endif /* VECTOR3D_H */
