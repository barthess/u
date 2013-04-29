#include <math.h>

#include "main.h"
#include "global_flags.h"
#include "mag_cal.hpp"
#include "message.hpp"
#include "mavdbg.hpp"
#include "sensors.hpp"
#include "imu.hpp"
#include "sanity.hpp"
#include "param_registry.hpp"
#include "sphere.hpp"
#include "misc_math.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

#define NEW_POSITION_THRESHOLD  175
#define NEW_POSITION_TMO_SEC    60

/**
 * @brief   State machine possible states.
 */
typedef enum {
  MAGCAL_UNINIT = 0,            /**< Not initialized.           */
  MAGCAL_COLLECTING = 1,        /**< Collecting statistic.      */
  MAGCAL_READY = 2,             /**< Statistic collected. Ready for new run.     */
  MAGCAL_WAIT_NEW_POS = 3,      /**< Wait for new position .                     */
} magcalstate_t;

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern ParamRegistry param_registry;

extern mavlink_system_t mavlink_system_struct;

/* how many ticks needed for calculate sphere */
volatile uint32_t sphere_time;

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

static magcalstate_t magcalstate = MAGCAL_UNINIT;

static int32_t const *zerocount;
static int32_t MagSum[3];
static int32_t SamplesCnt;

/* empty sphere to store results */
static Sphere S = {{0,0,0}, 0};

/* collected points of sphere */
static int32_t P[4][3]={{0, 0, 0},
                        {0, 0, 0},
                        {0, 0, 0},
                        {0, 0, 0}};

/* current collecting point */
static uint32_t CurrentPoint;

/* deadline for waiting new position */
static systime_t position_deadline;

/* for measuring of sphere calculation time */
static TimeMeasurement sphere_tmup;

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
static void __clear_state(void){
  SamplesCnt = *zerocount;
  MagSum[0] = 0;
  MagSum[1] = 0;
  MagSum[2] = 0;
}

/**
 * Return TRUE when full point statistic collected
 */
static bool_t __update_point(int32_t *data){
  if(IsDeviceStill()){
    MagSum[0] += data[0];
    MagSum[1] += data[1];
    MagSum[2] += data[2];
    SamplesCnt--;
  }
  else
    __clear_state();

  if (SamplesCnt == 0)
    return TRUE;
  else
    return FALSE;
}

/**
 * Return TRUE if device was turned to new position
 */
static bool_t __is_new_position(int32_t *data){
  uint32_t delta = 0;
  uint32_t i = CurrentPoint - 1;

  for (uint32_t n = 0; n < 3; n++)
    delta += (P[i][n] - data[n]) * (P[i][n] - data[n]);

  delta = sqrti(delta);

  if (delta > NEW_POSITION_THRESHOLD)
    return TRUE;
  else
    return FALSE;
}


/**
 * Syncronization functions for statistics update.
 */
bool_t mag_stat_update(int32_t *data){
  bool_t point_status = FALSE;

  switch(magcalstate){
  /* wait for "mag_cal" flag */
  case MAGCAL_READY:
    if (GlobalFlags.mag_cal != 1)
      return MAG_STAT_UNCHANGED;
    else{
      mavlink_system_struct.state = MAV_STATE_CALIBRATING;
      mavlink_dbg_print(MAV_SEVERITY_INFO, "MAG: start calibration");
      CurrentPoint = 0;
      __clear_state();
      magcalstate = MAGCAL_COLLECTING;
    }
    break;


  /* collecting samples in sums */
  case MAGCAL_COLLECTING:
    point_status = __update_point(data);
    if (point_status == TRUE){
      position_deadline = chTimeNow() + S2ST(NEW_POSITION_TMO_SEC);
      P[CurrentPoint][0] = MagSum[0] / *zerocount;
      P[CurrentPoint][1] = MagSum[1] / *zerocount;
      P[CurrentPoint][2] = MagSum[2] / *zerocount;
      CurrentPoint++;

      if (CurrentPoint == 4){
        tmStartMeasurement(&sphere_tmup);
        SolveSphere(&S, P);
        tmStopMeasurement(&sphere_tmup);
        sphere_time = sphere_tmup.last;

        *(int32_t *)(param_registry.valueSearch("MAG_xoffset"))   = roundf(S.c[0]);
        *(int32_t *)(param_registry.valueSearch("MAG_yoffset"))   = roundf(S.c[1]);
        *(int32_t *)(param_registry.valueSearch("MAG_zoffset"))   = roundf(S.c[2]);
        *(int32_t *)(param_registry.valueSearch("MAG_vectorlen")) = roundf(S.r);

        mavlink_dbg_print(MAV_SEVERITY_INFO, "MAG: calibration finished");
        mavlink_system_struct.state = MAV_STATE_STANDBY;
        clearGlobalFlag(GlobalFlags.mag_cal);
        magcalstate = MAGCAL_READY;
      }
      else{
        mavlink_dbg_print(MAV_SEVERITY_NOTICE, "MAG: waiting for new position");
        magcalstate = MAGCAL_WAIT_NEW_POS;
      }
    }
    break;


  /* wait until device be turned in position */
  case MAGCAL_WAIT_NEW_POS:
    point_status = __is_new_position(data);
    if (point_status == TRUE){
      mavlink_dbg_print(MAV_SEVERITY_NOTICE, "MAG: new position is OK");
      magcalstate = MAGCAL_COLLECTING;          /* collect next point */
    }
    else if (chTimeNow() > position_deadline){  /* device have not been turned in new position */
      mavlink_dbg_print(MAV_SEVERITY_WARNING,
      "MAG: no new position. Calibration interrupted");
      clearGlobalFlag(GlobalFlags.mag_cal);
      magcalstate = MAGCAL_READY;
    }
    __clear_state();
    break;


  /* error traps */
  case MAGCAL_UNINIT:
    chDbgPanic("Gyro calibrator uninitialized");
    break;
  default:
    chDbgPanic("Wrong case");
    break;
  }

  return MAG_STAT_UPDATED;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void MagCalInit(void){
  magcalstate = MAGCAL_UNINIT;

  zerocount = (const int32_t*)param_registry.valueSearch("MAG_zerocnt");

  tmObjectInit(&sphere_tmup);

  magcalstate = MAGCAL_READY;
}


/* test matrix */
//  int32_t P[4][3]={{2572, -2819, -1864},
//                   {2393, -2990, -1864},
//                   {2320, -2701, -1867},
//                   {2423, -2800, -1907}};
