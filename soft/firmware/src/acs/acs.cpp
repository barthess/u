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
#include "mavdbg.hpp"
#include "sins.hpp"
#include "navigation.hpp"

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

extern mavlink_system_t                 mavlink_system_struct;
extern mavlink_mission_current_t        mavlink_out_mission_current_struct;
extern mavlink_mission_item_reached_t   mavlink_out_mission_item_reached_struct;
extern mavlink_nav_controller_output_t  mavlink_out_nav_controller_output_struct;
extern mavlink_local_position_ned_t     mavlink_out_local_position_ned_struct;

extern EventSource event_mavlink_out_mission_current;
extern EventSource event_mavlink_out_mission_item_reached;
extern CompensatedData comp_data;

extern WpDB wpdb;
extern SINS sins;

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
  chEvtBroadcastFlags(&event_mavlink_out_mission_current,
                                          EVMSK_MAVLINK_OUT_MISSION_CURRENT);
  log_write_schedule(MAVLINK_MSG_ID_MISSION_CURRENT, NULL, 0);
}

/**
 *
 */
static void broadcast_mission_item_reached(uint16_t seq){
  mavlink_out_mission_item_reached_struct.seq = seq;
  chEvtBroadcastFlags(&event_mavlink_out_mission_item_reached,
                                      EVMSK_MAVLINK_OUT_MISSION_ITEM_REACHED);
  log_write_schedule(MAVLINK_MSG_ID_MISSION_ITEM_REACHED, NULL, 0);
}

/**
 *
 */
void ACS::pull_handbreak(void){
  /* thrust update */
  float impact;
  impact = spdPID.update(0 - comp_data.groundspeed_odo, comp_data.groundspeed_odo);
  mavlink_out_nav_controller_output_struct.aspd_error = 0 - comp_data.groundspeed_odo;

  if (impact < 0)  /* this check need because we can not get direction of moving */
    impact = 0;
  out->thrust = impact;
}

/**
 *
 */
void ACS::what_to_do_here(void){
  if ((mi.command == MAV_CMD_NAV_LOITER_UNLIM) ||
      (mi.command == MAV_CMD_NAV_LOITER_TURNS) ||
      (mi.command == MAV_CMD_NAV_LOITER_TIME)){
    /* we must loter here according to mission plan */
    mavlink_dbg_print(MAV_SEVERITY_INFO, "ACS: start loitering");
    loiter_halfturns = 0;
    loiter_timestamp = chTimeNow();
    state = ACS_STATE_LOITER;
  }
  else if(mi.command == MAV_CMD_NAV_WAYPOINT){
    /* this is regular waypoint. Just go to next item */
    state = ACS_STATE_LOAD_MISSION_ITEM;
  }
  else if(mi.command == MAV_CMD_NAV_TAKEOFF){
    /* rover successfully navigated to takeoff point. Go to next item */
    state = ACS_STATE_LOAD_MISSION_ITEM;
  }
  else if(mi.command == MAV_CMD_NAV_LAND){
    /* landing point reached. Go to idle state */
    state = ACS_STATE_IDLE;
    mavlink_system_struct.mode &= ~MAV_MODE_FLAG_SAFETY_ARMED;
    mavlink_system_struct.state = MAV_STATE_STANDBY;
    mavlink_dbg_print(MAV_SEVERITY_INFO, "ACS: Landed");
  }
  else{
    /* do not know hot to handle it. Just got to next */
    state = ACS_STATE_LOAD_MISSION_ITEM;
  }
}

/**
 *
 */
