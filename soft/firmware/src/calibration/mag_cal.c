#include <math.h>
#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define NEW_POSITION_THRESHOLD 30000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern uint32_t GlobalFlags;
extern MemoryHeap ThdHeap;
extern mavlink_system_t mavlink_system_struct;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* sums for offset calibration */
static BinarySemaphore mag_cal_sem;

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
/**
 * You must turn device in new position
 */
msg_t wait_new_position(void){
  int16_t prevx, prevy, prevz;
  uint32_t delta = 0;
  const uint32_t tmo = 200;
  const uint32_t overall_tmo = 60000;
  uint32_t retry = overall_tmo / tmo;

  prevx = raw_data.xmag;
  prevy = raw_data.ymag;
  prevz = raw_data.zmag;

  while (delta < NEW_POSITION_THRESHOLD){
    delta  = (prevx - raw_data.xmag) * (prevx - raw_data.xmag);
    delta += (prevy - raw_data.ymag) * (prevy - raw_data.ymag);
    delta += (prevz - raw_data.zmag) * (prevz - raw_data.zmag);
    retry--;
    if (retry == 0)
      return RDY_RESET;
    chThdSleepMilliseconds(tmo);
  }
  return RDY_OK;
}

/* test matrix */
//  int32_t P[4][3]={{2572, -2819, -1864},
//                   {2393, -2990, -1864},
//                   {2320, -2701, -1867},
//                   {2423, -2800, -1907}};

#define clear_state() {\
  SamplesCnt = *zerocount;\
  MagSumX = 0;\
  MagSumY = 0;\
  MagSumZ = 0;\
  device_still_clear();\
}

/**
 *
 */
static WORKING_AREA(MagCalThreadWA, 512);
static msg_t MagCalThread(void *arg){
  chRegSetThreadName("MagCal");
  (void)arg;

  int32_t const *zerocount = ValueSearch("MAG_zerocnt");
  uint32_t CurrentPoint = 0;
  uint32_t SamplesCnt = *zerocount;
  int32_t MagSumX = 0, MagSumY = 0, MagSumZ = 0;
  msg_t sem_status = RDY_OK;
  msg_t wait_status = RDY_RESET;
  Sphere S = {{0,0,0}, 0};
  int32_t P[4][3]={{0, 0, 0},
                   {0, 0, 0},
                   {0, 0, 0},
                   {0, 0, 0}};

  mavlink_system_struct.state = MAV_STATE_CALIBRATING;
  clear_state();

  /* main loop */
  while(CurrentPoint < 4){
    while(SamplesCnt){
      sem_status = chBSemWaitTimeout(&mag_cal_sem, MS2ST(200));
      if (sem_status == RDY_OK){
        if(is_device_still()){
          MagSumX += raw_data.xmag;
          MagSumY += raw_data.ymag;
          MagSumZ += raw_data.zmag;
          SamplesCnt--;
          SheduleBlink(3, MS2ST(100), MS2ST(1));
        }
        else{
          /* clear all collected statistics */
          clear_state();
          SheduleBlink(3, MS2ST(20), MS2ST(100));
        }
      }
      /* sigterm handler */
      if (chThdShouldTerminate())
        goto TERMINATE;
    }

    /* store collected point and go to next step */
    P[CurrentPoint][0] = MagSumX / *zerocount;
    P[CurrentPoint][1] = MagSumY / *zerocount;
    P[CurrentPoint][2] = MagSumZ / *zerocount;
    clear_state();
    CurrentPoint++;

    if (CurrentPoint < 4){
      SheduleBlink(30000, MS2ST(500), MS2ST(500));
      wait_status = wait_new_position();
      if (wait_status != RDY_OK)
        goto TERMINATE;
    }
  }

  /* all points got. Calculate sphere */
  SolveSphere(&S, P);
  *(int32_t *)(ValueSearch("MAG_xoffset")) = floorf(S.c[0]);
  *(int32_t *)(ValueSearch("MAG_yoffset")) = floorf(S.c[1]);
  *(int32_t *)(ValueSearch("MAG_zoffset")) = floorf(S.c[2]);

TERMINATE:
  clearGlobalFlag(MAG_CAL_FLAG);
  mavlink_system_struct.state = MAV_STATE_STANDBY;
  SheduleBlink(10, MS2ST(100), MS2ST(100));
  chThdExit(0);
  return 0;
}


/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 * Syncronization functions for statistics update.
 */
void mag_stat_update(void){
  chBSemSignal(&mag_cal_sem);
}

/**
 *
 */
Thread* MagCalStart(void){
  chBSemInit(&mag_cal_sem,  TRUE);

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap,
                            sizeof(MagCalThreadWA),
                            NORMALPRIO,
                            MagCalThread,
                            NULL);
  if (tp == NULL){
    chDbgPanic("can not allocate memory");
    return NULL;
  }
  else
    return tp;
}
