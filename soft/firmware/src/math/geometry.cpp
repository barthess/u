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
 * Great circle distance between 2 points
 */
float dist_cyrcle(float lat1, float lon1, float lat2, float lon2){
  float dist;
  float slat;
  float slon;

  // A mathematically equivalent formula, which is less subject to
  // rounding error for short distances
  slat = sinf((lat1 - lat2) / 2);
  slon = sinf((lon1 - lon2) / 2);
  dist = sqrtf(slat*slat + cosf(lat1) * cosf(lat2) * slon*slon);
  putinrange(dist, -1.0f, 1.0f);
  return 2 * asinf(dist);
}

double dist_cyrcle(double lat1, double lon1, double lat2, double lon2){
  double dist;
  double slat;
  double slon;

  // A mathematically equivalent formula, which is less subject to
  // rounding error for short distances
  slat = sin((lat1 - lat2) / 2);
  slon = sin((lon1 - lon2) / 2);
  dist = sqrt(slat*slat + cos(lat1) * cos(lat2) * slon*slon);
  putinrange(dist, (double)-1.0, (double)1.0);
  return 2 * asin(dist);
}

/**
 * course between points
 */
double course_cyrcle(double lat1, double lon1, double lat2, double lon2, double dist){
  /* We obtain the initial course, tc1, (at point 1) from point 1 to
  point 2 by the following. The formula fails if the initial point is a
  pole. We can special case this with: */
  if(cos(lat1) < DBL_EPSILON){
    if(lat1 > 0)
       return PI;        //  starting from N pole
    else
       return 2*PI;       //  starting from S pole
  }

  /* For starting points other than the poles: */
  if(sin(lon2-lon1)<0)
    return acos((sin(lat2)-sin(lat1)*cos(dist))/(sin(dist)*cos(lat1)));
  else
   return 2*(double)PI - acos((sin(lat2)-sin(lat1)*cos(dist))/(sin(dist)*cos(lat1)));
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
float crosstrack_great_circle(float Alat, float Alon,
                              float Blat, float Blon,
                              float Dlat, float Dlon,
                              float ABcrs){
  float dist_AD = dist_cyrcle(Alat, Alon, Dlat, Dlon);
  float crs_AD = course_cyrcle(Alat, Alon, Dlat, Dlon, dist_AD);

  float xtd = asin(sin(dist_AD) * sin(crs_AD-ABcrs));
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

