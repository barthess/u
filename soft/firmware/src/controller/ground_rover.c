/*
 * Stores functions sutable for ground rover - pulses to speed conversio, etc.
 */
#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define CONTROLLER_TMO      MS2ST(50)
#define MEDIAN_FILTER_LEN   3

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern MemoryHeap ThdHeap;

extern EventSource event_mavlink_in_manual_control;
extern EventSource event_mavlink_in_set_mode;
extern EventSource event_mavlink_in_mission_set_current;

extern mavlink_manual_control_t mavlink_in_manual_control_struct;
extern mavlink_set_mode_t mavlink_in_set_mode_struct;
extern mavlink_mission_set_current_t mavlink_in_mission_set_current_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint32_t tacho_filter_buf[MEDIAN_FILTER_LEN];
static float const *pulse2m;
static Thread *groundrover_tp = NULL;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 *
 */
static void manual_control_handler(mavlink_manual_control_t *mc){
  uint32_t v = 0;

//  if (mc->thrust_manual == 1){
//    v = float2thrust(mc->thrust);
//    ServoCarThrustSet(v);
//  }
//  if (mc->yaw_manual == 1){
//    v = float2servo(mc->yaw);
//    Servo7Set(v);
//  }
}

/**
 * Set autopilot mode logic.
 */
static void set_current_wp_handler(mavlink_mission_set_current_t *sc){
  WpSeqOverwrite(sc->seq);
}

/**
 *
 */
static WORKING_AREA(ControllerThreadWA, 512);
static msg_t ControllerThread(void* arg){
  chRegSetThreadName("Ground_rover");
  (void)arg;

  while(GlobalFlags.messaging_ready == 0)
  chThdSleepMilliseconds(50);

  eventmask_t evt = 0;
  struct EventListener el_manual_control;
  struct EventListener el_set_mode;
  struct EventListener el_mission_set_current;
  chEvtRegisterMask(&event_mavlink_in_manual_control,       &el_manual_control,     EVMSK_MAVLINK_IN_MANUAL_CONTROL);
  chEvtRegisterMask(&event_mavlink_in_set_mode,             &el_set_mode,           EVMSK_MAVLINK_IN_SET_MODE);
  chEvtRegisterMask(&event_mavlink_in_mission_set_current,  &el_mission_set_current,EVMSK_MAVLINK_IN_MISSION_SET_CURRENT);

  while (!chThdShouldTerminate()) {
    evt = chEvtWaitOne(EVMSK_MAVLINK_IN_MANUAL_CONTROL | EVMSK_MAVLINK_IN_SET_MODE | EVMSK_MAVLINK_IN_MISSION_SET_CURRENT);

    switch (evt){
      case EVMSK_MAVLINK_IN_MANUAL_CONTROL:
        manual_control_handler(&mavlink_in_manual_control_struct);
        break;
      case EVMSK_MAVLINK_IN_SET_MODE:
        set_mode_handler(&mavlink_in_set_mode_struct);
        break;
      case EVMSK_MAVLINK_IN_MISSION_SET_CURRENT:
        set_current_wp_handler(&mavlink_in_mission_set_current_struct);
        break;
    }
  }

  chEvtUnregister(&event_mavlink_in_manual_control,       &el_manual_control);
  chEvtUnregister(&event_mavlink_in_set_mode,             &el_set_mode);
  chEvtUnregister(&event_mavlink_in_mission_set_current,  &el_mission_set_current);

  chThdExit(0);
  return 0;
}

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
 * k - m in one pulse (got from params)
 *
 *      S      k
 * v = --- = ------------
 *      t    uS / 1000000
 */
float calc_ground_rover_speed(uint32_t rtt){

  uint32_t uS = 0;
  uS = median_filter_3(tacho_filter_buf, RTT2US(rtt));

  if (uS == 0)/* prevent division by zero */
    return 3;

  float t = ((float)uS / 1000000.0);
  return *pulse2m / t;
}

/**
 * Start stabilization thread on command from ground.
 * TODO: handle different takeoff cmd parameters
 */
enum MAV_RESULT cmd_nav_takeoff_handler(mavlink_command_long_t *cl){
  /* Takeoff from ground / hand
   * | Minimum pitch (if airspeed sensor present), desired pitch without sensor
   * | Empty
   * | Empty
   * | Yaw angle (if magnetometer present), ignored without magnetometer
   * | Latitude
   * | Longitude
   * | Altitude|  */
  (void)cl;

  if (GlobalFlags.mission_takeoff)    /* allready done */
    return MAV_RESULT_TEMPORARILY_REJECTED;
  else{
    setGlobalFlag(GlobalFlags.mission_takeoff);
    return MAV_RESULT_ACCEPTED;
  }
  /* default value */
  return MAV_RESULT_FAILED;
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
  return MAV_RESULT_UNSUPPORTED;}

/**
 * Flight straight to land location
 */
enum MAV_RESULT cmd_nav_land_handler(mavlink_command_long_t *cl){
  (void)cl;
  WpSeqOverwrite(get_waypoint_count() - 1);
  return MAV_RESULT_ACCEPTED;
}

/**
 *
 */
Thread *ControllerGroundRoverInit(void){

  pulse2m = ValueSearch("SPD_pulse2m");

  /* reset filter */
  uint32_t i = 0;
  for (i=0; i < MEDIAN_FILTER_LEN; i++)
    tacho_filter_buf[i] = 0;

  ServoInit();
  Servo4Set(128);
  Servo5Set(128);
  Servo6Set(128);
  Servo7Set(128);
  ServoCarThrustSet(128);

  PlannerInit();
  StabInit();

  groundrover_tp = chThdCreateFromHeap(&ThdHeap, sizeof(ControllerThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            ControllerThread,
                            NULL);
  if (groundrover_tp == NULL)
    chDbgPanic("can not allocate memory");

  return groundrover_tp;
}

