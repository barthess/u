#include <math.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/* define approximated retry count
 * stabilization updates syncronously with servos: every 20 ms and
 * we nee timout 500mS */
#define SPEED_UPDATE_RETRY  (500 / 20)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
//extern RawData raw_data;
extern MemoryHeap         ThdHeap;
extern CompensatedData    comp_data;
extern mavlink_vfr_hud_t  mavlink_vfr_hud_struct;
extern Mailbox            speedometer_mb;
extern BinarySemaphore    servo_updated_sem;
extern Mailbox            tolink_mb;

extern mavlink_mission_current_t      mavlink_mission_current_struct;
extern mavlink_mission_item_reached_t mavlink_mission_item_reached_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static pid_f32_t speed_pid;
static pid_f32_t heading_pid;
static float x_prev_wp = 0, y_prev_wp = 0;

static float const *pulse2m;

static Mail mission_current_mail = {NULL, MAVLINK_MSG_ID_MISSION_CURRENT, NULL};
static Mail mission_item_reached_mail = {NULL, MAVLINK_MSG_ID_MISSION_ITEM_REACHED, NULL};

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
static void broadcast_mission_current(uint16_t seq){
  mavlink_mission_current_struct.seq = seq;
  mission_current_mail.invoice = MAVLINK_MSG_ID_MISSION_CURRENT;
  mission_current_mail.payload = &mavlink_mission_current_struct;
  chMBPost(&tolink_mb, (msg_t)&mission_current_mail, TIME_IMMEDIATE);
}

/**
 *
 */
static void broadcast_mission_item_reached(uint16_t seq){
  mavlink_mission_item_reached_struct.seq = seq;
  mission_item_reached_mail.invoice = MAVLINK_MSG_ID_MISSION_ITEM_REACHED;
  mission_item_reached_mail.payload = &mavlink_mission_item_reached_struct;
  chMBPost(&tolink_mb, (msg_t)&mission_item_reached_mail, TIME_IMMEDIATE);
}

/**
 *
 */
static void keep_speed(pid_f32_t *spd_pidp, float current, float desired){
  float impact = 0;

  impact = UpdatePID(spd_pidp, desired - current, current);
  if (impact < 0)
    impact = 0;

  ServoCarThrustSet(float2thrust(impact));
}

/**
 *
 */
static void keep_heading(pid_f32_t *hdng_pidp, float current, float desired){
  float impact = 0;

  impact = UpdatePID(hdng_pidp, desired - current, current);
  if (impact < 0)
    impact = 0;

  ServoCarYawSet(float2servo(impact));
}

/**
 * Calculate current ground speed from tachometer pulses
 */
static void measure_speed(uint32_t *retry){
  msg_t tmp = 0;
  msg_t status = 0;

  /* get current speed without waiting, because it updates very slowly comparing to other sensors */
  status = chMBFetch(&speedometer_mb, &tmp, TIME_IMMEDIATE);
  if (status == RDY_OK){
    comp_data.groundspeed = calc_ground_rover_speed(tmp);
    *retry = 0;
  }
  else{
    (*retry)++;
    if (*retry > SPEED_UPDATE_RETRY){
      *retry = SPEED_UPDATE_RETRY + 2; // to avoid overflow
      comp_data.groundspeed = 0.0;
    }
  }

  /* set variable for telemetry */
  mavlink_vfr_hud_struct.groundspeed = comp_data.groundspeed;
}

/**
 * Load waypoint from EEPROM and calculate desired values.
 */
static bool_t parse_next_wp(uint16_t seq, float *heading, float *target_trip){
  mavlink_mission_item_t wp;
  bool_t status = WP_FAILED;

  /* get current waypoint */
  status = get_waypoint_from_eeprom(seq, &wp);
  if (status != WP_SUCCESS)
    return WP_FAILED;
  else{
    float delta_x = x_prev_wp - wp.x;
    float delta_y = y_prev_wp - wp.y;
    *heading = atan2f(delta_x, delta_y);
    *target_trip = sqrtf(delta_x * delta_x + delta_y * delta_y);
  }

  /* save values for next iteration */
  x_prev_wp = wp.x;
  y_prev_wp = wp.y;
  return WP_SUCCESS;
}

/**
 *
 */
bool_t is_wp_reached(float target_trip){
  if ((bkpOdometer * *pulse2m) >= target_trip)
    return TRUE;
  else
    return FALSE;
}

/**
 * Stabilization thread.
 * 1) perform PIDs in infinite loop synchronized with servo PWM
 * 2) every cycle tries to get new task from message_box[1]
 * 3) place task in local variables inside lock
 * 4) there is now way to cansel task, you only can send new one with zero speed
 *    or home coordinates, etc.
 */
static WORKING_AREA(StabThreadWA, 512);
static msg_t StabThread(void* arg){
  chRegSetThreadName("StabGroundRover");
  (void)arg;

  uint32_t speed_retry_cnt = 0;
  float target_trip = bkpOdometer * *pulse2m; /* current position is starting point */
  float desired_heading = 0;
  float desired_speed = 1.5;
  uint16_t seq = 0;
  uint16_t wp_cnt = get_waypoint_count();

  /* are there some waypoints on board? */
  if (wp_cnt == 0)
    chThdExit(RDY_RESET);

  do {
    parse_next_wp(seq, &desired_heading, &target_trip);
    broadcast_mission_current(seq);

    while (!is_wp_reached(target_trip)){
      chBSemWait(&servo_updated_sem);
      measure_speed(&speed_retry_cnt);
      keep_speed(&speed_pid, comp_data.groundspeed, desired_speed);
      keep_heading(&heading_pid, comp_data.heading, desired_heading);
    }

    broadcast_mission_item_reached(seq);
    seq++;
  } while (seq < wp_cnt);

  /* mission complete */
  chThdExit(RDY_OK);
  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

Thread* StabInit(void){

  pulse2m = ValueSearch("SPD_pulse2m");

  speed_pid.iGain  = ValueSearch("SPD_iGain");
  speed_pid.pGain  = ValueSearch("SPD_pGain");
  speed_pid.dGain  = ValueSearch("SPD_dGain");
  speed_pid.iMin   = ValueSearch("SPD_iMin");
  speed_pid.iMax   = ValueSearch("SPD_iMax");
  speed_pid.iState = 0;
  speed_pid.dState = 0;

  heading_pid.iGain  = ValueSearch("HEAD_iGain");
  heading_pid.pGain  = ValueSearch("HEAD_pGain");
  heading_pid.dGain  = ValueSearch("HEAD_dGain");
  heading_pid.iMin   = ValueSearch("HEAD_iMin");
  heading_pid.iMax   = ValueSearch("HEAD_iMax");
  heading_pid.iState = 0;
  heading_pid.dState = 0;

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap, sizeof(StabThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            StabThread,
                            NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}

