#ifndef GEOMETRY_H_
#define GEOMETRY_H_

//#include "arm_math.h"
#define PI          3.14159265358979323846
#define DEG_TO_RAD  0.017453292519943296
#define RAD_TO_DEG  57.295779513082321
#define RAD_TO_M    6.366707019493707E6

/**
 *
 */
template<typename T>
T deg2rad(T deg){
  return deg * (T)DEG_TO_RAD;
}

/**
 *
 */
template<typename T>
T rad2deg(T rad){
  return rad * (T)RAD_TO_DEG;
}

/**
 * Get meters from radians on earth sphere
 */
template<typename T>
T rad2m(T rad){
  return rad * (T)RAD_TO_M;
}

/**
 * Other
 */
int32_t wrap_180(int32_t error);
float wrap_pi(float error);
int32_t wrap_360(int32_t angle);
float wrap_2pi(float angle);

float crosstrack( float start_x,    float start_y,
                  float current_x,  float current_y,
                  float crs_AB);
float dist_cyrcle(float lat1, float lon1, float lat2, float lon2);
double dist_cyrcle(double lat1, double lon1, double lat2, double lon2);

#endif /* GEOMETRY_H_ */
