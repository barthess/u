#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "float.h"
#include "misc_math.hpp"

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
 * Great circle distance between 2 points
 */
template<typename T>
T dist_cyrcle(T lat1, T lon1, T lat2, T lon2){
  T dist;
  T slat;
  T slon;

  slat = sin((lat1 - lat2) / 2);
  slon = sin((lon1 - lon2) / 2);
  dist = sqrt(slat*slat + cos(lat1) * cos(lat2) * slon*slon);
  dist = putinrange(dist, 0.0f, 1.0f);
  return 2 * asin(dist);
}

/**
 * course between points
 */
template<typename T>
T course_cyrcle(T lat1, T lon1, T lat2, T lon2, T dist){
  /* We obtain the initial course, tc1, (at point 1) from point 1 to
  point 2 by the following. The formula fails if the initial point is a
  pole. We can special case this with: */
  float crs;

  if(cos(lat1) < FLT_EPSILON){
    if(lat1 > 0)
      return (T)PI;        //  starting from N pole
    else
      return 2 * (T)PI;       //  starting from S pole
  }

  /* For starting points other than the poles: */
  if(sin(lon2-lon1)<0){
    crs = (sin(lat2)-sin(lat1)*cos(dist))/(sin(dist)*cos(lat1));
    crs = putinrange(crs, -1.0f, 1.0f);
    crs = acos(crs);
  }
  else{
    crs = (sin(lat2)-sin(lat1)*cos(dist)) / (sin(dist)*cos(lat1));
    crs = putinrange(crs, -1.0f, 1.0f);
    crs = 2*(T)PI - acos(crs);
  }

  if (isnan(crs) || isinf(crs))
    return 0;
  else
    return crs;
}

/**
 * Other
 */
int32_t wrap_180(int32_t error);
float wrap_pi(float error);
int32_t wrap_360(int32_t angle);
float wrap_2pi(float angle);

#endif /* GEOMETRY_H_ */
