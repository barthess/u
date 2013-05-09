#ifndef GREAT_CYRCLE_HPP_
#define GREAT_CYRCLE_HPP_

#include "geometry.hpp"
#include "ch.hpp"

/**
 * @brief   Object for great cyrcle navigation.
 * @note    All values in radians!
 */
template<typename T>
class NavigationSphere{
public:
  NavigationSphere(void){ready = false;};
  bool updatePoints(T latA, T lonA, T latB, T lonB);
  bool crosstrack(T latD, T lonD, T *xtd, T *atd);
  bool course(T latD, T lonD, T *crsres, T *distres);

private:
  T latA, lonA, latB, lonB; // radians
  T crsAB, distAB; // radians
  bool ready;
};

/**
 * @brief   Update points of path
 */
template<typename T>
bool NavigationSphere<T>::updatePoints(T latA, T lonA, T latB, T lonB){
  this->latA = latA;
  this->lonA = lonA;
  this->latB = latB;
  this->lonB = lonB;
  this->distAB = dist_cyrcle<T>(latA, lonA, latB, lonB);
  this->crsAB = course_cyrcle<T>(latA, lonA, latB, lonB, this->distAB);

  ready = true;
  return CH_SUCCESS;
}

/**
 * Suppose you are proceeding on a great circle route from A to B
 * (course =crs_AB) and end up at D, perhaps off course.
 * (We presume that A is not a pole!) You can calculate the course from
 * A to D (crs_AD) and the distance from A to D (dist_AD) using the
 * formulae above.
 *
 * (positive XTD means right of course, negative means left)
 */
template<typename T>
bool NavigationSphere<T>::crosstrack(T latD, T lonD, T *xtdres, T *atdres){
  chDbgCheck(true == ready, "no path loaded");

  T xtd, atd;
  T distAD = dist_cyrcle<T>(this->latA, this->lonA, latD, lonD);
  T crsAD = course_cyrcle<T>(this->latA, this->lonA, latD, lonD, distAD);


  /* We obtain the initial course, tc1, (at point 1) from point 1 to
  point 2 by the following. The formula fails if the initial point is a
  pole. We can special case this with: */
  if(cos(latA) < FLT_EPSILON){
    // starting from N pole
    if(latA > 0){
      xtd = asin(sin(distAD) * sin(lonD - this->lonB));
    }
    // starting from S pole
    else
      xtd = asin(sin(distAD) * sin(this->lonB - lonD));
  }
  else
    xtd = asin(sin(distAD) * sin(crsAD - this->crsAB));

  /* */
  if (distAD > 0.05)
    atd = acos(cos(distAD) / cos(xtd));
  else{
    //For very short distances:
    T sindist = sin(distAD);
    T sinxtd = sin(xtd);
    atd = sqrt(sindist*sindist - sinxtd*sinxtd);
    atd = asin(atd / cos(xtd));
  }
  *xtdres = xtd;
  *atdres = atd;

  return CH_SUCCESS;
}

/**
 * course from current point D to target point B
 */
template<typename T>
bool NavigationSphere<T>::course(T latD, T lonD, T *crsres, T *distres){
  T distDB = dist_cyrcle<T>(latD, lonD, this->latB, this->lonB);
  T crs = course_cyrcle<T>(latD, lonD, this->latB, this->lonB, distDB);
  *crsres = crs;
  *distres = distDB;
  return CH_SUCCESS;
}

/**
 * Object for navigation on plane
 */
template<typename T>
class NavigationPlane{
public:
  bool reset(T latA, T lonA, T latB, T lonB);
  bool crosstrack(T latD, T lonD, T *xtd, T *atd);

private:
  T latA, lonA, latB, lonB;
  T crsAB, distAB;
};



#endif /* GREAT_CYRCLE_HPP_ */
