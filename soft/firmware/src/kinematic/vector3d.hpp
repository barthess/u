#ifndef VECTOR3D_H
#define VECTOR3D_H

float vector3d_modulusf(float* v);
void vector3d_normalizef(float* v);
float vector3d_dotf(const float* a, const float* b);
void vector3d_crossf(const float* a, const float* b, float* c);
void vector3d_scalef(const float s, const float* a, float* b);
void vector3d_addf(const float* a, const float* b, float* c);
void vector3d_subf(const float* a, const float* b, float* c);

double vector3d_modulus(double* v);
void vector3d_normalize(double* v);
double vector3d_dot(const double* a, const double* b);
void vector3d_cross(const double* a, const double* b, double* c);
void vector3d_scale(const double s, const double* a , double* b);
void vector3d_add(const double* a , const double* b, double* c);
void vector3d_sub(const double* a, const double* b, double* c);

#endif /* VECTOR3D_H */
