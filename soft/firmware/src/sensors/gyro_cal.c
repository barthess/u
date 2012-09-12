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
static BinarySemaphore gyro_cal_sem;

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/*
 * Blink every mag sample - device is not still
 * Light without blinking - collecting statistics
 */
static WORKING_AREA(GyroCalThreadWA, 512);
static msg_t GyroCalThread(void *arg){
  chRegSetThreadName("GyroCal");
  (void)arg;

  uint32_t const *zerocount = ValueSearch("GYRO_zerocnt");
  uint32_t SamplesCnt = *zerocount;
  msg_t sem_status = RDY_OK;

  /**/
  mavlink_system_struct.state = MAV_STATE_CALIBRATING;

  /* main loop */
  while(SamplesCnt){
    sem_status = chBSemWaitTimeout(&gyro_cal_sem, MS2ST(50));
    if (sem_status == RDY_OK){
      if(is_device_still()){
        raw_data.xgyro_zero_sum += raw_data.xgyro;
        raw_data.ygyro_zero_sum += raw_data.ygyro;
        raw_data.zgyro_zero_sum += raw_data.zgyro;
        SamplesCnt--;
        ProgramBlink(3, MS2ST(20), MS2ST(1));
      }
      else{
        /* clear all collected statistics */
        raw_data.xgyro_zero_sum = 0;
        raw_data.ygyro_zero_sum = 0;
        raw_data.zgyro_zero_sum = 0;
        SamplesCnt = *zerocount;
        device_still_clear();
        ProgramBlink(3, MS2ST(20), MS2ST(100));
      }
    }
    /* sigterm handler */
    if (chThdShouldTerminate())
      goto TERMINATE;
  }

TERMINATE:
  mavlink_system_struct.state = MAV_STATE_STANDBY;
  clearGlobalFlag(GYRO_CAL_FLAG);
  chThdExit(0);
  return 0;
}


/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 * Syncronization functions
 */
void gyro_stat_update(void){
  chBSemSignal(&gyro_cal_sem);
}

/**
 *
 */
Thread* GyroCalStart(void){
  chBSemInit(&gyro_cal_sem,  TRUE);

  Thread *tp = NULL;
  tp = chThdCreateFromHeap(&ThdHeap,
                            sizeof(GyroCalThreadWA),
                            NORMALPRIO,
                            GyroCalThread,
                            NULL);
  if (tp == NULL){
    chDbgPanic("can not allocate memory");
    return NULL;
  }
  else
    return tp;
}
