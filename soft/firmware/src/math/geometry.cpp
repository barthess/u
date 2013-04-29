#include <math.h>

#include "main.h"
#include "geometry.hpp"

#define DEG_TO_RAD  0.017453292519943296f
#define RAD_TO_DEG  57.295779513082321f

/**
 * convert from degrees to radians
 */
float fdeg2rad(float deg){
  return deg * DEG_TO_RAD;
}

/**
 * convert from degrees to radians
 */
float frad2deg(float rad){
  return rad * RAD_TO_DEG;
}

int32_t wrap_180(int32_t error){
  if (error > 180)
    error -= 360;
  else if (error < -180)
    error += 360;
  return error;
}

float wrap_pi(float error){
  if (error > PI)
    error -= 2*PI;
  else if (error < -PI)
    error += 2*PI;
  return error;
}

int32_t wrap_360(int32_t angle){
  if (angle > 360)
    angle -= 360;
  else if (angle < 0)
    angle += 360;
  return angle;
}

float wrap_2pi(float angle){
  if (angle > 2*PI)
    angle -= 2*PI;
  else if (angle < 0)
    angle += 2*PI;
  return angle;
}

/**
 * Suppose you are proceeding on a great circle route from A to B
 * (course =crs_AB) and end up at D, perhaps off course.
 * (We presume that A is not a pole!) You can calculate the course from
 * A to D (crs_AD) and the distance from A to D (dist_AD) using the
 * formulae above. In terms of these the cross track error, XTD,
 * (distance off course) is given by
 *
 * (positive XTD means right of course, negative means left)
 */
float crosstrack( float start_x,    float start_y,
                  float current_x,  float current_y,
                  float crs_AB){

  float crs_AD, dist_AD;
  float XTD;
  float delta_x, delta_y;

  delta_x = current_x - start_x;
  delta_y = current_y - start_y;
  dist_AD = sqrtf(delta_x*delta_x + delta_y*delta_y);

  crs_AD = atan2f(delta_y, delta_x);
  XTD = asinf(sinf(dist_AD) * sinf(crs_AD - crs_AB));
  return XTD;
}

