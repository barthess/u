#include "main.h"
#include "message.hpp"
#include "sensors.hpp"
#include "itg3200_cal.hpp"
#include "param_registry.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define STILL_MSK   (STILL_MAG_MSK | STILL_ACC_MSK)

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
static const int16_t fastblink[7] = {20, -100, 20, -100, 20, -100, 0};

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
void ITG3200calibrator::reset_stats(void){
  sample = 0;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * Updates calibration data.
 */
void ITG3200calibrator::update(const int32_t *raw, uint32_t still_msk){
  uint32_t i;

  /* check current system state */
  if (SLEEP == state)
    return;

  /* check immobility */
  if (! ((still_msk & STILL_MSK) == STILL_MSK)){
    this->reset_stats();
    red_blink_mb.post((msg_t)fastblink, TIME_IMMEDIATE);
    return;
  }

  /* looks like all ready */
  if (0 == sample){
    state = COLLECTING;
    for(i=0; i<3; i++)
      abeta[i].reset((float)raw[i], *zeroflen);
    sample++;
  }
  else{
    if (*zerocnt > sample){
      for(i=0; i<3; i++)
        abeta[i].update((float)raw[i], *zeroflen);
      sample++;
    }
    else{
      /* statistics successfully collected */
      *x_offset = abeta[0].get(*zeroflen);
      *y_offset = abeta[1].get(*zeroflen);
      *z_offset = abeta[2].get(*zeroflen);

      /* store in EEPROM for fast boot */
      param_registry.syncParam("GYRO_x_offset");
      param_registry.syncParam("GYRO_y_offset");
      param_registry.syncParam("GYRO_z_offset");

      /* final stuff */
      mavlink_system_struct.state = MAV_STATE_STANDBY;
      state = SLEEP;
    }
  }
}

/**
 *
 */
void ITG3200calibrator::trig(void){
  chDbgCheck((SLEEP == state), "inconsistent state");
  this->reset_stats();
  state = COLLECTING;
  mavlink_system_struct.state = MAV_STATE_CALIBRATING;
}

/**
 *
 */
void ITG3200calibrator::abort(void){
  chDbgCheck((UNINIT != state), "unitialized yet");

  if (SLEEP == state){ /* nothing to do */
    return;
  }
  else{
    chSysLock();
    state = SLEEP;
    this->reset_stats();
    chSysUnlock();
    mavlink_system_struct.state = MAV_STATE_STANDBY;
  }
}

/**
 *
 */
void ITG3200calibrator::start(void){
  x_offset  = (float*)param_registry.valueSearch("GYRO_x_offset");
  y_offset  = (float*)param_registry.valueSearch("GYRO_y_offset");
  z_offset  = (float*)param_registry.valueSearch("GYRO_z_offset");

  zerocnt   = (const int32_t*)param_registry.valueSearch("GYRO_zerocnt");
  zeroflen  = (const int32_t*)param_registry.valueSearch("GYRO_zeroflen");

  state = SLEEP;
}

/**
 *
 */
ITG3200calibrator::ITG3200calibrator(void){
  state = UNINIT;
}

/**
 *
 */
bool ITG3200calibrator::isCalibrating(void) {
  if (COLLECTING == state)
    return true;
  else
    return false;
}


