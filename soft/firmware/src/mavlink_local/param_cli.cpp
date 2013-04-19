#include <stdio.h>

#include "uav.h"
#include "global_flags.h"
#include "cli.hpp"
#include "message.hpp"
#include "param_cli.hpp"
#include "param_registry.hpp"

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
extern ParamRegistry param_registry;
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
  const GlobalParam_t *p;
  p = param_registry.getParam(NULL, i, NULL);

  nres = snprintf(str, n, "%-15s", p->name);
  cli_print_long(str, n, nres);

  switch(p->param_type){
  case MAVLINK_TYPE_FLOAT:
    nres = snprintf(str, n, " %-15f %-15f %-15f",
        (double)p->min.f32,
        (double)p->valuep->f32,
        (double)p->max.f32);
    break;
  case MAVLINK_TYPE_INT32_T:
    nres = snprintf(str, n, " %-15d %-15d %-15d",
        (int)p->min.i32,
        (int)p->valuep->i32,
        (int)p->max.i32);
    break;
  default: // uint32_t
    nres = snprintf(str, n, " %-15u %-15u %-15u",
        (unsigned int)p->min.u32,
        (unsigned int)p->valuep->u32,
        (unsigned int)p->max.u32);
    break;
  }

  cli_print_long(str, n, nres);
  cli_print(ENDL);

  if (need_help && (p->help != NULL)){
    cli_println("");
    cli_println(p->help);
  }
}

/**
 *
 */
static void _param_cli_print_header(void){
  cli_println("Name            min             value           max");
  cli_println("--------------------------------------------------------------");
}

/**
 *
 */
static void _param_print_all(void){
  int32_t i = 0;

  _param_cli_print_header();

  for (i = 0; i < param_registry.paramCount(); i++)
    _param_cli_print(i, FALSE);
}

/**
 *
 */
static param_status_t _param_cli_set(const char * val, uint32_t i){
  floatint v;
  int sscanf_status;
  const GlobalParam_t *p;
  p = param_registry.getParam(NULL, i, NULL);

  switch(p->param_type){
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
  else{
    return param_registry.setParam(&v, p);
  }
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
Thread* param_clicmd(int argc, const char * const * argv, SerialDriver *sdp){
  (void)sdp;

  int32_t i = -1;
  param_status_t status;

  /* wait until value uninitialized (just to be safe) */
  while (GlobalFlags.parameters_got != 1)
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
      param_registry.saveAll();
      cli_println("Done.");
    }
    else{
      i = -1;
      param_registry.getParam(*argv, 0, &i);
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
    param_registry.getParam(argv[0], 0, &i);
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

