#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SPEEDOMETER_TMO   MS2ST(1000)

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
static float      *cminpulse;
static pid_f32    spd_pid;

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
 * k - cm in one pulse (got from params)
 *
 *      S      k / 100          k
 * v = --- = ------------ = ------------
 *      t    uS / 1000000   uS / 10000.0
 */
float calc_speed(uint32_t uS){
  if (uS == 0)/* prevent division by zero */
    return 3;
  float k = *cminpulse;
  float t = ((float)uS / 10000.0);
  return k / t;
}

/**
 *
 */
void speed_control(float speed){

  /* do PID stuff */
  float desired = 1.2;
  UpdatePID(&spd_pid, desired - speed, speed);

  //ServoCarThrustSet((uint8_t)((3.0 / 128) * drive) + 128);
}

/**
 *
 */
static WORKING_AREA(StabThreadWA, 512);
static msg_t StabThread(void* arg){
  chRegSetThreadName("Stab");
  (void)arg;

  msg_t tmp = 0;
  msg_t status = 0;
  uint32_t t = 0;

  const uint32_t MEDIAN_FILTER_LEN = 3;
  uint32_t tacho_filter_buf[MEDIAN_FILTER_LEN];

  /* reset filter */
  uint32_t i = 0;
  for (i=0; i < MEDIAN_FILTER_LEN; i++)
    tacho_filter_buf[i] = 0;

  while (TRUE) {
    /* get current speed */
    status = chMBFetch(&speedometer_mb, &tmp, SPEEDOMETER_TMO);
    if (status == RDY_OK){
      t = median_filter_3(tacho_filter_buf, RTT2US(tmp));
      comp_data.groundspeed = calc_speed(t);
      bkpOdometer++;
    }
    else
      comp_data.groundspeed = 0.0;

    mavlink_vfr_hud_struct.groundspeed = comp_data.groundspeed;
  }
  return 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

Thread* SpeedControlInit(void){

  cminpulse = ValueSearch("SPD_cminpulse");

  spd_pid.iGain = ValueSearch("SPD_iGain");
  spd_pid.pGain = ValueSearch("SPD_pGain");
  spd_pid.dGain = ValueSearch("SPD_dGain");
  spd_pid.iMax = 20;
  spd_pid.iMin = -20;
  spd_pid.iState = 0;
  spd_pid.dState = 0;

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap, sizeof(StabThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            StabThread,
                            NULL);
  if (tp == NULL)
    chdbgPanic("Can not allocate memory");

  return tp;
}

