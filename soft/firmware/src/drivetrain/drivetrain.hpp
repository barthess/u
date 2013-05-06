#ifndef DRIVETRAIN_HPP_
#define DRIVETRAIN_HPP_

#include "sensors.hpp"

class Drivetrain{
public:
  void start(const Impact *impact);
  void update(void);
private:
  const Impact *impact;
};

#endif /* DRIVETRAIN_HPP_ */
