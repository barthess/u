#include <stdio.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define DCM_PRINT_PERIOD   MS2ST(200)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern CompensatedData comp_data;
extern float dcmEst[3][3];
extern MemoryHeap ThdHeap;

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
static WORKING_AREA(DcmPrintTreadWA, 1024);
static msg_t DcmPrintTread(void *arg){
  (void)arg;
  chRegSetThreadName("DcmPrint");

  const int n = 74;
  int nres = 0;
  char str[n];
  const char *format = " %-5f %-5f %-5f";

  while (!chThdShouldTerminate()){
    cli_print("\033[2J");    // ESC seq for clear entire screen
    cli_print("\033[H");     // ESC seq for move cursor at left-top corner

    cli_println("DCM:");
    nres = snprintf(str, n, format,
          dcmEst[0][0],
          dcmEst[0][1],
          dcmEst[0][2]);
    cli_print_long(str, n, nres);
    cli_println("");

    nres = snprintf(str, n, format,
          dcmEst[1][0],
          dcmEst[1][1],
          dcmEst[1][2]);
    cli_print_long(str, n, nres);
    cli_println("");

    nres = snprintf(str, n, format,
          dcmEst[2][0],
          dcmEst[2][1],
          dcmEst[2][2]);
    cli_print_long(str, n, nres);
    cli_println("");

    cli_println("Accelration in g [X Y Z]:");
    nres = snprintf(str, n, format,
          (float)comp_data.xacc / 1000.0f,
          (float)comp_data.yacc / 1000.0f,
          (float)comp_data.zacc / 1000.0f);
    cli_print_long(str, n, nres);
    cli_println("");

    chThdSleep(DCM_PRINT_PERIOD);
  }

  chThdExit(0);
  return 0;
}

/**
 *
 */
static void _dcm_cli_help(void){
  cli_println("Just run without parameters.");
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * Working with parameters from CLI.
 */
Thread* dcm_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;

  /* no arguments */
  if (argc == 0){
    return chThdCreateFromHeap(
        &ThdHeap,
        sizeof(DcmPrintTreadWA),
        NORMALPRIO,
        DcmPrintTread,
        NULL);
  }
  else
    _dcm_cli_help();

  return NULL;
}

