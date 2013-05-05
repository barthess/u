/*
 * Stores functions sutable for ground rover - pulses to speed conversion, etc.
 */
#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "servo.hpp"
#include "controller.hpp"
#include "dsp.hpp"
#include "planner.hpp"
#include "stab.hpp"
#include "param_registry.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define CONTROLLER_TMO      MS2ST(50)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;


/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

static Thread *groundrover_tp = NULL;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */



/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
void loiter_ground_rover(void){
  while (GlobalFlags.mission_loiter){
    ServoCarThrustSet(128);
    chThdSleep(MS2ST(20));
  }
}

/**
 *
 */
enum MAV_RESULT cmd_override_goto_handler(mavlink_command_long_t *cl){
  /* Hold / continue the current action
   * | MAV_GOTO_DO_HOLD: hold MAV_GOTO_DO_CONTINUE: continue with next item in mission plan
   * | MAV_GOTO_HOLD_AT_CURRENT_POSITION: Hold at current position MAV_GOTO_HOLD_AT_SPECIFIED_POSITION: hold at specified position
   * | MAV_FRAME coordinate frame of hold point
   * | Desired yaw angle in degrees
   * | Latitude / X position
   * | Longitude / Y position
   * | Altitude / Z position|  */
  if (cl->param1 == MAV_GOTO_DO_HOLD &&
      cl->param2 == MAV_GOTO_HOLD_AT_CURRENT_POSITION &&
      cl->param3 == 0 &&
      cl->param4 == 0 &&
      cl->param5 == 0 &&
      cl->param6 == 0 &&
      cl->param7 == 0){
    setGlobalFlag(GlobalFlags.mission_loiter);
    return MAV_RESULT_ACCEPTED;
  }
  else if (cl->param1 == MAV_GOTO_DO_CONTINUE &&
           cl->param2 == MAV_GOTO_HOLD_AT_CURRENT_POSITION &&
           cl->param3 == 0 &&
           cl->param4 == 0 &&
           cl->param5 == 0 &&
           cl->param6 == 0 &&
           cl->param7 == 0){
    clearGlobalFlag(GlobalFlags.mission_loiter);
    return MAV_RESULT_ACCEPTED;
  }
  /* default return value */
  return MAV_RESULT_UNSUPPORTED;
}

/**
 * Start unlimited loiter
 */
enum MAV_RESULT cmd_nav_loiter_unlim_handler(mavlink_command_long_t *cl){
  (void)cl;

  if (GlobalFlags.mission_loiter)    /* allready done */
    return MAV_RESULT_TEMPORARILY_REJECTED;
  else{
    setGlobalFlag(GlobalFlags.mission_loiter);
    return MAV_RESULT_ACCEPTED;
  }
  /* default return value */
  return MAV_RESULT_UNSUPPORTED;
}

/* stub */
enum MAV_RESULT cmd_nav_return_to_launch_handler(mavlink_command_long_t *cl){
  (void)cl;
  return MAV_RESULT_UNSUPPORTED;
}

/**
 * Flight straight to land location
 */
enum MAV_RESULT cmd_nav_land_handler(mavlink_command_long_t *cl){
  (void)cl;
  chDbgPanic("uncomment next line");
  //WpSeqOverwrite(get_waypoint_count() - 1);
  return MAV_RESULT_ACCEPTED;
}

/**
 *
 */
Thread *ControllerGroundRoverInit(void){
  StabInit();
  return groundrover_tp;
}

