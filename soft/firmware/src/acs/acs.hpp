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
  MAV_RESULT takeoff(mavlink_mission_item_t *mip);
  MAV_RESULT next(mavlink_mission_item_t *mip);
  /**
   * @brief   Emergency loiter
   */
  MAV_RESULT loiter(mavlink_command_long_t *clp);
  MAV_RESULT owerwrite(mavlink_mission_item_t *mip);
  MAV_RESULT kill(mavlink_mission_item_t *mip);
  void setCurrentMission(mavlink_mission_set_current_t *scp);
  void setMode(mavlink_set_mode_t *smp);
  void manualControl(mavlink_manual_control_t *mcp);
  acs_status_t update(void);

private:
  acs_status_t navigating(void);
  acs_status_t passing_wp(void);
  acs_status_t loitering(void);
  acs_status_t taking_off(void);
  bool is_wp_reached_local(void);
  mavlink_mission_item_t mi;        // mission item currently executed
  mavlink_mission_item_t mi_prev;   // previouse mission item to construct navigation path
  const StateVector *in;
  Impact *out;
  PIDControl<float> spd;
  PIDControl<float> hdg;
  PIDControl<float> xtrack;
  float launch_lon; // cached value
  float launch_lat; // cached value
  acs_state_t state;

  float const *speed_min, *pulse2m;
};

#endif /* ACS_H_ */
