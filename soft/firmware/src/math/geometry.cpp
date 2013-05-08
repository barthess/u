/*
 * Bearing Between Two Points:
 * http://mathforum.org/library/drmath/view/55417.html
 *
 * Aviation Formulary V1.46:
 * http://williams.best.vwh.net/avform.htm
 *
 * what is crosstrack error in pictures
 * http://diydrones.com/profiles/blogs/705844:BlogPost:43438
 *
 * Calculate distance, bearing and more between Latitude/Longitude points
 * http://www.movable-type.co.uk/scripts/latlong.html
 */

#include <math.h>

#include "main.h"
#include "float.h"
#include "geometry.hpp"
#include "misc_math.hpp"

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
 *
 */
float crosstrack_plane( float start_x,    float start_y,
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

