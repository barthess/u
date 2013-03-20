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
static GyroCalContext ctx;

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
 * Fast blinking -- device is not still
 * Light without blinking -- collecting statistics
 *
 * Return FALSE if nothing to do, otherwise - TRUE
 */
bool_t GyroZeroUpdate(int32_t *data){

  switch(ctx.gyrocalstate){

  /* wait for "gyro_cal" flag */
  case GYROCAL_READY:
    if (GlobalFlags.gyro_cal != 1)
      return GYRO_STAT_UNCHANGED;
    else
      ctx.gyrocalstate = GYROCAL_WAIT_FOR_STILL;
    break;


  /* wait for stillness and clear statistics every non still cycle */
  case GYROCAL_WAIT_FOR_STILL:
    mavlink_system_struct.state = MAV_STATE_CALIBRATING;

    /* clear all collected statistics */
    ctx.ZeroSum[0] = 0;
    ctx.ZeroSum[1] = 0;
    ctx.ZeroSum[2] = 0;
    *ctx.x_offset = 0;
    *ctx.y_offset = 0;
    *ctx.z_offset = 0;
    ctx.SamplesCnt = *ctx.zerocount;

    DeviceStillSet();
    SheduleRedBlink(3, MS2ST(20), MS2ST(100));

    ctx.gyrocalstate = GYROCAL_COLLECTING;
    break;

  /* collecting samples in sums */
  case GYROCAL_COLLECTING:
    if(IsDeviceStill()){
      ctx.ZeroSum[0] += data[0];
      ctx.ZeroSum[1] += data[1];
      ctx.ZeroSum[2] += data[2];
      ctx.SamplesCnt--;

      *ctx.x_offset = (float)ctx.ZeroSum[0] / (float)(*ctx.zerocount - ctx.SamplesCnt);
      *ctx.y_offset = (float)ctx.ZeroSum[1] / (float)(*ctx.zerocount - ctx.SamplesCnt);
      *ctx.z_offset = (float)ctx.ZeroSum[2] / (float)(*ctx.zerocount - ctx.SamplesCnt);

      SheduleRedBlink(3, MS2ST(20), MS2ST(1));
    }
    else{
      ctx.gyrocalstate = GYROCAL_WAIT_FOR_STILL;
      break;
    }

    if (ctx.SamplesCnt == 0){  /* Collecting done. */
      clearGlobalFlag(GlobalFlags.gyro_cal);
      chSysLock();

      comp_data.xgyro_angle = 0;
      comp_data.ygyro_angle = 0;
      comp_data.zgyro_angle = 0;
      chSysUnlock();

      /* store in EEPROM for fast boot */
      save_param_to_eeprom("GYRO_x_offset");
      save_param_to_eeprom("GYRO_y_offset");
      save_param_to_eeprom("GYRO_z_offset");
      /* just to be safe. Because it can be changed manually from QGC */
      save_param_to_eeprom("GYRO_zerocnt");

      mavlink_system_struct.state = MAV_STATE_STANDBY;
      ctx.gyrocalstate = GYROCAL_READY;
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
  ctx.gyrocalstate = GYROCAL_UNINIT;

  ctx.ZeroSum[0] = 0;
  ctx.ZeroSum[1] = 0;
  ctx.ZeroSum[2] = 0;

  ctx.zerocount  = ValueSearch("GYRO_zerocnt");
  ctx.x_offset   = ValueSearch("GYRO_x_offset");
  ctx.y_offset   = ValueSearch("GYRO_y_offset");
  ctx.z_offset   = ValueSearch("GYRO_z_offset");

  ctx.gyrocalstate = GYROCAL_READY;
}



