#include "main.h"
#include "acs.hpp"
#include "mavdbg.hpp"

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
extern CompensatedData comp_data;

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
acs_status_t ACS::loop_loiter_turns(void){
  float impact = 0;

  /* set rudder */
  if (mi.param3 > 0)
    out->rud = 0.2f;
  else
    out->rud = -0.2f;

  /* thrust update */
  impact = spdPID.update(*speed - comp_data.groundspeed_odo, comp_data.groundspeed_odo);
  if (impact < 0)  /* this check need because we can not get direction of moving */
    impact = 0;
  out->thrust = impact;

  /* count halfturns instead of turns to use halfcyrcle as hysteresis */
  if (loiter_halfturns & 1){
    if((in->psi > 0) && (in->psi < PI))
      loiter_halfturns++;
  }
  else{
    if((in->psi > PI) && (in->psi < (2*PI)))
      loiter_halfturns++;
  }

  /* is loitering done */
  if ((loiter_halfturns / 2) >= mi.param2){
    state = ACS_STATE_LOAD_MISSION_ITEM;
  }

  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_loiter_time(void){
  float impact = 0;

  /* set rudder */
  if (mi.param3 > 0)
    out->rud = 0.2f;
  else
    out->rud = -0.2f;

  /* thrust update */
  impact = spdPID.update(*speed - comp_data.groundspeed_odo, comp_data.groundspeed_odo);
  if (impact < 0)  /* this check need because we can not get direction of moving */
    impact = 0;
  out->thrust = impact;

  /* is loitering done */
  if ((chTimeNow() - loiter_timestamp) < S2ST((systime_t)mi.param1)){
    state = ACS_STATE_LOAD_MISSION_ITEM;
  }
  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_loiter_unlim(void){
  state = ACS_STATE_LOAD_MISSION_ITEM;
  mavlink_dbg_print(MAV_SEVERITY_WARNING, "WARNING: Unlimited loiter unrealized");
  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_loiter(void){
  switch(mi.command){
  case MAV_CMD_NAV_LOITER_TURNS:
    return loop_loiter_turns();
    break;

  case MAV_CMD_NAV_LOITER_TIME:
    return loop_loiter_time();
    break;

  case MAV_CMD_NAV_LOITER_UNLIM:
    return loop_loiter_unlim();
    break;

  default:
    return ACS_STATUS_ERROR;
    break;
  }
}


