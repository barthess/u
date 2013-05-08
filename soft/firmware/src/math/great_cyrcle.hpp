#ifndef GREAT_CYRCLE_HPP_
#define GREAT_CYRCLE_HPP_

#include "geometry.hpp"

/**
 * Creat cyrcle object
 */
template<typename T>
class GreatCyrcle{
  void reset(T latA, T lonA, T latB, T lonB);
  void crosstrack(T latD, T lonD, T *xtd, T *atd);
private:
  T latA, lonA, latB, lonB;
  T crsAB, distAB;
};

template<typename T>
void GreatCyrcle<T>::reset(T latA, T lonA, T latB, T lonB){
  this->latA = latA;
  this->lonA = lonA;
  this->latB = latB;
  this->lonB = lonB;
  this->distAB = dist_cyrcle(latA, lonA, latB, lonB);
  this->crsAB = course_cyrcle(latA, lonA, latB, lonB, this->distAB);
}

#endif /* GREAT_CYRCLE_HPP_ */
