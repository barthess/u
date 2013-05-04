#ifndef DRIVETRAIN_HPP_
#define DRIVETRAIN_HPP_

#include "sensors.hpp"

class Drivetrain{
public:
  void update(const Impact *impact);
};

#endif /* DRIVETRAIN_HPP_ */
