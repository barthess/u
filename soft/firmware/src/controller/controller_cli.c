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
extern Mailbox testpoint_mb;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static test_point_t test_point = {0,0,0};

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
#define _controller_cli_err() (cli_println(\
    "ERROR: command can not be recognised. Try 'controller help'."))

/**
 *
 */
static void _controller_default_cmd(void){
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
static void _controller_cli_help(void){
  cli_println("Allowable commands in ground rover mode:");
  cli_println("  controller speed [0.0 .. 10.0]");
  cli_println("    set desired speed in m/s and stay _still_");
  cli_println("    usable values 0.7 .. 3.0");
  cli_println("  controller heading [0..359]");
  cli_println("    rover heading in degrees");
  cli_println("  controller trip [0..100]");
  cli_println("    path length in m. It will be run at previously set speed and heading");
  cli_println("  controller stop");
  cli_println("    cansel current point and stop");

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
void _controller_cli_get_speed(const char * val){
  int32_t sscanf_status;

  sscanf_status = sscanf(val, "%f", &test_point.speed);
  if (sscanf_status == 1){
    float tmp = test_point.speed;
    putinrange(test_point.speed, 0, 10);
    if (tmp != test_point.speed)
      cli_println("WARNING: value clamped to 0..10 limits.");
  }
  else{
    test_point.speed = 0;
    _controller_cli_err();
  }
}

/**
 *
 */
void _controller_cli_get_heading(const char * val){
  int32_t sscanf_status;

  sscanf_status = sscanf(val, "%u", (unsigned int*)&test_point.heading);
  if (sscanf_status == 1){
    uint32_t tmp = test_point.heading;
    putinrange(test_point.heading, 0, 359);
    if (tmp != test_point.heading)
      cli_println("WARNING: value clamped to 0..359 limits.");
  }
  else{
    test_point.heading = 0;
    _controller_cli_err();
  }
}

/**
 *
 */
void _controller_cli_get_trip(const char * val){
  int32_t sscanf_status;

  sscanf_status = sscanf(val, "%u", (unsigned int*)&test_point.trip);
  if (sscanf_status == 1){
    uint32_t tmp = test_point.trip;
    putinrange(test_point.trip, 0, 100);
    if (tmp != test_point.trip)
      cli_println("WARNING: value clamped to 0..100 limits.");
  }
  else{
    test_point.trip = 0;
    _controller_cli_err();
  }
}

/**
 *
 */
void _controller_cli_ground_rover(const char * const * argv){

  if (strcmp(argv[0], "speed") == 0)
    _controller_cli_get_speed(argv[1]);
  else if (strcmp(argv[0], "heading") == 0)
    _controller_cli_get_heading(argv[1]);
  else if (strcmp(argv[0], "trip") == 0){
    _controller_cli_get_trip(argv[1]);
    chMBPost(&testpoint_mb, (msg_t)&test_point, TIME_IMMEDIATE);
  }
  else if (strcmp(argv[0], "stop") == 0)
    chMBPost(&testpoint_mb, (msg_t)NULL, TIME_IMMEDIATE);
  else
    _controller_cli_err();
}


/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 * Working with parameters from CLI.
 */
Thread* controller_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;

  /* no arguments */
  if (argc == 0)
    _controller_default_cmd();

  /* one argument */
  else if (argc == 1){
    if (strcmp(*argv, "help") == 0)
      _controller_cli_help();
    else
      cli_println("ERROR: not enough arguments. Try 'controller help'.");
  }

  /* two arguments */
  else if (argc == 2){
    if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER)
      _controller_cli_ground_rover(argv);
    else
      _controller_cli_fixed_wing(argv);
  }

  /* error handler */
  else
    cli_println("ERROR: too many arguments. Try 'servo help'.");

  /* stub */
  return NULL;
}
