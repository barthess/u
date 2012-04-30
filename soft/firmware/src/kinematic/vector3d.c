/*
 *      Author: starlino
 *              http://www.starlino.com/dcm_tutorial.html
 */

#include <math.h>

//get modulus of a 3d vector sqrt(x^2+y^2+y^2)
float vector3d_modulus(float* vector){
  return sqrtf(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
}

//convert vector to a vector with same direction and modulus 1
void vector3d_normalize(float* vector){
  float R;
  R = vector3d_modulus(vector);
  vector[0] /= R;
  vector[1] /= R;
  vector[2] /= R;
}

//calcuate vector dot-product  c = a . b
float vector3d_dot(float* a, float* b) {
  return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

//calcuate vector cross-product  c = a x b
void vector3d_cross(float* a, float* b, float* c){
  c[0] = a[1]*b[2] - a[2]*b[1];
  c[1] = a[2]*b[0] - a[0]*b[2];
  c[2] = a[0]*b[1] - a[1]*b[0];
}

//calcuate vector scalar-product  n = s x a
void vector3d_scale(float s, float* a , float* b){
  b[0] = s*a[0];
  b[1] = s*a[1];
  b[2] = s*a[2];
}

//calcuate vector sum   c = a + b
void vector3d_add(float* a , float* b, float* c){
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
}

//creates equivalent skew symetric matrix plus identity
//for v = {x,y,z} returns
// m = {{1,-z,y}
//    {z,1,-x}
//    {-y,x,1}}
void vector3d_skew_plus_identity(float *v,float* m){
  m[0*3+0]=1;
  m[0*3+1]=-v[2];
  m[0*3+2]=v[1];
  m[1*3+0]=v[2];
  m[1*3+1]=1;
  m[1*3+2]=-v[0];
  m[2*3+0]=-v[1];
  m[2*3+1]=v[0];
  m[2*3+2]=1;
}


