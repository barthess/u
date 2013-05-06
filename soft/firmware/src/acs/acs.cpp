#include <math.h>

#include "main.h"
#include "acs.hpp"
#include "param_registry.hpp"
#include "waypoint_db.hpp"
#include "servo.hpp"
#include "mission_planner.hpp"
#include "misc_math.hpp"
#include "geometry.hpp"
#include "logger.hpp"

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
extern ParamRegistry      param_registry;
extern mavlink_system_t   mavlink_system_struct;

extern mavlink_mission_current_t        mavlink_out_mission_current_struct;
extern mavlink_mission_item_reached_t   mavlink_out_mission_item_reached_struct;
extern mavlink_nav_controller_output_t  mavlink_out_nav_controller_output_struct;
extern mavlink_vfr_hud_t                mavlink_out_vfr_hud_struct;
extern mavlink_local_position_ned_t     mavlink_out_local_position_ned_struct;

extern EventSource event_mavlink_out_mission_current;
extern EventSource event_mavlink_out_mission_item_reached;
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
static void broadcast_mission_current(uint16_t seq){
  mavlink_out_mission_current_struct.seq = seq;
  chEvtBroadcastFlags(&event_mavlink_out_mission_current, EVMSK_MAVLINK_OUT_MISSION_CURRENT);
  log_write_schedule(MAVLINK_MSG_ID_MISSION_CURRENT, NULL, 0);
}

/**
 *
 */
static void broadcast_mission_item_reached(uint16_t seq){
  mavlink_out_mission_item_reached_struct.seq = seq;
  chEvtBroadcastFlags(&event_mavlink_out_mission_item_reached, EVMSK_MAVLINK_OUT_MISSION_ITEM_REACHED);
  log_write_schedule(MAVLINK_MSG_ID_MISSION_ITEM_REACHED, NULL, 0);
}

/**
 *
 */
bool ACS::is_wp_reached_local(void){
  float sqr_target_radius = mi.param1 * mi.param1;
  float dx = in->Xsins - mi.x;
  float dy = in->Ysins - mi.y;

  if ((dx*dx + dy*dy) < sqr_target_radius)
    return true;
  else
    return false;
}

/**
 *
 */
