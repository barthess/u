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

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
/**
 * Working with parameters from CLI.
 */
Thread* servo_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){

//  (void)cmdarray;
//  int32_t i = -1;
//  param_status_t status;
//
//  /* wait until value uninitialized (just to be safe) */
//  while (OnboardParamCount == 0)
//    chThdSleepMilliseconds(10);
//
//  /* no arguments */
//  if (argc == 0)
//    _param_print_all();
//
//  /* one argument */
//  else if (argc == 1){
//    if (strcmp(*argv, "help") == 0)
//      _param_cli_help();
//    else if (strcmp(*argv, "save") == 0){
//      cli_print("Please wait. Saving to EEPROM... ");
//      save_params_to_eeprom();
//      cli_println("Done.");
//    }
//    else{
//      i = key_index_search(*argv);
//      if (i != -1)
//        _param_cli_print(i);
//      else{
//        cli_println("ERROR: unknown parameter name");
//      }
//    }
//  }
//
//  /* two arguments */
//  else if (argc == 2){
//    i = -1;
//    i = key_index_search(argv[0]);
//    if (i != -1){
//      status = _param_cli_set(argv[1], i);
//      _param_cli_confirm(status);
//    }
//    else{
//      cli_println("ERROR: unknown parameter name");
//    }
//  }
//  else{
//    cli_println("ERROR: bad arguments. Try \"param\" help");
//  }
//
//  /* stub */
  return NULL;
}
