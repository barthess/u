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
extern GlobalParam_t GlobalParam[];
extern uint32_t OnboardParamCount;

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
 * confirmation of changes
 */
static void _param_cli_confirm(param_status_t status){
  if (status == PARAM_OK)
    return;
    //cli_println("Success");
  else if (status == PARAM_CLAMPED)
    cli_println("WARNING: value clamped to safety limits.");
  else if (status == PARAM_NOT_CHANGED)
    cli_println("WARNING: value not changed.");
  else if (status == PARAM_INCONSISTENT)
    cli_println("ERROR: value inconsistent.");
  else
    cli_println("ERROR: Unhandled error.");
}

/**
 *
 */
static void _param_cli_print(uint32_t i, bool_t need_help){

  int n = 80;
  int nres = 0;
  char str[n];

  nres = snprintf(str, n, "%-15s", GlobalParam[i].name);
  cli_print_long(str, n, nres);

  switch(GlobalParam[i].param_type){
  case MAVLINK_TYPE_FLOAT:
    nres = snprintf(str, n, " %-15f %-15f %-15f",
        GlobalParam[i].min.f32,
        GlobalParam[i].valuep->f32,
        GlobalParam[i].max.f32);
    break;
  case MAVLINK_TYPE_INT32_T:
    nres = snprintf(str, n, " %-15d %-15d %-15d",
        (int)GlobalParam[i].min.i32,
        (int)GlobalParam[i].valuep->i32,
        (int)GlobalParam[i].max.i32);
    break;
  default: // uint32_t
    nres = snprintf(str, n, " %-15u %-15u %-15u",
        (unsigned int)GlobalParam[i].min.u32,
        (unsigned int)GlobalParam[i].valuep->u32,
        (unsigned int)GlobalParam[i].max.u32);
    break;
  }

  cli_print_long(str, n, nres);
  cli_print(ENDL);

  if (need_help && (GlobalParam[i].help != NULL)){
    cli_println("");
    cli_println(GlobalParam[i].help);
  }
}

/**
 *
 */
void _param_cli_print_header(void){
  cli_println("Name            min             value           max");
  cli_println("--------------------------------------------------------------");
}

/**
 *
 */
static void _param_print_all(void){
  uint32_t i = 0;

  _param_cli_print_header();

  for (i = 0; i < OnboardParamCount; i++)
    _param_cli_print(i, FALSE);
}

/**
 *
 */
static param_status_t _param_cli_set(const char * val, uint32_t i){
  floatint v;
  int sscanf_status;

  switch(GlobalParam[i].param_type){
  case MAVLINK_TYPE_FLOAT:
    sscanf_status = sscanf(val, "%f", &v.f32);
    break;

  case MAVLINK_TYPE_INT32_T:
    sscanf_status = sscanf(val, "%i", (int*)&v.i32);
    break;

  default: // uint32_t
    sscanf_status = sscanf(val, "%u", (unsigned int*)&v.u32);
    break;
  }

  if (sscanf_status != 1)
    return PARAM_INCONSISTENT;
  else
    return set_global_param(&v, &GlobalParam[i]);
}

/**
 *
 */
static void _param_cli_help(void){
  cli_println("Run without parameters to get full parameters list.");
  cli_println("'param save' to save parameters to EEPROM.");
  cli_println("'param help' to get this message.");
  cli_println("'param PARAM_name' to get value of parameter.");
  cli_println("'param PARAM_name N' to set value of parameter to N.");
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * Working with parameters from CLI.
 */
Thread* param_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){

  (void)cmdarray;
  int32_t i = -1;
  param_status_t status;

  /* wait until value uninitialized (just to be safe) */
  while (OnboardParamCount == 0)
    chThdSleepMilliseconds(10);

  /* no arguments */
  if (argc == 0)
    _param_print_all();

  /* one argument */
  else if (argc == 1){
    if (strcmp(*argv, "help") == 0)
      _param_cli_help();
    else if (strcmp(*argv, "save") == 0){
      cli_print("Please wait. Saving to EEPROM... ");
      save_params_to_eeprom();
      cli_println("Done.");
    }
    else{
      i = key_index_search(*argv);
      if (i != -1){
        _param_cli_print_header();
        _param_cli_print(i, TRUE);
      }
      else{
        cli_println("ERROR: unknown parameter name.");
      }
    }
  }

  /* two arguments */
  else if (argc == 2){
    i = -1;
    i = key_index_search(argv[0]);
    if (i != -1){
      status = _param_cli_set(argv[1], i);
      _param_cli_confirm(status);
    }
    else{
      cli_println("ERROR: unknown parameter name.");
    }
  }
  else{
    cli_println("ERROR: bad arguments. Try 'param help'.");
  }

  /* stub */
  return NULL;
}

