#ifndef DRIVETRAIN_HPP_
#define DRIVETRAIN_HPP_

#include "sensors.hpp"

class Drivetrain{
public:
  Drivetrain(const Impact *impact);
  void start(void);
  void update(void);
private:
  const Impact *impact;
};

#endif /* DRIVETRAIN_HPP_ */
