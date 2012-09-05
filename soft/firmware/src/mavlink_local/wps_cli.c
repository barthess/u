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
extern mavlink_system_t       mavlink_system_struct;

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
#define _wps_cli_err() (cli_println(\
    "ERROR: command can not be recognised. Try 'wps help'."))

/**
 *
 */
static void _wps_print_all_cmd(void){
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    cli_println("Atopilot is running in ground rover mode.");
  }
  else{
    cli_println("Atopilot is running in fixed wing mode.");
  }
  cli_println("Try 'controller help' to get list of allowable subcommands.");
}

/**
 *
 */
static void _wps_cli_help(void){
  cli_println("Allowable commands in ground rover mode:");

  cli_println("Allowable commands in fixed wing mode:");
  cli_println("  NOT REALISED YET");
}

/**
 *
 */
void _controller_cli_fixed_wing(const char * const * argv){
  (void)argv;
  cli_println("ERROR: setting servos for fixed wing unimplemented yet.");
}

/**
 *
 */
void _wps_cli_ground_rover(const char * const * argv){

  if (strcmp(argv[0], "speed") == 0)
    _controller_cli_get_speed(argv[1]);



  else if (strcmp(argv[0], "heading") == 0)
    _controller_cli_get_heading(argv[1]);
  else if (strcmp(argv[0], "trip") == 0){
    _wps_cli_get_trip(argv[1]);
    //chMBPost(&testpoint_mb, (msg_t)&test_point, TIME_IMMEDIATE);
  }
  else if (strcmp(argv[0], "stop") == 0)
    ;//chMBPost(&testpoint_mb, (msg_t)NULL, TIME_IMMEDIATE);
  else
    _wps_cli_err();
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

  /* no arguments */
  if (argc == 0)
    _wps_print_all_cmd();

  /* one argument */
  else if (argc == 1){
    if (strcmp(*argv, "help") == 0)
      _wps_cli_help();
    else
      cli_println("ERROR: not enough arguments. Try 'controller help'.");
  }

  /* two arguments */
  else if (argc == 2){
    if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER)
      _wps_cli_ground_rover(argv);
    else
      _controller_cli_fixed_wing(argv);
  }

  /* error handler */
  else
    cli_println("ERROR: too many arguments. Try 'servo help'.");

  /* stub */
  return NULL;
}
