/*
 * Stores functions sutable for ground rover - pulses to speed conversio, etc.
 */

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define CONTROLLER_TMO      MS2ST(500)
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
static float      *cminpulse;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * k - cm in one pulse (got from params)
 *
 *      S      k / 100          k
 * v = --- = ------------ = ------------
 *      t    uS / 1000000   uS / 10000.0
 */
float calc_ground_rover_speed(uint32_t rtt){

  uint32_t uS = median_filter_3(tacho_filter_buf, RTT2US(rtt));

  if (uS == 0)/* prevent division by zero */
    return 3;

  float k = *cminpulse;
  float t = ((float)uS / 10000.0);
  return k / t;
}

/**
 *
 */
void manual_control_handler(mavlink_manual_control_t *mavlink_manual_control_struct){
  uint32_t v = 0;

  if (mavlink_manual_control_struct->thrust_manual == 1){
    v = float2thrust(mavlink_manual_control_struct->thrust);
    ServoCarThrustSet(v);
  }
  if (mavlink_manual_control_struct->yaw_manual == 1){
    v = float2servo(mavlink_manual_control_struct->yaw);
    Servo7Set(v);
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

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
Thread *ControllerGroundRoverInit(void){

  cminpulse = ValueSearch("SPD_cminpulse");

  /* reset filter */
  uint32_t i = 0;
  for (i=0; i < MEDIAN_FILTER_LEN; i++)
    tacho_filter_buf[i] = 0;

  ServoInit();
  NavigationInit();
  StabInit();

  Servo4Set(128);
  Servo5Set(128);
  Servo6Set(128);
  Servo7Set(128);
  ServoCarThrustSet(128);

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap, sizeof(ControllerThreadWA),
                            CONTROLLER_THREADS_PRIO,
                            ControllerThread,
                            NULL);
  if (tp == NULL)
    chDbgPanic("Can not allocate memory");

  return tp;
}

