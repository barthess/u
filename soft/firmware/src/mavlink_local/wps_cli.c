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
static void _wps_print_all_cmd(void){
}

/**
 * Print single waypoint
 */
static void _wps_print_wp(uint16_t seq){
  (void)seq;
}

/**
 * Print single waypoint
 */
static void _wps_cli_set_wp(const char * const * argv){

}

/**
 *
 */
static void _wps_cli_help(void){
  cli_println("Allowable commands in ground rover mode:");
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 * Working with parameters from CLI.
 */
Thread* wps_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  int sscanf_status;
  uint16_t seq = 0;

  /* no arguments */
  if (argc == 0)
    _wps_print_all_cmd();

  /* 1 argument */
  else if (argc == 1){
    sscanf_status = sscanf(argv[0], "%hu", &seq);
    if (sscanf_status != 1){
      cli_println("ERROR: Bad arguments.");
      _wps_cli_help();
    }
    else
      _wps_print_wp(seq);
  }

  /* 2 arguments */
  else if (argc == 2){
    cli_println("ERROR: Bad arguments.");
    _wps_cli_help();
  }

  /* 3 arguments */
  else if (argc == 3){
    _wps_cli_set_wp(argv);
  }

  /* error handler */
  else{
    cli_println("ERROR: too many arguments.");
    _wps_cli_help();
  }

  /* stub */
  return NULL;
}
