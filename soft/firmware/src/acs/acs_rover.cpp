#include <math.h>

#include "main.h"
#include "acs_rover.hpp"
#include "param_registry.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern ParamRegistry param_registry;
extern CompensatedData comp_data;
extern mavlink_nav_controller_output_t  mavlink_out_nav_controller_output_struct;
extern mavlink_local_position_ned_t     mavlink_out_local_position_ned_struct;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
/**
 *
 */
void ACSRover::pull_handbreak(void){
  /* thrust update */
  float impact;
  impact = spdPID.update(0 - comp_data.groundspeed_odo, comp_data.groundspeed_odo);
  mavlink_out_nav_controller_output_struct.aspd_error = 0 - comp_data.groundspeed_odo;

  if (impact < 0)  /* this check need because we can not get direction of moving */
    impact = 0;
  out->thrust = impact;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
ACSRover::ACSRover(const StateVector *in, Impact *out):
    ACS(in, out)
{
  return;
}


/**
 *
 */
void ACSRover::start(void){
  this->speed =   (const float*)param_registry.valueSearch("SPD_speed");
  this->pulse2m = (const float*)param_registry.valueSearch("SPD_pulse2m");

  this->hdgPID.start((const float*)param_registry.valueSearch("HDG_iMin"),
                  (const float*)param_registry.valueSearch("HDG_iMax"),
                  (const float*)param_registry.valueSearch("HDG_pGain"),
                  (const float*)param_registry.valueSearch("HDG_iGain"),
                  (const float*)param_registry.valueSearch("HDG_dGain"));
  this->spdPID.start((const float*)param_registry.valueSearch("SPD_iMin"),
                  (const float*)param_registry.valueSearch("SPD_iMax"),
                  (const float*)param_registry.valueSearch("SPD_pGain"),
                  (const float*)param_registry.valueSearch("SPD_iGain"),
                  (const float*)param_registry.valueSearch("SPD_dGain"));
  this->xtdPID.start((const float*)param_registry.valueSearch("XTRACK_iMin"),
                  (const float*)param_registry.valueSearch("XTRACK_iMax"),
                  (const float*)param_registry.valueSearch("XTRACK_pGain"),
                  (const float*)param_registry.valueSearch("XTRACK_iGain"),
                  (const float*)param_registry.valueSearch("XTRACK_dGain"));

  dbg_lat = (const float*)param_registry.valueSearch("DBG_lat");
  dbg_lon = (const float*)param_registry.valueSearch("DBG_lon");

  this->loiter_timestamp = chTimeNow();
  this->loiter_halfturns = 0;
  this->state = ACS_STATE_IDLE;
}

/**
 * @brief   Kill uas. Pull break for rover. Eject parachute for airplane.
 */
MAV_RESULT ACSRover::kill(void){
  state = ACS_STATE_IDLE;
  pull_handbreak();
  return MAV_RESULT_ACCEPTED;
}
