#include <math.h>

#include "main.h"
#include "acs.hpp"
#include "gps.hpp"

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
extern mavlink_nav_controller_output_t  mavlink_out_nav_controller_output_struct;
extern mavlink_global_position_int_t  mavlink_out_global_position_int_struct;
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
acs_status_t ACS::loop_navigate_local(void){
  float target_heading = 0;
  float target_distance = 10000;
  float impact = 0;
  float error = 0;
  float dx = 0, dy = 0;

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

  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_navigate_global(void){
  float target_heading = 0;
  float target_distance = 10000;
  float xtd_corr = 0;
  float impact = 0;
  float error = 0;
  float xtd = 0, atd = 0;
  float xtdm = 0;

  /* heading update */
  sphere.crosstrack(in->lat, in->lon, &xtd, &atd);
  sphere.course(in->lat, in->lon, &target_heading, &target_distance);
  //sphere.updatePoints(deg2rad((double)*this->dbg_lat), deg2rad((double)*this->dbg_lon), deg2rad((double)mi.x), deg2rad((double)mi.y));
  //sphere.course(deg2rad((double)*this->dbg_lat), deg2rad((double)*this->dbg_lon), &target_heading, &target_distance);
  //sphere.updatePoints(deg2rad(*this->dbg_lat), deg2rad(*this->dbg_lon), deg2rad(mi.x), deg2rad(mi.y));
//  sphere.course(deg2rad(*this->dbg_lat), deg2rad(*this->dbg_lon), &target_heading, &target_distance);
//  sphere.crosstrack(deg2rad(*this->dbg_lat), deg2rad(*this->dbg_lon), &xtd, &atd);

  xtdm = rad2m(xtd);
  if(isinf(xtdm) || isnan(xtdm))
    xtd_corr = xtdPID.update(0, 0);
  else
    xtd_corr = xtdPID.update(xtdm, 0);

//  mavlink_out_global_position_int_struct.lat = *this->dbg_lat * 10000000.0f;
//  mavlink_out_global_position_int_struct.lon = *this->dbg_lon * 10000000.0f;

  target_heading = wrap_2pi(-target_heading);
  error = wrap_pi(target_heading - in->psi + xtd_corr);
  impact = hdgPID.update(error, in->psi);
  putinrange(impact, (typeof(impact))-0.2, (typeof(impact))0.2);
  out->rud = impact;

  /* thrust update */
  impact = spdPID.update(*speed - comp_data.groundspeed_odo, comp_data.groundspeed_odo);
  if (impact < 0)  /* this check need because we can not get direction of moving */
    impact = 0;
  out->thrust = impact;

  /* fill telemetry data */
  mavlink_out_nav_controller_output_struct.nav_bearing = rad2deg(in->psi);
  mavlink_out_nav_controller_output_struct.target_bearing = rad2deg(target_heading);
  mavlink_out_nav_controller_output_struct.xtrack_error = xtdm;
  mavlink_out_nav_controller_output_struct.wp_dist = rad2m(target_distance);
  mavlink_out_nav_controller_output_struct.aspd_error = *speed - comp_data.groundspeed_odo;

  /* check reachablillity */
  if (rad2m(target_distance) < mi.param2){
    broadcast_mission_item_reached(mi.seq);
    what_to_do_here();
  }

  return ACS_STATUS_OK;
}

/**
 *
 */
acs_status_t ACS::loop_navigate(void){
  switch(mi.frame){
  case MAV_FRAME_LOCAL_NED:
    return loop_navigate_local();
    break;

  case MAV_FRAME_GLOBAL:
    return loop_navigate_global();
    break;

  default:
    return ACS_STATUS_ERROR;
  }
}


