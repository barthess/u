#include <math.h>

#include "uav.h"

/* Bearing Between Two Points:
 * http://mathforum.org/library/drmath/view/55417.html
 *
 * Aviation Formulary V1.46:
 * http://williams.best.vwh.net/avform.htm
 */

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/* define approximated retry count
 * stabilization updates syncronously with servos: every 20 ms and
 * we nee timout 500mS */
#define SPEED_UPDATE_RETRY  (500 / 20)
#define STAB_TMO            MS2ST(20)
#define TARGET_RADIUS       param2      /* dirty fix to correspond QGC not mavlink lib */
#define METERS_IN_DEGREE    111194.93f  /* meter in degree on equator */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t           GlobalFlags;
extern RawData            raw_data;
extern CompensatedData    comp_data;
extern mavlink_vfr_hud_t  mavlink_vfr_hud_struct;
extern Mailbox            speedometer_mb;
extern BinarySemaphore    servo_updated_sem;
extern Mailbox            tolink_mb;

extern mavlink_mission_current_t      mavlink_mission_current_struct;
extern mavlink_mission_item_reached_t mavlink_mission_item_reached_struct;

extern float LongitudeScale;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint32_t speedRetryCnt = 0;

static pid_f32_t speedPid;
static pid_f32_t headingPid;
static uint16_t WpSeqNew = 0;

static float const *pulse2m;
static float const *speed_min;

static Mail mission_current_mail = {NULL, MAVLINK_MSG_ID_MISSION_CURRENT, NULL};
static Mail mission_item_reached_mail = {NULL, MAVLINK_MSG_ID_MISSION_ITEM_REACHED, NULL};

static uint8_t currWpFrame = MAV_FRAME_GLOBAL;
static float xPrevWp = 0, yPrevWp = 0; /* for local NED waypoint calculations */

float CurrentWpRadius;        /* radius of current waypoing in degrees */
float CurrentWpPseudoRadius;  /* the length of the side of a square of approximated waypoing radius */

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
 *
 */
static bool_t is_local_ned_wp_reached(float target_trip){
  if ((bkpOdometer * *pulse2m) >= target_trip)
    return TRUE;
  else
    return FALSE;
}

/**
 * Unlimited loiter intil flag will be cleared.
 */
static void loiter_if_need(void){
  while (GlobalFlags & MISSION_LOITER_FLAG){
    ServoCarThrustSet(128);
    chThdSleep(STAB_TMO);
  }
}

/**
 *
 */
static void reset_pids(void){
  speedPid.iState   = 0;
  speedPid.dState   = 0;
  headingPid.iState = 0;
  headingPid.dState = 0;
}

/**
 *
 */
static void broadcast_mission_current(uint16_t seq){
  mavlink_mission_current_struct.seq = seq;
  mission_current_mail.invoice = MAVLINK_MSG_ID_MISSION_CURRENT;
  mission_current_mail.payload = &mavlink_mission_current_struct;
  chMBPost(&tolink_mb, (msg_t)&mission_current_mail, TIME_IMMEDIATE);
  log_write_schedule(MAVLINK_MSG_ID_MISSION_CURRENT, NULL, 0);
}

/**
 *
 */
static void broadcast_mission_item_reached(uint16_t seq){
  mavlink_mission_item_reached_struct.seq = seq;
  mission_item_reached_mail.invoice = MAVLINK_MSG_ID_MISSION_ITEM_REACHED;
  mission_item_reached_mail.payload = &mavlink_mission_item_reached_struct;
  chMBPost(&tolink_mb, (msg_t)&mission_item_reached_mail, TIME_IMMEDIATE);
  log_write_schedule(MAVLINK_MSG_ID_MISSION_ITEM_REACHED, NULL, 0);
}

/**
 *
 */
static void pid_keep_speed(pid_f32_t *spd_pidp, float current, float desired){
  float impact = 0;

  impact = UpdatePID(spd_pidp, desired - current, current);

  /* this check need because we can not get direction */
  if (impact < 0)
    impact = 0;

  ServoCarThrustSet(float2thrust(impact));
}

/**
 *
 */
static void pid_keep_heading(pid_f32_t *hdng_pidp, float current, float desired){
  float impact;
  float error;

  error = wrap_pi(desired - current);
  impact = UpdatePID(hdng_pidp, error, current);
  putinrange(impact, -0.2f, 0.2f);
  ServoCarYawSet(float2servo(impact));
}

/**
 * Calculate current ground speed from tachometer pulses
 */
