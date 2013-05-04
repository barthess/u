#ifndef ACS_H_
#define ACS_H_

#include <stdint.h>
#include "mavlink.h"
#include "pid.hpp"
#include "sensors.hpp"

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

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
  ACS_STATE_NAVIGATE_TO_WAYPOINT,
  ACS_STATE_PASS_WAYPOINT,
  ACS_STATE_LOITER,
}acs_state_t;

/**
 *
 */
class ACS{
public:
  ACS(void){state = ACS_STATE_UNINIT;};
  void start(void);
  acs_status_t launch(uint16_t seq);
  acs_status_t update(const StateVector *in, Impact *out);
  acs_status_t overwriteWp(uint16_t seq);
  acs_status_t go_home(void);
  acs_status_t loiter(systime_t t);

private:
  acs_status_t navigating(const StateVector *in, Impact *out);
  acs_status_t passing_wp(const StateVector *in, Impact *out);
  acs_status_t loitering(const StateVector *in, Impact *out);
  mavlink_mission_item_t wp;
  uint16_t seq;
  acs_state_t state;
  PIDControl<float> spd;
  PIDControl<float> hdg;
  PIDControl<float> xtrack;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* ACS_H_ */
