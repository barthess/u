#include <math.h>
#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

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
/* test matrix */
//  int32_t P[4][3]={{2572, -2819, -1864},
//                   {2393, -2990, -1864},
//                   {2320, -2701, -1867},
//                   {2423, -2800, -1907}};

/*
 * Blink every mag sample - device is not still
 * Light without blinking - collecting statistics
 */
static WORKING_AREA(MagCalThreadWA, 512);
static msg_t MagCalThread(void *arg){
  chRegSetThreadName("MagCal");
  (void)arg;

  uint32_t const *zerocount = ValueSearch("MAG_zerocnt");
  uint32_t CurrentPoint = 0;
  uint32_t SamplesCnt = *zerocount;
  int32_t MagSumX = 0, MagSumY = 0, MagSumZ = 0;
  msg_t sem_status = RDY_OK;
  Sphere S = {{0,0,0}, 0};
  int32_t P[4][3]={{0, 0, 0},
                   {0, 0, 0},
                   {0, 0, 0},
                   {0, 0, 0}};

  mavlink_system_struct.state = MAV_STATE_CALIBRATING;

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
          ProgramBlink(3, MS2ST(100), MS2ST(1));
        }
        else{
          /* clear all collected statistics */
          SamplesCnt = *zerocount;
          MagSumX = 0;
          MagSumY = 0;
          MagSumZ = 0;
          device_still_clear();
          ProgramBlink(2, MS2ST(100), MS2ST(100));
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
    CurrentPoint++;
  }

  /* all points got. Calculate sphere */
  SolveSphere(&S, P);
  *(int32_t *)(ValueSearch("MAG_xoffset")) = floorf(S.c[0]);
  *(int32_t *)(ValueSearch("MAG_yoffset")) = floorf(S.c[1]);
  *(int32_t *)(ValueSearch("MAG_zoffset")) = floorf(S.c[2]);

TERMINATE:
  clearGlobalFlag(MAG_CAL_FLAG);
  mavlink_system_struct.state = MAV_STATE_STANDBY;
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
