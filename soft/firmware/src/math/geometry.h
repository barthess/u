#ifndef GEOMETRY_H_
#define GEOMETRY_H_

float fdeg2rad(float deg);
float frad2deg(float rad);

int32_t wrap_180(int32_t error);
float wrap_pi(float error);
int32_t wrap_360(int32_t angle);
float wrap_2pi(float angle);

float crosstrack( float start_x,    float start_y,
                  float current_x,  float current_y,
                  float crs_AB);

#endif /* GEOMETRY_H_ */
