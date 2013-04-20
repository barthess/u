#include <string.h>

#include "uav.h"
#include "global_flags.h"
#include "cli.hpp"

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

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * PROTOTYPES
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
static void _cal_cli_help(void){
  cli_println("'cal gyro' to start gyroscope calibration");
  cli_println("'cal mag'  to start magnetometer calibration");
}

/**
 *
 */
static void  _cal_cli_gyro(void){
  setGlobalFlag(GlobalFlags.gyro_cal);
}

/**
 *
 */
static void _cal_cli_mag(void){
  setGlobalFlag(GlobalFlags.mag_cal);
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 *
 */
Thread* cal_clicmd(int argc, const char * const * argv, SerialDriver *sdp){
  (void)sdp;

  /* no arguments */
  if (argc == 0)
    _cal_cli_help();

  /* 1 argument */
  else if (argc == 1){
    if (strcmp(*argv, "gyro") == 0)
      _cal_cli_gyro();
    else if (strcmp(*argv, "mag") == 0)
      _cal_cli_mag();
    else
      _cal_cli_help();
  }

  /* error handler */
  else{
    cli_println("ERROR: wrong arguments.");
    _cal_cli_help();
  }

  /* stub */
  return NULL;
}
