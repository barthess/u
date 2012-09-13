#include <stdio.h>

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
extern uint32_t GlobalFlags;

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
  setGlobalFlag(GYRO_CAL_FLAG);
}

/**
 *
 */
static void _cal_cli_mag(void){
  setGlobalFlag(MAG_CAL_FLAG);
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 *
 */
Thread* cal_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;

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
