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
//extern RawData raw_data;
extern Mailbox controller_mb;
extern MemoryHeap ThdHeap;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint32_t tacho_filter_buf[MEDIAN_FILTER_LEN];
static uint16_t WpSeqOverwrite = 0;
static float const *pulse2m;
static Thread *stab_tp = NULL;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * k - m in one pulse (got from params)
 *
 *      S      k
 * v = --- = ------------
 *      t    uS / 1000000
 */
float calc_ground_rover_speed(uint32_t rtt){

  uint32_t uS = median_filter_3(tacho_filter_buf, RTT2US(rtt));

  if (uS == 0)/* prevent division by zero */
    return 3;

  float t = ((float)uS / 1000000.0);
  return *pulse2m / t;
}

/**
 *
 */
static void manual_control_handler(mavlink_manual_control_t *mc){
  uint32_t v = 0;

  if (mc->thrust_manual == 1){
    v = float2thrust(mc->thrust);
    ServoCarThrustSet(v);
  }
  if (mc->yaw_manual == 1){
    v = float2servo(mc->yaw);
    Servo7Set(v);
  }
}

/**
 * Set autopilot mode logic.
 */
static void set_current_handler(mavlink_mission_set_current_t *sc){
  chSysLock();
  WpSeqOverwrite = sc->seq;
  chSysUnlock();
}

/**
 *
 */
static WORKING_AREA(ControllerThreadWA, 512);
static msg_t ControllerThread(void* arg){
  chRegSetThreadName("Ground_rover");
  (void)arg;

  Mail* mailp = NULL;
  msg_t tmp = 0;
  msg_t status = 0;

  while (TRUE) {
    status = chMBFetch(&controller_mb, &tmp, CONTROLLER_TMO);
    if (status == RDY_OK){
      mailp = (Mail*)tmp;

      switch(mailp->invoice){
      case MAVLINK_MSG_ID_MANUAL_CONTROL:
        manual_control_handler(mailp->payload);
        break;
      case MAVLINK_MSG_ID_SET_MODE:
        set_mode_handler(mailp->payload);
        break;
      case MAVLINK_MSG_ID_MISSION_SET_CURRENT:
        set_current_handler(mailp->payload);
        break;
      }
      ReleaseMail(mailp);
    }

    /* collect memory from ended stabilization thread */
    if (stab_tp != NULL && stab_tp->p_state == THD_STATE_FINAL){
      chThdWait(stab_tp);
      stab_tp = NULL;
    }
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * Start stabilization thread on command from ground.
 * TODO: handle different takeoff cmd parameters
 */
enum MAV_RESULT cmd_nav_takeoff_handler(mavlink_command_long_t *cl){
  (void)cl;

  if (stab_tp != NULL)    /* probably allready running */
    return MAV_RESULT_TEMPORARILY_REJECTED;

  stab_tp = StabInit();   /* launch stabilization thread */
  if (stab_tp == NULL)
    return MAV_RESULT_FAILED;
  else
    return MAV_RESULT_ACCEPTED;
}

enum MAV_RESULT cmd_nav_return_to_launch_handler(mavlink_command_long_t *cl){
  (void)cl;
  return MAV_RESULT_UNSUPPORTED;
}

enum MAV_RESULT cmd_nav_land_handler(mavlink_command_long_t *cl){
  (void)cl;
  return MAV_RESULT_UNSUPPORTED;
}
enum MAV_RESULT cmd_nav_loiter_unlim_handler(mavlink_command_long_t *cl){
  (void)cl;
  return MAV_RESULT_UNSUPPORTED;
}
enum MAV_RESULT cmd_override_goto_handler(mavlink_command_long_t *cl){
  (void)cl;
  return MAV_RESULT_UNSUPPORTED;
}

/**
 *
 */
Thread *ControllerGroundRoverInit(void){

  WpSeqOverwrite = 0;

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

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap, sizeof(ControllerThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            ControllerThread,
                            &WpSeqOverwrite);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}

