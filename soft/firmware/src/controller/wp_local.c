#include "uav.h"

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
extern GlobalFlags_t GlobalFlags;
extern uint8_t currWpFrame;
extern uint16_t WpSeqNew;
extern BinarySemaphore servo_updated_sem;
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
static float const *pulse2m;
static float const *speed_min;
static float xPrevWp = 0, yPrevWp = 0; /* for local NED waypoint calculations */

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
static bool_t is_local_ned_wp_reached(float target_trip){
  return (bkpOdometer * *pulse2m) >= target_trip;
}

/**
 * Calculate trip and heading needed to reach waypoint.
 */
static void parse_local_ned_wp(mavlink_mission_item_t *wp, float *heading, float *trip){

  /* clear previosly saved points only if system changed waypoint frame's type */
  if (currWpFrame == MAV_FRAME_GLOBAL){
    xPrevWp = 0;
    yPrevWp = 0;
    currWpFrame = MAV_FRAME_LOCAL_NED;
  }

  float delta_x = wp->x - xPrevWp;
  float delta_y = wp->y - yPrevWp;

  /* first argumetn of atan2 must be y, second - x */
  *heading = atan2f(delta_y, delta_x);

  *trip  = bkpOdometer * *pulse2m;
  *trip += sqrtf(delta_x * delta_x + delta_y * delta_y);

  /* save values for next iteration */
  xPrevWp = wp->x;
  yPrevWp = wp->y;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * Handle waypoint with MAV_FRAME_LOCAL_NED
 */
goto_wp_result_t goto_wp_local_ned(mavlink_mission_item_t *wp){
  float target_trip = 0;
  float target_heading = 0;

  broadcast_mission_current(wp->seq);
  parse_local_ned_wp(wp, &target_heading, &target_trip);

  /* stabilization loop for single waypoint */
  while (!is_local_ned_wp_reached(target_trip)){
    if (GlobalFlags.mission_abort)
      return WP_GOTO_ABORTED;

    loiter_if_need();

    if (WpSeqNew != 0)
      return WP_GOTO_RESCHEDULED;

    chBSemWait(&servo_updated_sem);

    pid_keep_speed(comp_data.groundspeed_odo, *speed_min);
    pid_keep_heading(comp_data.heading, target_heading);
  }
  return WP_GOTO_REACHED;
}

/**
 *
 */
void WpLocalInit(void){
  pulse2m = ValueSearch("SPD_pulse2m");
  speed_min = ValueSearch("SPD_speed_min");
}

