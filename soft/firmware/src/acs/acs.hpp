#ifndef ACS_H_
#define ACS_H_

#include <stdint.h>
#include "mavlink.h"
#include "pid.hpp"
#include "sensors.hpp"

/**
 * @brief   Status of operation returned by ACS
 */
typedef enum {
  ACS_STATUS_OK,
  ACS_STATUS_NO_SUCH_WP,
  ACS_STATUS_LOADING_WP_FAILED,
  ACS_STATUS_ERROR,
}acs_status_t;

/**
 * @brief   State of ACS
 */
typedef enum {
  ACS_STATE_UNINIT,
  ACS_STATE_IDLE,
  ACS_STATE_TAKEOFF,
  ACS_STATE_NAVIGATE_TO_WAYPOINT,
  ACS_STATE_PASS_WAYPOINT,
  ACS_STATE_LOITER,
  ACS_STATE_LANDING,
  ACS_STATE_DEAD,
}acs_state_t;

/**
 *
 */
class ACS{
public:
  ACS(void){state = ACS_STATE_UNINIT;};
  void start(const StateVector *in, Impact *out);
  MAV_RESULT takeoff(mavlink_command_long_t *clp);
  MAV_RESULT loiter(mavlink_command_long_t *clp);
  MAV_RESULT owerwrite(mavlink_command_long_t *clp);
  MAV_RESULT kill(mavlink_command_long_t *clp);
  void setCurrentMission(mavlink_mission_set_current_t *sc);
  void setMode(mavlink_set_mode_t *sm);
  void manualControl(mavlink_manual_control_t *mc);
  acs_status_t update(void);

private:
  acs_status_t navigating(void);
  acs_status_t passing_wp(void);
  acs_status_t loitering(void);
  acs_status_t taking_off(void);
  mavlink_command_long_t cl;  // command currently executed
  const StateVector *in;
  Impact *out;
  PIDControl<float> spd;
  PIDControl<float> hdg;
  PIDControl<float> xtrack;
  float launch_lon; // cached value
  float launch_lat; // cached value
  acs_state_t state;

  float const *speed_min;
};

#endif /* ACS_H_ */