acs_status_t ACS::navigating(void){
  float target_heading = 0;
  float impact;
  float error;

  switch(mi.frame){
  /*
   * Local NED
   */
  case MAV_FRAME_LOCAL_NED:
    /* check reachablillity */
    if (is_wp_reached_local()){
      state = ACS_STATE_PASS_WAYPOINT;
    }
    else{
      /* heading update */
      //NOTE: atan2(0,0) is forbidden arguments
      target_heading = atan2f(mi.y, mi.x);
      error = wrap_pi(target_heading - in->psi);
      impact = hdg.update(error, in->psi);
      putinrange(impact, -0.2f, 0.2f);
      out->rud = impact;

      /* thrust update */
      impact = spd.update(*speed_min - comp_data.groundspeed_odo, comp_data.groundspeed_odo);
      mavlink_out_vfr_hud_struct.groundspeed = comp_data.groundspeed_odo;
      mavlink_out_nav_controller_output_struct.aspd_error = *speed_min - comp_data.groundspeed_odo;
      if (impact < 0)  /* this check need because we can not get direction of moving */
        impact = 0;
      out->thrust = impact;
    }
    break;

  /*
   * Global WGS-84
   */
  case MAV_FRAME_GLOBAL:
    break;
  default:
    return ACS_STATUS_ERROR;
  }

  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::passing_wp(void){

  switch(mi.frame){
  /*
   * Local NED
   */
  case MAV_FRAME_LOCAL_NED:
    mavlink_out_mission_item_reached_struct.seq = mi_prev.seq;
    chEvtBroadcastFlags(&event_mavlink_out_mission_item_reached,
                          EVMSK_MAVLINK_OUT_MISSION_ITEM_REACHED);
    break;

  /*
   * Global WGS-84
   */
  case MAV_FRAME_GLOBAL:
    break;
  default:
    return ACS_STATUS_ERROR;
  }
  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loitering(void){
  chDbgPanic("unrealized");
  return ACS_STATUS_ERROR;
}

/**
 *
 */
acs_status_t ACS::taking_off(void){

  chSysLock();
  mi_prev = mi;
  chSysUnlock();

  mavlink_out_mission_item_reached_struct.seq = mi_prev.seq;
  chEvtBroadcastFlags(&event_mavlink_out_mission_item_reached, EVMSK_MAVLINK_OUT_MISSION_ITEM_REACHED);
  return ACS_STATUS_OK;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void ACS::start(const StateVector *in, Impact *out){
  this->in = in;
  this->out = out;

  this->speed_min = (const float*)param_registry.valueSearch("SPD_speed_min");
  this->pulse2m = (const float*)param_registry.valueSearch("SPD_pulse2m");
  this->hdg.start((const float*)param_registry.valueSearch("HDG_iMax"),
                  (const float*)param_registry.valueSearch("HDG_iMin"),
                  (const float*)param_registry.valueSearch("HDG_iGain"),
                  (const float*)param_registry.valueSearch("HDG_pGain"),
                  (const float*)param_registry.valueSearch("HDG_dGain"));
  this->spd.start((const float*)param_registry.valueSearch("SPD_iMax"),
                  (const float*)param_registry.valueSearch("SPD_iMin"),
                  (const float*)param_registry.valueSearch("SPD_iGain"),
                  (const float*)param_registry.valueSearch("SPD_pGain"),
                  (const float*)param_registry.valueSearch("SPD_dGain"));
  this->xtrack.start((const float*)param_registry.valueSearch("XTRACK_iMax"),
                  (const float*)param_registry.valueSearch("XTRACK_iMin"),
                  (const float*)param_registry.valueSearch("XTRACK_iGain"),
                  (const float*)param_registry.valueSearch("XTRACK_pGain"),
                  (const float*)param_registry.valueSearch("XTRACK_dGain"));

  mavlink_out_nav_controller_output_struct.nav_roll       = 0;
  mavlink_out_nav_controller_output_struct.nav_pitch      = 0;
  mavlink_out_nav_controller_output_struct.alt_error      = 0;
  mavlink_out_nav_controller_output_struct.aspd_error     = 0;
  mavlink_out_nav_controller_output_struct.wp_dist        = 0;
  mavlink_out_nav_controller_output_struct.nav_bearing    = 0;
  mavlink_out_nav_controller_output_struct.target_bearing = 0;
  mavlink_out_nav_controller_output_struct.xtrack_error   = 0;

  mavlink_out_local_position_ned_struct.x  = 0;
  mavlink_out_local_position_ned_struct.y  = 0;
  mavlink_out_local_position_ned_struct.z  = 0;
  mavlink_out_local_position_ned_struct.vx = 0;
  mavlink_out_local_position_ned_struct.vy = 0;
  mavlink_out_local_position_ned_struct.vz = 0;
  mavlink_out_local_position_ned_struct.time_boot_ms = TIME_BOOT_MS;

  spd.reset();
  hdg.reset();
  xtrack.reset();

  this->state = ACS_STATE_IDLE;
}

/**
 *
 */
acs_status_t ACS::update(void){
  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");
  chDbgCheck((NULL != in) && (NULL != out), "");

  switch(this->state){
  case ACS_STATE_IDLE:
    return ACS_STATUS_OK;
    break;

  case ACS_STATE_NAVIGATE_TO_WAYPOINT:
    return navigating();
    break;

  case ACS_STATE_PASS_WAYPOINT:
    return passing_wp();
    break;

  case ACS_STATE_LOITER:
    return loitering();
    break;

  default:
    chDbgPanic("unhandled case");
    return ACS_STATUS_ERROR;
    break;
  }
}

/**
 * @brief   Launch UAV
 */
MAV_RESULT ACS::takeoff(mavlink_mission_item_t *mip){
  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");

  if (ACS_STATE_IDLE != state)    /* allready done */
    return MAV_RESULT_TEMPORARILY_REJECTED;

  switch(mip->frame){

  /* local fram handler */
  case MAV_FRAME_LOCAL_NED:
    mi_prev = *mip;
    mi_prev.x = 0;
    mi_prev.y = 0;
    mi_prev.z = 0;
    launch_lon = 0;
    launch_lat = 0;
    break;

  /* global fram handler */
  case MAV_FRAME_GLOBAL:
    if (in->gpsfix < 2)    /* can not fly without GPS */
      return MAV_RESULT_TEMPORARILY_REJECTED;
    else{
      launch_lon = in->lon;
      launch_lat = in->lat;
    }
    break;

  /* error trap */
  default:
    chDbgPanic("unsupported frame");
    break;
  }

  if (MAV_CMD_NAV_WAYPOINT == mip->command)
    state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
  else if(MAV_CMD_NAV_TAKEOFF == mip->command)
    state = ACS_STATE_TAKEOFF;
  else
    return MAV_RESULT_UNSUPPORTED;

  mavlink_out_mission_current_struct.seq = mip->seq;
  chEvtBroadcastFlags(&event_mavlink_out_mission_current, EVMSK_MAVLINK_OUT_MISSION_CURRENT);

  /* store this waipoint as cached */
  chSysLock();
  mi = *mip;
  chSysUnlock();

  return MAV_RESULT_ACCEPTED;
}

/**
 *
 */
MAV_RESULT ACS::next(mavlink_mission_item_t *mip){
  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");

  /* you have to take device off first */
  if (ACS_STATE_IDLE == state)
    return MAV_RESULT_TEMPORARILY_REJECTED;

  if ((ACS_STATE_NAVIGATE_TO_WAYPOINT == state) ||
      (ACS_STATE_TAKEOFF == state) ||
      (ACS_STATE_PASS_WAYPOINT == state)){
    /* cache this waipoint */
    chSysLock();
    mi = *mip;
    chSysUnlock();

    state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
    return MAV_RESULT_ACCEPTED;
  }
  else
    return MAV_RESULT_TEMPORARILY_REJECTED;
}

/**
 *
 */
MAV_RESULT ACS::loiter(mavlink_command_long_t *clp){
  (void)clp;
  chDbgPanic("unrealized");
  return MAV_RESULT_ACCEPTED;
}

/**
 *
 */
void ACS::setCurrentMission(mavlink_mission_set_current_t *sc){
  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");

  (void)sc;
  chDbgPanic("unrealized");
  return;
}

/**
 * Set autopilot mode logic.
 */
void ACS::setMode(mavlink_set_mode_t *sm){
  mavlink_system_struct.mode = sm->custom_mode | sm->base_mode;
}

/**
 *
 */
void ACS::manualControl(mavlink_manual_control_t *mc){
  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");

  uint32_t v = 0;
  (void)v;
  (void)mc;
  chDbgPanic("unrealized");
//  if (mc->thrust_manual == 1){
//    v = float2thrust(mc->thrust);
//    ServoCarThrustSet(v);
//  }
//  if (mc->yaw_manual == 1){
//    v = float2servo(mc->yaw);
//    Servo7Set(v);
//  }
}
