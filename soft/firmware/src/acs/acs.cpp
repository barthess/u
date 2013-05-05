#include "main.h"
#include "acs.hpp"
#include "param_registry.hpp"
#include "waypoint_db.hpp"
#include "servo.hpp"
#include "mavcmd.hpp"

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
extern mavlink_system_t   mavlink_system_struct;
extern WpDB wpdb;

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
 * Construct command long message from mission item to be executed
 */
static void wp2cl(const mavlink_mission_item_t *wp,
                  mavlink_command_long_t *cl){
  cl->command = wp->command;
  cl->param1  = wp->param1;
  cl->param2  = wp->param2;
  cl->param3  = wp->param3;
  cl->param4  = wp->param4;
  cl->param5  = wp->x;
  cl->param6  = wp->y;
  cl->param7  = wp->z;
  cl->confirmation = 0;
  cl->target_component = wp->target_component;
  cl->target_system = wp->target_system;
}

/**
 *
 */
acs_status_t ACS::navigating(void){
  return ACS_STATUS_ERROR;
}

/**
 *
 */
acs_status_t ACS::passing_wp(void){
  return ACS_STATUS_ERROR;
}

/**
 *
 */
acs_status_t ACS::loitering(void){
  return ACS_STATUS_ERROR;
}

/**
 *
 */
acs_status_t ACS::taking_off(void){

  /* wait untill GPS fix */
  if (in->gpsfix < 2)
    return ACS_STATUS_OK;
  else{
    /* get 0-th waypoint */
    wpdb.load(&wp, 0);

    /* construct command from it */
    wp2cl(&wp, &cl);

    /* execute it */
    ExecuteCommandLong(&cl);

    state = ACS_STATE_NAVIGATE_TO_WAYPOINT;
    return ACS_STATUS_OK;
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

  this->speed_min = (const float*)param_registry.valueSearch("SPD_speed_min");
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

  ServoInit();
  this->state = ACS_STATE_IDLE;
}

/**
 *
 */
MAV_RESULT ACS::loiter(mavlink_command_long_t *clp){
  (void)clp;
  return MAV_RESULT_ACCEPTED;
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
MAV_RESULT ACS::takeoff(mavlink_command_long_t *clp){
  // TODO: handle different takeoff cmd parameters

  /* Takeoff from ground / hand
   * | Minimum pitch (if airspeed sensor present), desired pitch without sensor
   * | Empty
   * | Empty
   * | Yaw angle (if magnetometer present), ignored without magnetometer
   * | Latitude
   * | Longitude
   * | Altitude|  */
  (void)clp;

  if (ACS_STATE_IDLE != state)    /* allready done */
    return MAV_RESULT_TEMPORARILY_REJECTED;
  else{
    launch_lon = in->lon;
    launch_lat = in->lat;
    state = ACS_STATE_TAKEOFF;
    return MAV_RESULT_ACCEPTED;
  }
}

/**
 *
 */
void ACS::setCurrentMission(mavlink_mission_set_current_t *sc){
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
