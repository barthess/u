#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/* approximately define calculate retry count
 * stabilization updates syncronously with servos: every 20 ms
 * we nee timout 1S */
#define SPEED_UPDATE_RETRY  (1000 / 20)

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
 * Прикинем регулятор:
 * Пусть максимальная скорость будет 2м/с,
 * тогда должен быть выработан следующий сигнал
 * (2/128) * drive + 128
 */
void speed_stab(pid_f32 *spd_pid, float speed){
  float drive = 0;

  /* do PID stuff */
  float desired = 1.0; // hardcoded value
  drive = UpdatePID(spd_pid, desired - speed, speed);
  drive = 128 + drive * (2.0 / 128);

  ServoCarThrustSet(float2thrust(drive / 128));
}

/**
 * Calculate current ground speed from tachometer pulses
 */
void _update_speed(uint32_t *retry){
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
  spd_pid.iGain = ValueSearch("SPD_iGain");
  spd_pid.pGain = ValueSearch("SPD_pGain");
  spd_pid.dGain = ValueSearch("SPD_dGain");
  spd_pid.iMax = 20;
  spd_pid.iMin = -20;
  spd_pid.iState = 0;
  spd_pid.dState = 0;

  while (TRUE) {
    _update_speed(&speed_retry);
    speed_stab(&spd_pid, comp_data.groundspeed);
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

