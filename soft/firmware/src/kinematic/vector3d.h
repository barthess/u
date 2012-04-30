/*
 *      Author: starlino
 *              http://www.starlino.com/dcm_tutorial.html
 */


#ifndef VECTOR3D__H
#define VECTOR3D__H


float vector3d_modulus(float* vector);
void vector3d_normalize(float* vector);
float vector3d_dot(float* a, float* b);
void vector3d_cross(float* a, float* b, float* c);
void vector3d_scale(float s, float* a , float* b);
void vector3d_add(float* a , float* b, float* c);
void vector3d_skew_plus_identity(float *v,float* m);


#endif /* VECTOR3D__H */
