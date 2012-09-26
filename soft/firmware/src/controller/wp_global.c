#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define TARGET_RADIUS       param2      /* dirty fix to correspond QGC not mavlink lib */
#define METERS_IN_DEGREE    111194.93f  /* meter in degree on equator */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;
extern uint8_t currWpFrame;
extern uint16_t WpSeqNew;
extern BinarySemaphore servo_updated_sem;
extern CompensatedData comp_data;
extern RawData raw_data;
extern mavlink_nav_controller_output_t  mavlink_nav_controller_output_struct;
extern float LongitudeScale;

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
static float const *speed_min;

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
/**
 * Calculate heading needed to reach waypoint and return TRUE if waypoint reached.
 */
static bool_t is_global_wp_reached(mavlink_mission_item_t *wp, float *heading){
  float delta_x;
  float delta_y;

  currWpFrame = MAV_FRAME_GLOBAL;

  delta_x = wp->x - (raw_data.gps_latitude  / GPS_FIXED_POINT_SCALE);
  delta_y = wp->y - (raw_data.gps_longitude / GPS_FIXED_POINT_SCALE);
  delta_y *= LongitudeScale;

  mavlink_nav_controller_output_struct.wp_dist =
      sqrtf(delta_x*delta_x + delta_y*delta_y) * METERS_IN_DEGREE;

  //NOTE: atan2(0,0) is forbidden arguments
  if (mavlink_nav_controller_output_struct.wp_dist > wp->TARGET_RADIUS){
    *heading = atan2f(delta_y, delta_x);
    return FALSE;
  }
  else
    return TRUE;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void WpGlobalInit(void){
  speed_min = ValueSearch("SPD_speed_min");
}

/**
 * Handle waypoint with MAV_FRAME_GLOBAL
 */
goto_wp_result_t goto_wp_global(mavlink_mission_item_t *wp){
  float target_heading = 0;

  broadcast_mission_current(wp->seq);

  /* stabilization loop for single waypoint */
  while (!is_global_wp_reached(wp, &target_heading)){
    if (GlobalFlags & MISSION_ABORT_FLAG)
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
