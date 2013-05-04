#ifndef ACS_H_
#define ACS_H_

#include <stdint.h>
#include "mavlink.h"
#include "pid.hpp"

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
 * @brief   Input data for ACS
 */
typedef struct {
  float     gamma;    // roll (rad)
  float     theta;    // pitch (rad)
  float     psi;      // heading (rad)
  float     lat;      // lattitude from GNSS (WGS-84, rad)
  float     lon;      // longitude from GNSS (WGS-84, rad)
  float     hmsl;     // altitude from GNSS (WGS-84, m)
  float     xn;       // X coordinate, North (m)
  float     hup;      // H coordinate, Up (m)
  float     ye;       // Y coordinate, East (m)
  float     v;        // speed (m/s)
}acs_input_t;

/**
 * @brief   Output data from ACS
 */
typedef struct {
  float     angle0;   // (rad)
  float     angle1;   // (rad)
  float     angle2;   // (rad)
  uint8_t   thrust;   // (percents)
}acs_output_t;

/**
 *
 */
class ACS{
public:
  ACS(void){state = ACS_STATE_UNINIT;};
  void start(void);
  acs_status_t launch(uint16_t seq);
  acs_status_t update(const acs_input_t *in, acs_output_t *out);
  acs_status_t overwriteWp(uint16_t seq);
  acs_status_t go_home(void);

private:
  acs_status_t navigate(const acs_input_t *in, acs_output_t *out);
  acs_status_t pass(const acs_input_t *in, acs_output_t *out);
  acs_status_t loiter(const acs_input_t *in, acs_output_t *out);
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