static void update_odometer_speed(void){
  msg_t tmp = 0;
  msg_t status = 0;

  /* get current speed without waiting, because it updates very slowly comparing to other sensors */
  status = chMBFetch(&speedometer_mb, &tmp, TIME_IMMEDIATE);
  if (status == RDY_OK){
    comp_data.groundspeed = calc_ground_rover_speed(tmp);
    speedRetryCnt = 0;
  }
  else{
    speedRetryCnt++;
    if (speedRetryCnt > SPEED_UPDATE_RETRY){
      speedRetryCnt = SPEED_UPDATE_RETRY + 2; // to avoid overflow
      comp_data.groundspeed = 0.0; /* device is still */
    }
  }

  /* set variable for telemetry */
  mavlink_vfr_hud_struct.groundspeed = comp_data.groundspeed;
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

/**
 * Handle waypoint with MAV_FRAME_LOCAL_NED
 */
static goto_wp_result_t goto_wp_local_ned(mavlink_mission_item_t *wp){

  float target_trip = 0;
  float target_heading = 0;
  speedRetryCnt = 0;

  broadcast_mission_current(wp->seq);
  parse_local_ned_wp(wp, &target_heading, &target_trip);

  /* stabilization loop for single waypoint */
  while (!is_local_ned_wp_reached(target_trip)){
    if (GlobalFlags & MISSION_ABORT_FLAG)
      return WP_GOTO_ABORTED;

    loiter_if_need();

    if (WpSeqNew != 0)
      return WP_GOTO_RESCHEDULED;

    chBSemWait(&servo_updated_sem);
    update_odometer_speed();
    pid_keep_speed(&speedPid, comp_data.groundspeed, *speed_min);
    pid_keep_heading(&headingPid, comp_data.heading, target_heading);
  }
  return WP_GOTO_REACHED;
}

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

  //NOTE: atan2(0,0) is forbidden arguments
  if (fabsf(delta_x) > CurrentWpPseudoRadius || fabsf(delta_y) > CurrentWpPseudoRadius){
    *heading = atan2f(delta_y, delta_x);
    return FALSE;
  }
  else
    return TRUE;
}

/**
 * Handle waypoint with MAV_FRAME_GLOBAL
 */
static goto_wp_result_t goto_wp_global(mavlink_mission_item_t *wp){
  float target_heading = 0;

  broadcast_mission_current(wp->seq);

  CurrentWpPseudoRadius = (sqrtf(2)/2) * (wp->TARGET_RADIUS / METERS_IN_DEGREE);

  /* stabilization loop for single waypoint */
  while (!is_global_wp_reached(wp, &target_heading)){
    if (GlobalFlags & MISSION_ABORT_FLAG)
      return WP_GOTO_ABORTED;

    loiter_if_need();

    if (WpSeqNew != 0)
      return WP_GOTO_RESCHEDULED;

    chBSemWait(&servo_updated_sem);
    update_odometer_speed();
    pid_keep_speed(&speedPid, comp_data.groundspeed, *speed_min);
//    if ((comp_data.groundspeed > 0.3) && raw_data.gps_valid)
//      pid_keep_heading(&headingPid, fdeg2rad(raw_data.gps_course / 100.0 - 180), target_heading);
//    else
      pid_keep_heading(&headingPid, comp_data.heading, target_heading);
  }
  return WP_GOTO_REACHED;
}

/**
 * Get waypoint from EEPROM
 * determine its type and call specialized routine
 */
static goto_wp_result_t goto_wp(uint16_t seq){
  mavlink_mission_item_t wp;
  bool_t status = WP_FAILED;

  /* get current waypoint */
  status = get_waypoint_from_eeprom(seq, &wp);
  if (status != WP_SUCCESS)
    return WP_GOTO_FAILED;
  else{
    switch (wp.frame){
    case MAV_FRAME_LOCAL_NED:
      return goto_wp_local_ned(&wp);
      break;

    case MAV_FRAME_GLOBAL:
      return goto_wp_global(&wp);
      break;

    default:
      chDbgPanic("");
      break;
    }
  }

  return WP_GOTO_FAILED;
}


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
  clearGlobalFlag(MISSION_ABORT_FLAG);
  clearGlobalFlag(MISSION_TAKEOFF_FLAG);
  clearGlobalFlag(MISSION_LOITER_FLAG);
  reset_pids();
  ServoCarThrustSet(128);
  ServoCarYawSet(128);
  while(!(GlobalFlags & MISSION_TAKEOFF_FLAG))
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
void WpSeqOverwrite(uint16_t seq){
  if (WpSeqNew < get_waypoint_count()){
    chSysLock();
    WpSeqNew = seq;
    chSysUnlock();
  }
}

/**
 *
 */
Thread* StabInit(void){

  pulse2m   = ValueSearch("SPD_pulse2m");
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

  Thread *tp = NULL;

  tp = chThdCreateStatic(StabThreadWA, sizeof(StabThreadWA),
                         CONTROLLER_THREADS_PRIO,
                         StabThread,
                         NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}

