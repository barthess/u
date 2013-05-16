#ifndef SINS_HPP_
#define SINS_HPP_

#include "sensors.hpp"


class SINS{
public:
  SINS(StateVector *in);
  void start(void);
  void update(void);
  void reset(void);

private:
  StateVector *in;
  uint32_t prev_odo;    // last measured odometer value
  float prev_hdg;       // previouse heading to imrove angle estimating
  float const *pulse2m;
};

#endif /* SINS_HPP_ */
