#ifndef ACS_H_
#define ACS_H_

#include <stdint.h>
#include "mavlink.h"
#include "pid.hpp"
#include "sensors.hpp"
#include "navigation.hpp"

/**
 * @brief   Status of operation returned by ACS
 */
typedef enum {
  ACS_STATUS_OK,
  ACS_STATUS_NO_MISSION,
  ACS_STATUS_ERROR,
}acs_status_t;

/**
 * @brief   State of ACS
 */
typedef enum {
  ACS_STATE_UNINIT,
  ACS_STATE_IDLE,
  ACS_STATE_TAKEOFF,
  ACS_STATE_LOAD_MISSION_ITEM,
  ACS_STATE_NAVIGATE_TO_WAYPOINT,
  ACS_STATE_PASS_WAYPOINT,
  ACS_STATE_LOITER,
  ACS_STATE_PAUSE,
  ACS_STATE_LAND,
  ACS_STATE_DEAD,
}acs_state_t;

/**
 *
 */
class ACS{
public:
  ACS(const StateVector *in, Impact *out);
  acs_status_t update(void);
  MAV_RESULT takeoff(void);
  MAV_RESULT goHome(void);
  MAV_RESULT returnToLaunch(mavlink_command_long_t *clp);
  MAV_RESULT overrideGoto(mavlink_command_long_t *clp);
  MAV_RESULT emergencyGotoLand(mavlink_command_long_t *clp);
  MAV_RESULT setCurrentMission(mavlink_mission_set_current_t *scp);
  void setMode(mavlink_set_mode_t *smp);
  void manualControl(mavlink_manual_control_t *mcp);

public:
  virtual void start(void) = 0;
  virtual MAV_RESULT kill(void) = 0;

private:
  acs_status_t loop_load_mission_item(void);
  MAV_RESULT jump_to(uint16_t seq);

private:
  virtual acs_status_t loop_loiter(void) = 0;
  virtual acs_status_t loop_loiter_time(void) = 0;
  virtual acs_status_t loop_loiter_turns(void) = 0;
  virtual acs_status_t loop_loiter_unlim(void) = 0;
  virtual acs_status_t loop_takeoff(void) = 0;
  virtual acs_status_t loop_navigate(void) = 0;
  virtual acs_status_t loop_navigate_local(void) = 0;
  virtual acs_status_t loop_navigate_global(void) = 0;
  virtual acs_status_t loop_passwp(void) = 0;
  virtual acs_status_t loop_land(void) = 0;
  virtual acs_status_t loop_pause(void) = 0;
  virtual acs_status_t loop_idle(void) = 0;

protected:
  void broadcast_mission_current(uint16_t seq);
  void broadcast_mission_item_reached(uint16_t seq);
  void what_to_do_here(void);

protected:
  mavlink_mission_item_t mi;        // mission item currently executed
  mavlink_mission_item_t mi_prev;   // previouse mission item to construct navigation line
  const StateVector *in;
  Impact *out;
  NavigationSphere<float> sphere;
  float launch_lon; // cached value
  float launch_lat; // cached value
  float launch_alt; // cached value
  systime_t loiter_timestamp;
  uint32_t loiter_halfturns;
  float const *speed, *pulse2m, *dbg_lat, *dbg_lon;
  acs_state_t state;
};

#endif /* ACS_H_ */