acs_status_t ACS::loop_navigate(void){
  float target_heading = 0;
  float target_distance = 10000;
  float xtd_corr = 0;
  float impact = 0;
  float error = 0;
  float xtd = 0, atd = 0;
  float dx = 0, dy = 0;

  switch(mi.frame){
  /************
   * Local NED
   ***********/
  case MAV_FRAME_LOCAL_NED:
    /* heading update. NOTE: atan2(0,0) is forbidden arguments */
    target_heading = atan2f(mi.y - in->Ysins, mi.x - in->Xsins);
    error = wrap_pi(target_heading - in->psi);
    impact = hdgPID.update(error, in->psi);
    putinrange(impact, -0.2f, 0.2f);
    out->rud = impact;

    /* thrust update */
    impact = spdPID.update(*speed - comp_data.groundspeed_odo, comp_data.groundspeed_odo);
    if (impact < 0)  /* this check need because we can not get direction of moving */
      impact = 0;
    out->thrust = impact;

    /* fill telemetry messages */
    mavlink_out_nav_controller_output_struct.xtrack_error = 0;
    mavlink_out_nav_controller_output_struct.wp_dist = target_distance;
    mavlink_out_nav_controller_output_struct.aspd_error = *speed - comp_data.groundspeed_odo;

    /* check reachability */
    dx = in->Xsins - mi.x;
    dy = in->Ysins - mi.y;
    target_distance = sqrtf(dx*dx + dy*dy);
    if (target_distance < mi.param2){
      broadcast_mission_item_reached(mi.seq);
      what_to_do_here();
    }
    break;

  /***************
   * Global WGS-84
   ***************/
  case MAV_FRAME_GLOBAL:
    /* heading update */
    sphere.crosstrack(in->lat, in->lon, &xtd, &atd);
    sphere.course(in->lat, in->lon, &target_heading, &target_distance);
    xtd_corr = xtdPID.update(xtd, in->psi);
    error = wrap_pi(target_heading - in->psi - xtd_corr);
    impact = hdgPID.update(error, in->psi);
    putinrange(impact, -0.2f, 0.2f);
    out->rud = impact;

    /* thrust update */
    impact = spdPID.update(*speed - comp_data.groundspeed_odo, comp_data.groundspeed_odo);
    if (impact < 0)  /* this check need because we can not get direction of moving */
      impact = 0;
    out->thrust = impact;

    /* fill telemetry data */
    mavlink_out_nav_controller_output_struct.xtrack_error = xtd;
    mavlink_out_nav_controller_output_struct.wp_dist = rad2m(target_distance);
    mavlink_out_nav_controller_output_struct.aspd_error = *speed - comp_data.groundspeed_odo;

    /* check reachablillity */
    if (rad2m(target_distance) < mi.param2){
      broadcast_mission_item_reached(mi.seq);
      what_to_do_here();
    }
    break;

  /*
   *
   */
  default:
    return ACS_STATUS_ERROR;
  }

  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_pause(void){
  /* for ground rover we must just to pull handbrake and wait next command */
  pull_handbreak();
  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_pass_wp(void){
  chDbgPanic("unrealized");
  switch(mi.frame){
  /***********
   * Local NED
   ***********/
  case MAV_FRAME_LOCAL_NED:
    break;

  /****************
   * Global WGS-84
   ***************/
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

/**
 *
 */
acs_status_t ACS::loop_land(void){
  /* there is nothing special landing procedures for rover. Just navigate
   * to landing waypoint */
  state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_takeoff(void){
  /* there is nothing special take off procedures for rover. Just navigate
   * to lauch waypoint */
  state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_load_mission_item(void){
  bool load_status = CH_FAILED;

  mi_prev = mi;
  if (wpdb.getCount() <= (mi.seq + 1)){ // no more items
    /* if we fall here than last mission was not 'land'. System do not know
     * what to do so start unlimited loitering */
    state = ACS_STATE_LOITER;
    return ACS_STATUS_NO_MISSION;
  }
  else{
    load_status = wpdb.load(&mi, mi_prev.seq + 1);
    if (CH_SUCCESS != load_status){
      /* something goes wrong with waypoint loading */
      state = ACS_STATE_LOITER;
      return ACS_STATUS_ERROR;
    }
    else{
      broadcast_mission_current(mi.seq);
      sphere.updatePoints(deg2rad(mi_prev.x), deg2rad(mi_prev.y),
                          deg2rad(mi.x),      deg2rad(mi.y));
      state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
      return ACS_STATUS_OK;
    }
  }
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

  this->speed =   (const float*)param_registry.valueSearch("SPD_speed");
  this->pulse2m = (const float*)param_registry.valueSearch("SPD_pulse2m");
  this->hdgPID.start((const float*)param_registry.valueSearch("HDG_iMax"),
                  (const float*)param_registry.valueSearch("HDG_iMin"),
                  (const float*)param_registry.valueSearch("HDG_iGain"),
                  (const float*)param_registry.valueSearch("HDG_pGain"),
                  (const float*)param_registry.valueSearch("HDG_dGain"));
  this->spdPID.start((const float*)param_registry.valueSearch("SPD_iMax"),
                  (const float*)param_registry.valueSearch("SPD_iMin"),
                  (const float*)param_registry.valueSearch("SPD_iGain"),
                  (const float*)param_registry.valueSearch("SPD_pGain"),
                  (const float*)param_registry.valueSearch("SPD_dGain"));
  this->xtdPID.start((const float*)param_registry.valueSearch("XTRACK_iMax"),
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

  spdPID.reset();
  hdgPID.reset();
  xtdPID.reset();

  this->loiter_timestamp = chTimeNow();
  this->loiter_halfturns = 0;
  this->state = ACS_STATE_IDLE;
}

/**
 *
 */
acs_status_t ACS::update(void){
  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");
  chDbgCheck((NULL != in) && (NULL != out), "");

  switch(this->state){
  case ACS_STATE_NAVIGATE_TO_WAYPOINT:
    return loop_navigate();
    break;

  case ACS_STATE_LOITER:
    return loop_loiter();
    break;

  case ACS_STATE_PASS_WAYPOINT:
    return loop_pass_wp();
    break;

  case ACS_STATE_TAKEOFF:
    return loop_takeoff();
    break;

  case ACS_STATE_LOAD_MISSION_ITEM:
    return loop_load_mission_item();
    break;

  case ACS_STATE_LAND:
    return loop_land();
    break;

  case ACS_STATE_PAUSE:
    return loop_pause();
    break;

  case ACS_STATE_IDLE:
    pull_handbreak();
    return ACS_STATUS_OK;
    break;

  default:
    chDbgPanic("unhandled case");
    return ACS_STATUS_ERROR;
    break;
  }

  /* warning supressor */
  return ACS_STATUS_ERROR;
}

/**
 * @brief   Launch UAV
 */
MAV_RESULT ACS::takeoff(void){
  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");

  /* check system state */
  if (MAV_STATE_STANDBY != mavlink_system_struct.state){
    mavlink_dbg_print(MAV_SEVERITY_ERROR, "ERROR: system must be in STANDBY");
    return MAV_RESULT_TEMPORARILY_REJECTED;
  }

  /* system disarmed */
  if (!(mavlink_system_struct.mode & MAV_MODE_FLAG_SAFETY_ARMED)){
    mavlink_dbg_print(MAV_SEVERITY_ERROR, "ERROR: motors disarmed");
    return MAV_RESULT_TEMPORARILY_REJECTED;
  }

  /* allready done */
  if (ACS_STATE_IDLE != state){
    mavlink_dbg_print(MAV_SEVERITY_ERROR, "ERROR: mission in process");
    return MAV_RESULT_TEMPORARILY_REJECTED;
  }

  /* try to load start of mission to RAM */
  if (0 == wpdb.getCount()){
    mavlink_dbg_print(MAV_SEVERITY_ERROR, "ERROR: mission empty");
    return MAV_RESULT_TEMPORARILY_REJECTED;
  }
  if (CH_SUCCESS != wpdb.load(&mi, 0))
    chDbgPanic("can not acquare waypoint");
  if (mi.command != MAV_CMD_NAV_TAKEOFF)
    chDbgPanic("first item must be takeoff");

  switch(mi.frame){
  /*
   * local frame handler
   */
  case MAV_FRAME_LOCAL_NED:
    mi_prev = mi; // hack to fill all other fields correctly
    mi_prev.x = 0;
    mi_prev.y = 0;
    mi_prev.z = 0;
    launch_lat = 0;
    launch_lon = 0;
    launch_alt = 0;
    break;

  /*
   * global fram handler
   */
  case MAV_FRAME_GLOBAL:
    if (in->gpsfix < 2){    /* can not fly without GPS */
      mavlink_dbg_print(MAV_SEVERITY_ERROR, "ERROR: no GPS fix");
      return MAV_RESULT_TEMPORARILY_REJECTED;
    }
    else{
      launch_lon = in->lon;
      launch_lat = in->lat;
      launch_alt = in->hmsl;
      mi_prev = mi; // hack to fill all other fields correctly
      mi_prev.x = launch_lat;
      mi_prev.y = launch_lon;
      mi_prev.z = launch_alt;
    }
    break;

  /*
   * error trap
   */
  default:
    chDbgPanic("unhandled case");
    break;
  }

  sins.reset();
  mavlink_dbg_print(MAV_SEVERITY_INFO, "ACS: Taking off");
  state = ACS_STATE_TAKEOFF;
  mavlink_system_struct.state = MAV_STATE_ACTIVE;
  broadcast_mission_current(mi.seq);
  return MAV_RESULT_ACCEPTED;
}

/**
 *
 */
MAV_RESULT ACS::emergencyLand(mavlink_command_long_t *clp){
  (void)clp;
  chDbgPanic("unrealized");
  return MAV_RESULT_ACCEPTED;
}

/**
 * @brief   Used for emergency pause the mission.
 */
MAV_RESULT ACS::overrideGoto(mavlink_command_long_t *clp){
  /* Hold / continue the current action
   * | MAV_GOTO_DO_HOLD: hold
   *   MAV_GOTO_DO_CONTINUE: continue with next item in mission plan
   *
   * | MAV_GOTO_HOLD_AT_CURRENT_POSITION: Hold at current position
   *   MAV_GOTO_HOLD_AT_SPECIFIED_POSITION: hold at specified position
   *
   * | MAV_FRAME coordinate frame of hold point
   * | Desired yaw angle in degrees
   * | Latitude / X position
   * | Longitude / Y position
   * | Altitude / Z position|  */

  /* pause at current position */
  if (clp->param1 == MAV_GOTO_DO_HOLD &&
      clp->param2 == MAV_GOTO_HOLD_AT_CURRENT_POSITION &&
      clp->param3 == 0 &&
      clp->param4 == 0 &&
      clp->param5 == 0 &&
      clp->param6 == 0 &&
      clp->param7 == 0){

    if (ACS_STATE_NAVIGATE_TO_WAYPOINT != state){
      mavlink_dbg_print(MAV_SEVERITY_ERROR, "ERROR: pause allowed only during navigation");
      return MAV_RESULT_TEMPORARILY_REJECTED;
    }
    else{
      state = ACS_STATE_PAUSE;
      mavlink_dbg_print(MAV_SEVERITY_INFO, "INFO: mission paused");
      return MAV_RESULT_ACCEPTED;
    }
  }

  /* unpause */
  else if (clp->param1 == MAV_GOTO_DO_CONTINUE &&
           clp->param2 == MAV_GOTO_HOLD_AT_CURRENT_POSITION &&
           clp->param3 == 0 &&
           clp->param4 == 0 &&
           clp->param5 == 0 &&
           clp->param6 == 0 &&
           clp->param7 == 0){

    if (ACS_STATE_PAUSE != state){
      mavlink_dbg_print(MAV_SEVERITY_ERROR, "ERROR: continue allowed only during pause");
      return MAV_RESULT_TEMPORARILY_REJECTED;
    }
    else{
      state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
      mavlink_dbg_print(MAV_SEVERITY_INFO, "INFO: mission continued");
      return MAV_RESULT_ACCEPTED;
    }
  }

  /* unrealized */
  else{
    return MAV_RESULT_UNSUPPORTED;
  }
}

/**
 *
 */
MAV_RESULT ACS::returnToLaunch(mavlink_command_long_t *clp){
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
  /* safety armed bit can be changed only in STANDBY mode*/
  if ((mavlink_system_struct.mode & MAV_MODE_FLAG_SAFETY_ARMED) !=
                   (sm->base_mode & MAV_MODE_FLAG_SAFETY_ARMED)){
    if (! (MAV_STATE_STANDBY == mavlink_system_struct.state &&
           ACS_STATE_IDLE == state)){
      mavlink_dbg_print(MAV_SEVERITY_ERROR, "ERROR: system must be in STANDBY");
      return;
    }
  }

  /* mode can be changed */
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

///**
// *
// */
//MAV_RESULT ACS::next(void){
//  chDbgCheck(ACS_STATE_UNINIT != this->state, "invalid state");
//
//  /* you have to take device off first */
//  if (ACS_STATE_WAIT_MISSION_ITEM == state){
//    /* cache this waipoint */
//    chSysLock();
//    mi = *mip;
//    state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
//    chSysUnlock();
//
//    return MAV_RESULT_ACCEPTED;
//  }
//  else
//    return MAV_RESULT_TEMPORARILY_REJECTED;
//}
