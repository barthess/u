#include "main.h"
#include "sensors.hpp"
#include "message.hpp"
#include "ground_rover.hpp"
#include "dsp.hpp"
#include "param_registry.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SPEED_TMO           MS2ST(1000)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern chibios_rt::Mailbox speedometer_mb;
extern CompensatedData comp_data;
extern mavlink_vfr_hud_t mavlink_out_vfr_hud_struct;
extern ParamRegistry param_registry;
extern StateVector state_vector;

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
static Median<uint32_t, 3> tacho_filter;
static float const *pulse2m;

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
/**
 * k - m in one pulse (got from params)
 *
 *      S      k
 * v = --- = ------------
 *      t    uS / 1000000
 */
static float calc_ground_rover_speed(uint32_t rtt){

//  uint32_t uS = tacho_filter.update(RTT2US(rtt));
  uint32_t uS = RTT2US(rtt);

  if (uS == 0)/* prevent division by zero */
    return 3;

  float t = ((float)uS / 1000000.0f);
  return *pulse2m / t;
}

/**
 *
 */
static WORKING_AREA(SpeedometerThreadWA, 192);
static msg_t SpeedometerThread(void *arg){
  chRegSetThreadName("Speedometer");
  (void)arg;
  msg_t spd = 0;
  msg_t status = 0;

  while (TRUE) {
    /* get current speed without waiting, because it updates very slowly comparing to other sensors */
    status = speedometer_mb.fetch(&spd, SPEED_TMO);
    if (status == RDY_OK)
      comp_data.groundspeed_odo = calc_ground_rover_speed(spd);
    else
      comp_data.groundspeed_odo = 0; /* device is still */

    /**/
    state_vector.vodo = comp_data.groundspeed_odo;
    mavlink_out_vfr_hud_struct.groundspeed = comp_data.groundspeed_odo;
  }

  return 0;
}


/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

void SpeedometerInit(void){
  pulse2m = (const float*)param_registry.valueSearch("SPD_pulse2m");

  chThdCreateStatic(SpeedometerThreadWA,
          sizeof(SpeedometerThreadWA),
          NORMALPRIO,
          SpeedometerThread,
          NULL);
}


