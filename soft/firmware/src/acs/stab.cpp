#include <math.h>

#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "dsp.hpp"
#include "pid.hpp"
#include "stab.hpp"
#include "servo.hpp"
#include "controller.hpp"
#include "waypoint_db.hpp"
#include "wp.hpp"
#include "wp_local.hpp"
#include "wp_global.hpp"
#include "speedometer.hpp"
#include "param_registry.hpp"
#include "ground_rover.hpp"
#include "geometry.hpp"
#include "misc_math.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define STAB_TMO            MS2ST(20)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t      GlobalFlags;
extern ParamRegistry      param_registry;
extern WpDB               wpdb;

extern mavlink_system_t                 mavlink_system_struct;

extern mavlink_local_position_ned_t     mavlink_out_local_position_ned_struct;
extern mavlink_nav_controller_output_t  mavlink_out_nav_controller_output_struct;
extern mavlink_vfr_hud_t                mavlink_out_vfr_hud_struct;

extern uint8_t currWpFrame;
extern uint16_t WpSeqNew;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static pid_f32_t  speedPid;
static pid_f32_t  headingPid;
static pid_f32_t  xtrackPid;

static float const *speed_min;
static Thread *stab_tp = NULL;

/*
 ******************************************************************************
 * PROTOTYPES
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
 * Stabilization thread.
 * - perform PIDs in infinite loop synchronized with servo PWM
 * - there is now way to cansel task, you only can send new one with zero speed
 *   or home coordinates, etc.
 */
static WORKING_AREA(StabThreadWA, 512);
static msg_t StabThread(void* arg){
  chRegSetThreadName("StabGroundRover");
  (void)arg;

  goto_wp_result_t wp_result;
  uint16_t seq;
  uint16_t wp_cnt;

WAIT_NEW_MISSION:
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

  clearGlobalFlag(GlobalFlags.mission_abort);
  clearGlobalFlag(GlobalFlags.mission_takeoff);
  clearGlobalFlag(GlobalFlags.mission_loiter);

  reset_pid(&headingPid);
  reset_pid(&speedPid);
  reset_pid(&xtrackPid);

  ServoCarThrustSet(float2thrust(0));
  ServoCarYawSet(128);
  while(!GlobalFlags.mission_takeoff)
    chThdSleep(STAB_TMO);

  currWpFrame = MAV_FRAME_GLOBAL;
  seq = 0;
  wp_cnt = wpdb.getCount();

  /* are there some waypoints on board? */
  if (wp_cnt == 0)
    goto WAIT_NEW_MISSION; /* nothing to do */

  /* loop the whole mission */
  do {
    wp_result = goto_wp(seq);
    switch (wp_result){
    case WP_GOTO_REACHED:
      /* regular schedule next waypoint */
      broadcast_mission_item_reached(seq);
      seq++;
      break;

    case WP_GOTO_RESCHEDULED:
      /* force schedule specified waypoint */
      seq = WpSeqNew;
      chSysLock();
      WpSeqNew = 0;
      chSysUnlock();
      break;

    default:
      chDbgPanic("");
      break;
    }
  }while (seq < wp_cnt);

  goto WAIT_NEW_MISSION;

  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
Thread* StabInit(void){

  WpLocalInit();
  WpGlobalInit();

  speed_min = (const float*)param_registry.valueSearch("SPD_speed_min");

  speedPid.iGain  = (const float*)param_registry.valueSearch("SPD_iGain");
  speedPid.pGain  = (const float*)param_registry.valueSearch("SPD_pGain");
  speedPid.dGain  = (const float*)param_registry.valueSearch("SPD_dGain");
  speedPid.iMin   = (const float*)param_registry.valueSearch("SPD_iMin");
  speedPid.iMax   = (const float*)param_registry.valueSearch("SPD_iMax");

  headingPid.iGain  = (const float*)param_registry.valueSearch("HDG_iGain");
  headingPid.pGain  = (const float*)param_registry.valueSearch("HDG_pGain");
  headingPid.dGain  = (const float*)param_registry.valueSearch("HDG_dGain");
  headingPid.iMin   = (const float*)param_registry.valueSearch("HDG_iMin");
  headingPid.iMax   = (const float*)param_registry.valueSearch("HDG_iMax");

  xtrackPid.iGain  = (const float*)param_registry.valueSearch("XTRACK_iGain");
  xtrackPid.pGain  = (const float*)param_registry.valueSearch("XTRACK_pGain");
  xtrackPid.dGain  = (const float*)param_registry.valueSearch("XTRACK_dGain");
  xtrackPid.iMin   = (const float*)param_registry.valueSearch("XTRACK_iMin");
  xtrackPid.iMax   = (const float*)param_registry.valueSearch("XTRACK_iMax");

  stab_tp = chThdCreateStatic(StabThreadWA, sizeof(StabThreadWA),
                         CONTROLLER_THREADS_PRIO,
                         StabThread,
                         NULL);
  if (stab_tp == NULL)
    chDbgPanic("can not allocate memory");

  return stab_tp;
}

/**
 * Unlimited loiter intil flag will be cleared.
 */
void loiter_if_need(void){
  switch (mavlink_system_struct.type){

  case MAV_TYPE_GROUND_ROVER:
    loiter_ground_rover();
    break;

  case MAV_TYPE_FIXED_WING:
    chDbgPanic("This mode is unsupported");
    break;

  default:
    chDbgPanic("This mode is unsupported");
    break;
  }
}

/**
 *
 */
void pid_keep_heading(float current, float desired){
  float impact;
  float error;

  error = wrap_pi(desired - current);
  impact = UpdatePID(&headingPid, error, current);
  putinrange(impact, -0.2f, 0.2f);
  ServoCarYawSet(float2servo(impact));
}

/**
 *
 */
void pid_keep_speed(float current, float desired){
  float impact = 0;

  impact = UpdatePID(&speedPid, desired - current, current);

  mavlink_out_vfr_hud_struct.groundspeed = current;
  mavlink_out_nav_controller_output_struct.aspd_error = desired - current;

  /* this check need because we can not get direction */
  if (impact < 0)
    impact = 0;

  ServoCarThrustSet(float2thrust(impact));
}
