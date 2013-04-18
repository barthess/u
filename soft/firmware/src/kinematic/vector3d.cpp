#include <math.h>
#include "vector3d.hpp"

//get modulus of a 3d vector sqrt(x^2+y^2+z^2)
float vector3d_modulusf(float* v){
  return sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

//convert vector to a vector with same direction and modulus 1
void vector3d_normalizef(float* v){
  float R;
  R = vector3d_modulusf(v);
  v[0] /= R;
  v[1] /= R;
  v[2] /= R;
}

//calcuate vector dot-product  c = a . b
float vector3d_dotf(const float* a, const float* b) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

//calcuate vector cross-product  c = a x b
void vector3d_crossf(const float* a, const float* b, float* c){
  c[0] = a[1]*b[2] - a[2]*b[1];
  c[1] = a[2]*b[0] - a[0]*b[2];
  c[2] = a[0]*b[1] - a[1]*b[0];
}

//calcuate vector scalar-product  b = s x a
void vector3d_scalef(const float s, const float* a, float* b){
  b[0] = s*a[0];
  b[1] = s*a[1];
  b[2] = s*a[2];
}

//calcuate vector sum   c = a + b
void vector3d_addf(const float* a, const float* b, float* c){
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
}

//calcuate vector substraction c = a - b
void vector3d_subf(const float* a, const float* b, float* c){
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
}

/*****************************************************************************
 double precision counterparts
 *****************************************************************************/

//get modulus of a 3d vector sqrt(x^2+y^2+z^2)
double vector3d_modulus(double* v){
  return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

//convert vector to a vector with same direction and modulus 1
void vector3d_normalize(double* v){
  double R;
  R = vector3d_modulus(v);
  v[0] /= R;
  v[1] /= R;
  v[2] /= R;
}

//calcuate vector dot-product  c = a . b
double vector3d_dot(const double* a, const double* b) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

//calcuate vector cross-product  c = a x b
void vector3d_cross(const double* a, const double* b, double* c){
  c[0] = a[1]*b[2] - a[2]*b[1];
  c[1] = a[2]*b[0] - a[0]*b[2];
  c[2] = a[0]*b[1] - a[1]*b[0];
}

//calcuate vector scalar-product  b = s x a
void vector3d_scale(const double s, const double* a, double* b){
  b[0] = s*a[0];
  b[1] = s*a[1];
  b[2] = s*a[2];
}

//calcuate vector sum   c = a + b
void vector3d_add(const double* a, const double* b, double* c){
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
}

//calcuate vector substraction c = a - b
void vector3d_sub(const double* a, const double* b, double* c){
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
}
