#include <math.h>

#include "uav.h"

/*
 * Bearing Between Two Points:
 * http://mathforum.org/library/drmath/view/55417.html
 *
 * Aviation Formulary V1.46:
 * http://williams.best.vwh.net/avform.htm
 *
 * what is crosstrack error in pictures
 * http://diydrones.com/profiles/blogs/705844:BlogPost:43438
 *
 * Calculate distance, bearing and more between Latitude/Longitude points
 * http://www.movable-type.co.uk/scripts/latlong.html
 */

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
extern mavlink_vfr_hud_t  mavlink_vfr_hud_struct;

extern mavlink_local_position_ned_t     mavlink_local_position_ned_struct;
extern mavlink_nav_controller_output_t  mavlink_nav_controller_output_struct;
extern mavlink_vfr_hud_t                mavlink_vfr_hud_struct;
extern mavlink_system_t                 mavlink_system_struct;

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
 * Calculate course correction of cross track error.
 */
//static float pid_keep_track(pid_f32_t *track_pidp, float current, float desired){
//  float impact;
//  float error;
//
//  error = desired - current;
//  impact = UpdatePID(track_pidp, error, current);
//  return impact;
//}

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
  mavlink_nav_controller_output_struct.nav_roll       = 0;
  mavlink_nav_controller_output_struct.nav_pitch      = 0;
  mavlink_nav_controller_output_struct.alt_error      = 0;
  mavlink_nav_controller_output_struct.aspd_error     = 0;
  mavlink_nav_controller_output_struct.wp_dist        = 0;
  mavlink_nav_controller_output_struct.nav_bearing    = 0;
  mavlink_nav_controller_output_struct.target_bearing = 0;
  mavlink_nav_controller_output_struct.xtrack_error   = 0;

  mavlink_local_position_ned_struct.x  = 0;
  mavlink_local_position_ned_struct.y  = 0;
  mavlink_local_position_ned_struct.z  = 0;
  mavlink_local_position_ned_struct.vx = 0;
  mavlink_local_position_ned_struct.vy = 0;
  mavlink_local_position_ned_struct.vz = 0;
  mavlink_local_position_ned_struct.time_boot_ms = TIME_BOOT_MS;

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
  wp_cnt = get_waypoint_count();

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
  SpeedometerInit();

  speed_min = ValueSearch("SPD_speed_min");

  speedPid.iGain  = ValueSearch("SPD_iGain");
  speedPid.pGain  = ValueSearch("SPD_pGain");
  speedPid.dGain  = ValueSearch("SPD_dGain");
  speedPid.iMin   = ValueSearch("SPD_iMin");
  speedPid.iMax   = ValueSearch("SPD_iMax");

  headingPid.iGain  = ValueSearch("HEAD_iGain");
  headingPid.pGain  = ValueSearch("HEAD_pGain");
  headingPid.dGain  = ValueSearch("HEAD_dGain");
  headingPid.iMin   = ValueSearch("HEAD_iMin");
  headingPid.iMax   = ValueSearch("HEAD_iMax");

  xtrackPid.iGain  = ValueSearch("XTRACK_iGain");
  xtrackPid.pGain  = ValueSearch("XTRACK_pGain");
  xtrackPid.dGain  = ValueSearch("XTRACK_dGain");
  xtrackPid.iMin   = ValueSearch("XTRACK_iMin");
  xtrackPid.iMax   = ValueSearch("XTRACK_iMax");

  Thread *tp = NULL;

  tp = chThdCreateStatic(StabThreadWA, sizeof(StabThreadWA),
                         CONTROLLER_THREADS_PRIO,
                         StabThread,
                         NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
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

  mavlink_vfr_hud_struct.groundspeed = current;
  mavlink_nav_controller_output_struct.aspd_error = desired - current;

  /* this check need because we can not get direction */
  if (impact < 0)
    impact = 0;

  ServoCarThrustSet(float2thrust(impact));
}
