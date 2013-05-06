#include <math.h>

#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "sensors.hpp"
#include "gps.hpp"
#include "param_registry.hpp"
#include "stab.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define TARGET_RADIUS       param2      /* dirty fix to correspond QGC not mavlink lib */
#define METERS_IN_DEGREE    111194.93f  /* meters in one degree on equator */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern ParamRegistry param_registry;

extern uint8_t currWpFrame;
extern uint16_t WpSeqNew;
extern chibios_rt::BinarySemaphore servo_updated_sem;
extern CompensatedData comp_data;
extern RawData raw_data;
extern mavlink_nav_controller_output_t  mavlink_out_nav_controller_output_struct;
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

  mavlink_out_nav_controller_output_struct.wp_dist =
      sqrtf(delta_x*delta_x + delta_y*delta_y) * METERS_IN_DEGREE;

  //NOTE: atan2(0,0) is forbidden arguments
  if (mavlink_out_nav_controller_output_struct.wp_dist > wp->TARGET_RADIUS){
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
