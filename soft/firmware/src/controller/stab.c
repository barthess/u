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
extern MemoryHeap ThdHeap;
extern CompensatedData comp_data;
extern mavlink_vfr_hud_t mavlink_vfr_hud_struct;
extern Mailbox speedometer_mb;
extern BinarySemaphore servo_updated_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static pid_f32_t speed_pid;
static pid_f32_t heading_pid;

static float const *pulse2m;

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
void stab_speed_rover(pid_f32_t *spd_pid, float speed, float desired){
  float drive = 0;

  drive = UpdatePID(spd_pid, desired - speed, speed);
  if (drive < 0)
    drive = 0;

  ServoCarThrustSet(float2thrust(drive));
}

/**
 *
 */
void stab_heading_rover(uint32_t heading){
  (void)heading;
}

/**
 * Calculate current ground speed from tachometer pulses
 */
void update_speed_rover(uint32_t *retry){
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
 * Stabilization thread.
 * 1) perform PIDs in infinite loop synchronized with servo PWM
 * 2) every cycle tries to get new task from message_box[1]
 * 3) place task in local variables inside lock
 * 4) there is now way to cansel task, you only can send new one with zero speed
 *    or home coordinates, etc.
 */
static WORKING_AREA(StabThreadWA, 512);
static msg_t StabThread(void* arg){
  chRegSetThreadName("Stab");
  (void)arg;

  uint32_t speed_retry_cnt = 0;

  uint32_t heading = 0;
  float target_trip = 0;
  float speed = 0;
  msg_t status = RDY_RESET;
  msg_t tmp = 0;

  while (TRUE) {
    chBSemWait(&servo_updated_sem);
    update_speed_rover(&speed_retry_cnt);

    //status = chMBFetch(&testpoint_mb, &tmp, TIME_IMMEDIATE);
    if (status == RDY_OK){
      if (tmp != (msg_t)NULL){
        /* load new task */
//        speed = ((test_point_t*)tmp)->speed;
//        heading = ((test_point_t*)tmp)->heading;
//        target_trip = bkpOdometer * *pulse2m;
//        target_trip += ((test_point_t*)tmp)->trip * *pulse2m;
      }
      else
        target_trip = bkpOdometer * *pulse2m;/* task canselled. Stopping. */
    }

    if ((bkpOdometer * *pulse2m) >= target_trip)
      speed = 0; /* task finished. Stopping. */

    stab_speed_rover(&speed_pid, comp_data.groundspeed, speed);
    stab_heading_rover(heading);
  }
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

