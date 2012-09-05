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
#define _servo_cli_err() (cli_println(\
    "ERROR: command can not be recognised. Try 'servo help'."))

/**
 *
 */
static void _servo_default_cmd(void){
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    cli_println("Atopilot is running in ground rover mode.");
  }
  else{
    cli_println("Atopilot is running in fixed wing mode.");
  }
  cli_println("Try 'servo help' to get list of allowable subcommands.");
}

/**
 *
 */
static void _servo_cli_help(void){
  cli_println("Allowable commands in ground rover mode:");
  cli_println("  servo thrust [0..255]");
  cli_println("    0   : max back");
  cli_println("    128 : neutral");
  cli_println("    255 : max forward");
  cli_println("  servo yaw [0..255]");
  cli_println("    0   : max left");
  cli_println("    128 : neutral");
  cli_println("    255 : max right");

  cli_println("Allowable commands in fixed wing mode:");
  cli_println("  NOT REALISED YET");
}

/**
 *
 */
void _servo_cli_fixed_wing(const char * const * argv){
  (void)argv;
  cli_println("ERROR: setting servos for fixed wing unimplemented yet.");
}

/**
 * @return  -1      in case of error
 *          0..255  value in other case
 */
int32_t _servor_cli_get_value(const char * val){
  int32_t sscanf_status;
  uint32_t v;

  sscanf_status = sscanf(val, "%u", (unsigned int*)&v);
  if (sscanf_status == 1){
    uint32_t tmp = v;
    putinrange(v, 0, 255);
    if (tmp != v)
      cli_println("WARNING: value clamped to 0..255 limits.");
    return v;
  }
  else
    return -1;
}

/**
 *
 */
void _servo_cli_ground_rover(const char * const * argv){
  int32_t v = -1;

  if (strcmp(argv[0], "thrust") == 0){
    v = _servor_cli_get_value(argv[1]);
    if (v == -1)
      _servo_cli_err();
    else
      ServoCarThrustSet(v);
  }
  else if (strcmp(argv[0], "yaw") == 0){
    v = _servor_cli_get_value(argv[1]);
    if (v == -1)
      _servo_cli_err();
    else
      ServoCarYawSet(v);
  }
  else
    _servo_cli_err();
}


/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 * Working with parameters from CLI.
 */
Thread* servo_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;

  /* no arguments */
  if (argc == 0)
    _servo_default_cmd();

  /* one argument */
  else if (argc == 1){
    if (strcmp(*argv, "help") == 0)
      _servo_cli_help();
    else
      cli_println("ERROR: not enough arguments. Try 'servo help'.");
  }

  /* two arguments */
  else if (argc == 2){
    if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER)
      _servo_cli_ground_rover(argv);
    else
      _servo_cli_fixed_wing(argv);
  }

  /* error handler */
  else
    cli_println("ERROR: too many arguments. Try 'servo help'.");

  /* stub */
  return NULL;
}
