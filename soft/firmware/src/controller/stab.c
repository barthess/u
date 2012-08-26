#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/* approximately define calculate retry count
 * stabilization updates syncronously with servos: every 20 ms
 * we nee timout 0.5S */
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
void stab_speed_rover(pid_f32 *spd_pid, float speed, float desired){
  float drive = 0;

  drive = UpdatePID(spd_pid, desired - speed, speed);
  if (drive < 0)
    drive = 0;

  ServoCarThrustSet(float2thrust(drive));
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
 *
 */
static WORKING_AREA(StabThreadWA, 512);
static msg_t StabThread(void* arg){
  chRegSetThreadName("Stab");
  (void)arg;

  uint32_t speed_retry = 0;

  pid_f32 spd_pid;
  spd_pid.iGain  = ValueSearch("SPD_iGain");
  spd_pid.pGain  = ValueSearch("SPD_pGain");
  spd_pid.dGain  = ValueSearch("SPD_dGain");
  spd_pid.iMin   = ValueSearch("SPD_iMin");
  spd_pid.iMax   = ValueSearch("SPD_iMax");
  spd_pid.iState = 0;
  spd_pid.dState = 0;

  while (TRUE) {
    chBSemWait(&servo_updated_sem);
    update_speed_rover(&speed_retry);
    stab_speed_rover(&spd_pid, comp_data.groundspeed, 0.8);
  }
  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

Thread* StabInit(void){

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap, sizeof(StabThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            StabThread,
                            NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}

