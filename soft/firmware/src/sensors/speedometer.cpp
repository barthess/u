#include "main.h"
#include "sensors.hpp"
#include "message.hpp"
#include "ground_rover.hpp"

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

    /* set variable for telemetry */
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
  chThdCreateStatic(SpeedometerThreadWA,
          sizeof(SpeedometerThreadWA),
          NORMALPRIO,
          SpeedometerThread,
          NULL);
}
