#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/**
 * @brief   State machine possible states.
 */
typedef enum {
  GYROCAL_UNINIT = 0,         /**< Not initialized.           */
  GYROCAL_WAIT_FOR_STILL = 1, /**< Wait device stillness.                     */
  GYROCAL_COLLECTING = 2,     /**< Collecting statistic.      */
  GYROCAL_READY = 3,          /**< Statistic collected. Ready for new run.     */
} gyrocalstate_t;

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern CompensatedData comp_data;
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

static gyrocalstate_t gyrocalstate;

static int32_t  *x_zerosum, *y_zerosum, *z_zerosum;
static int32_t const *zerocount;

/* how many points remains to collect for full statistic */
static uint32_t SamplesCnt;

/* collecte sums for zero offset correction */
static int32_t ZeroSum[3];

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/**
 * For initilize calibration you must set global flag "gyro_cal"
 *
 * Blinking -- device is not still
 * Light without blinking -- collecting statistics
 *
 * Return FALSE if nothing to do, otherwise - TRUE
 */
bool_t gyro_stat_update(int32_t *data){

  switch(gyrocalstate){

  /* wait for "gyro_cal" flag */
  case GYROCAL_READY:
    if (GlobalFlags.gyro_cal != 1)
      return GYRO_STAT_UNCHANGED;
    else
      gyrocalstate = GYROCAL_WAIT_FOR_STILL;
    break;


  /* wait for stillness and clear statistics every non still cycle */
  case GYROCAL_WAIT_FOR_STILL:
    mavlink_system_struct.state = MAV_STATE_CALIBRATING;

    /* clear all collected statistics */
    ZeroSum[0] = 0;
    ZeroSum[1] = 0;
    ZeroSum[2] = 0;
    SamplesCnt = *zerocount;

    DeviceStillSet();
    SheduleRedBlink(3, MS2ST(20), MS2ST(100));

    gyrocalstate = GYROCAL_COLLECTING;
    break;

  /* collecting samples in sums */
  case GYROCAL_COLLECTING:
    if(IsDeviceStill()){
      ZeroSum[0] += data[0];
      ZeroSum[1] += data[1];
      ZeroSum[2] += data[2];
      SamplesCnt--;
      SheduleRedBlink(3, MS2ST(20), MS2ST(1));
    }
    else{
      gyrocalstate = GYROCAL_WAIT_FOR_STILL;
      break;
    }

    if (SamplesCnt == 0){  /* Collecting done. */
      clearGlobalFlag(GlobalFlags.gyro_cal);
      chSysLock();
      *x_zerosum = ZeroSum[0];
      *y_zerosum = ZeroSum[1];
      *z_zerosum = ZeroSum[2];
      comp_data.xgyro_angle = 0;
      comp_data.ygyro_angle = 0;
      comp_data.zgyro_angle = 0;
      chSysUnlock();

      /* store in EEPROM for fast boot */
      save_param_to_eeprom("GYRO_x_zerosum");
      save_param_to_eeprom("GYRO_y_zerosum");
      save_param_to_eeprom("GYRO_z_zerosum");
      /* just to be safe. Because it can be changed manually from QGC */
      save_param_to_eeprom("GYRO_zerocnt");

      mavlink_system_struct.state = MAV_STATE_STANDBY;
      gyrocalstate = GYROCAL_READY;
    }
    break;

  /* error traps */
  case GYROCAL_UNINIT:
    chDbgPanic("Gyro calibrator uninitialized");
    break;
  default:
    chDbgPanic("Wrong case");
    break;
  }

  return GYRO_STAT_UPDATED;
}


/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void GyroCalInit(void){
  gyrocalstate = GYROCAL_UNINIT;

  ZeroSum[0] = 0;
  ZeroSum[1] = 0;
  ZeroSum[2] = 0;
  zerocount = ValueSearch("GYRO_zerocnt");
  x_zerosum = ValueSearch("GYRO_x_zerosum");
  y_zerosum = ValueSearch("GYRO_y_zerosum");
  z_zerosum = ValueSearch("GYRO_z_zerosum");

  gyrocalstate = GYROCAL_READY;
}



