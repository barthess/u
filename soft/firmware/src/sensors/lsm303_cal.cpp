#include "main.h"
#include "message.hpp"
#include "sensors.hpp"
#include "lsm303_cal.hpp"
#include "param_registry.hpp"
#include "mavdbg.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define STILL_MSK           (STILL_GYRO_MSK | STILL_ACC_MSK)

/* how much time wait until next calibration trigger called */
#define WAIT_NEXT_TIMEOUT   MS2ST(60000)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern mavlink_system_t     mavlink_system_struct;
extern ParamRegistry        param_registry;
extern chibios_rt::Mailbox  red_blink_mb;

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
static const int16_t fastblink[] = {20, -100, 20, -100, 20, -100, 0};
static const int16_t slowblink[] = {500, -500, 0};

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * Updates calibration data.
 */
void LSM303calibrator::update(const float *data, uint32_t still_msk){
  switch(state){
  case LSM303_CAL_SLEEP:
    /* nothing to do */
    return;
    break;

  case LSM303_CAL_WAIT_NEXT:
    if ((chTimeNow() - last_point_timestamp) < WAIT_NEXT_TIMEOUT){
      red_blink_mb.post((msg_t)slowblink, TIME_IMMEDIATE);
      return;
    }
    else{
      /* time is out */
      chSysLock();
      sample = 0;
      point = 0;
      state = LSM303_CAL_SLEEP;
      chSysUnlock();
      mavlink_dbg_print(MAV_SEVERITY_INFO, "MAG: wait next point time out");
      mavlink_system_struct.state = MAV_STATE_STANDBY;
    }
    break;

  case LSM303_CAL_COLLECTING:
    collecting(data, still_msk);
    break;

  default:
    chDbgPanic("unhandled case");
    break;
  }
}

/**
 *
 */
void LSM303calibrator::collecting(const float *data, uint32_t still_msk){
  uint32_t i;

  /* check immobility */
  if (! ((still_msk & STILL_MSK) == STILL_MSK)){
    sample = 0;
    red_blink_mb.post((msg_t)fastblink, TIME_IMMEDIATE);
    return;
  }

  /* */
  if (0 == sample){
    /* start from clear states */
    for(i=0; i<3; i++)
      abeta[i].reset(data[i], *zeroflen);
    sample++;
  }
  else{
    if (*zerocnt > sample){
      for(i=0; i<3; i++)
        abeta[i].update(data[i], *zeroflen);
      sample++;
    }
    else{
      /* statistics for single point successfully collected */
      for(uint32_t i=0; i<3; i++)
        P[point][i] = abeta[i].get(*zeroflen);
      point++;
      sample = 0;

      if (4 == point){
        /* we have enough points to calculate compensation sphere */
        SolveSphere(&S, P);
        point = 0;

        /* save data to registry and syng to eeprom */
        *(float *)(param_registry.valueSearch("MAG_xoffset"))   = S.c[0];
        *(float *)(param_registry.valueSearch("MAG_yoffset"))   = S.c[1];
        *(float *)(param_registry.valueSearch("MAG_zoffset"))   = S.c[2];
        *(float *)(param_registry.valueSearch("MAG_vectorlen")) = S.r;
        param_registry.syncParam("MAG_xoffset");
        param_registry.syncParam("MAG_yoffset");
        param_registry.syncParam("MAG_zoffset");
        param_registry.syncParam("MAG_vectorlen");

        /* final stuff */
        mavlink_dbg_print(MAV_SEVERITY_INFO, "MAG: calibration finished");
        mavlink_system_struct.state = MAV_STATE_STANDBY;
        state = LSM303_CAL_SLEEP;
      }
      else{
        mavlink_dbg_print(MAV_SEVERITY_NOTICE, "MAG: waiting for new position");
        last_point_timestamp = chTimeNow();
        state = LSM303_CAL_WAIT_NEXT;
      }
    }
  }
}

/**
 *
 */
bool LSM303calibrator::trig(void){
  switch(state){
  case LSM303_CAL_SLEEP:

    chSysLock();
    last_point_timestamp = chTimeNow();
    sample = 0;
    point = 0;
    state = LSM303_CAL_COLLECTING;
    chSysUnlock();

    mavlink_dbg_print(MAV_SEVERITY_INFO, "MAG: calibration started");
    chThdSleep(1);
    mavlink_system_struct.state = MAV_STATE_CALIBRATING;
    return CH_SUCCESS;
    break;

  case LSM303_CAL_WAIT_NEXT:
    mavlink_dbg_print(MAV_SEVERITY_NOTICE, "MAG: new position reached");
    state = LSM303_CAL_COLLECTING;
    return CH_SUCCESS;
    break;

  default:
    return CH_FAILED;
    break;
  }
}

/**
 *
 */
void LSM303calibrator::abort(void){
  chDbgCheck((LSM303_CAL_UNINIT != state), "unitialized yet");

  if (LSM303_CAL_SLEEP == state){ /* nothing to do */
    return;
  }
  else{
    chSysLock();
    state = LSM303_CAL_SLEEP;
    sample = 0;
    point = 0;
    chSysUnlock();
    mavlink_system_struct.state = MAV_STATE_STANDBY;
  }
}

/**
 *
 */
void LSM303calibrator::start(void){
  zerocnt   = (const int32_t*)param_registry.valueSearch("MAG_zerocnt");
  zeroflen  = (const int32_t*)param_registry.valueSearch("MAG_zeroflen");

  state = LSM303_CAL_SLEEP;
}

/**
 *
 */
LSM303calibrator::LSM303calibrator(void){
  state = LSM303_CAL_UNINIT;
}

/**
 *
 */
bool LSM303calibrator::isCalibrating(void) {
  if ((LSM303_CAL_COLLECTING == state) || (LSM303_CAL_WAIT_NEXT == state))
    return true;
  else
    return false;
}


