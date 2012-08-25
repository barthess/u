#include <math.h>

#include "uav.h"

#include "ground_rover.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define CONTROLLER_TMO    MS2ST(500)
#define SPEEDOMETER_TMO   MS2ST(1000)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
//extern RawData raw_data;
extern Mailbox controller_mb;
extern Mailbox speedometer_mb;
extern MemoryHeap ThdHeap;
extern mavlink_vfr_hud_t mavlink_vfr_hud_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static float   *cminpulse;

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
void manual_control_handler(mavlink_manual_control_t *mavlink_manual_control_struct){
  uint32_t thrust = 0;

  if (mavlink_manual_control_struct->thrust_manual == 1){
    thrust = float2thrust(mavlink_manual_control_struct->thrust);
    ServoCarThrustSet(thrust);
  }
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
      }

      chBSemSignal(mailp->semp);
    }
  }
  return 0;
}

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

  return *cminpulse / ((float)uS / 10000.0);
}

/**
 *
 */
static WORKING_AREA(PidTrustThreadWA, 512);
static msg_t PidTrustThread(void* arg){
  chRegSetThreadName("PidTrust");
  (void)arg;

  msg_t tmp = 0;
  msg_t status = 0;
  uint32_t t = 0; /* */

  const uint32_t MEDIAN_FILTER_LEN = 3;
  uint32_t tacho_filter_buf[MEDIAN_FILTER_LEN];

  /* clear filter */
  uint32_t i = 0;
  for (i=0; i < MEDIAN_FILTER_LEN; i++)
    tacho_filter_buf[i] = 0;

  while (TRUE) {
    status = chMBFetch(&speedometer_mb, &tmp, SPEEDOMETER_TMO);
    if (status == RDY_OK){
      t = median_filter_3(tacho_filter_buf, RTT2US(tmp));
      mavlink_vfr_hud_struct.groundspeed = calc_speed(t);
      bkpOdometer++;
    }
    else{
      mavlink_vfr_hud_struct.groundspeed = 0.0;
    }
  }
  return 0;
}



/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
Thread *ControllerGroundRoverInit(void){

  cminpulse = ValueSearch("ODO_cminpulse");

  Thread *tp = NULL;

  ServoInit();

  Servo4Set(128);
  Servo5Set(128);
  Servo6Set(128);
  Servo7Set(128);
  ServoCarThrustSet(128);

  tp = chThdCreateFromHeap(&ThdHeap, sizeof(ControllerThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            ControllerThread,
                            NULL);

  chThdCreateStatic(PidTrustThreadWA,
        sizeof(PidTrustThreadWA),
        NORMALPRIO,
        PidTrustThread,
        NULL);

  return tp;
}





