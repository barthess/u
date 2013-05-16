#ifndef ACS_ROVER_HPP_
#define ACS_ROVER_HPP_

#include "acs.hpp"

class ACSRover : public ACS{
public:
  ACSRover(const StateVector *in, Impact *out);
  void start(void);
  MAV_RESULT kill(void);

private:
  acs_status_t loop_loiter(void);
  acs_status_t loop_loiter_time(void);
  acs_status_t loop_loiter_turns(void);
  acs_status_t loop_loiter_unlim(void);
  acs_status_t loop_takeoff(void);
  acs_status_t loop_navigate(void);
  acs_status_t loop_navigate_local(void);
  acs_status_t loop_navigate_global(void);
  acs_status_t loop_passwp(void);
  acs_status_t loop_land(void);
  acs_status_t loop_pause(void);
  acs_status_t loop_idle(void);
  void pull_handbreak(void);

private:
  PIDControl<float> spdPID;
  PIDControl<float> hdgPID;
  PIDControl<float> xtdPID;
};


#endif /* ACS_ROVER_HPP_ */
