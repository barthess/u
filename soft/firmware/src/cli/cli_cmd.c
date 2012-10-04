#include <string.h>
#include <stdlib.h>
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
extern MemoryHeap ThdHeap;
extern RawData raw_data;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 *
 */
Thread* clear_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  (void)argc;
  (void)argv;
  cli_print("\033[2J");    // ESC seq for clear entire screen
  cli_print("\033[H");     // ESC seq for move cursor at left-top corner
  return NULL;
}

/**
 *
 */
Thread* echo_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;

  int i = 0;

  while (i < argc)
    cli_print(argv[i++]);

  cli_print(ENDL);
  return NULL;
}

/**
 *
 */
Thread* help_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argc;
  (void)argv;

  int32_t i = 0;

  cli_println("Use TAB key for completion, UpArrow for previous command.");
  cli_println("Available commands:");

  while(cmdarray[i].name != NULL){
    cli_print("    ");
    cli_print(cmdarray[i].name);
    cli_print(" - ");
    cli_println(cmdarray[i].help);
    i++;
  }

  return NULL;
}

/**
 *
 */
static WORKING_AREA(LoopCmdThreadWA, 1024);
static msg_t LoopCmdThread(void *arg){
  chRegSetThreadName("LoopCmd");
  (void)arg;

  cli_print("This is loop function test. Press ^C to stop it.\n\r");
  while (!chThdShouldTerminate()){
    int n = 16;
    char str[n];

    snprintf(str, n, "%i\r\n", raw_data.zmag);
    cli_print(str);
    chThdSleepMilliseconds(25);
  }

  chThdExit(0);
  return 0;
}

/**
 *
 */
Thread* loop_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  (void)argc;
  (void)argv;

  Thread *tp = chThdCreateFromHeap(&ThdHeap,
                                  sizeof(LoopCmdThreadWA),
                                  CMD_THREADS_PRIO - 1,
                                  LoopCmdThread,
                                  NULL);
  return tp;
}

/**
 *
 */
Thread* reboot_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;
  cli_print("System going to reboot now...\r\n");
  chThdSleepMilliseconds(100);
  NVIC_SystemReset();
  return NULL;
}

/**
 *
 */
Thread* sleep_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;

  cli_print("System sleeping.\r\n");
  cli_print("Press any key to wake it up.\r\n");
  chThdSleepMilliseconds(100);

  chSysLock();
  PWR->CR |= (PWR_CR_PDDS | PWR_CR_LPDS | PWR_CR_CSBF | PWR_CR_CWUF);
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  __WFI();
  return NULL;
}

/**
 *
 */
Thread* selftest_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;

  cli_print("GPS - OK\r\nModem - OK\r\nEEPROM - OK\r\nStorage - OK\r\nServos - OK\r\n");
  return NULL;
}

/**
 *
 */
Thread* sensor_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;
  cli_print("temperature is ...");
  cli_print(ENDL);
  return NULL;
}

/**
 *
 */
Thread* uname_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  (void)argc;
  (void)argv;

  int n = 80;
  int nres = 0;
  char str[n];

  nres = snprintf(str, n, "Kernel:       %s\r\n", CH_KERNEL_VERSION);
  cli_print_long(str, n, nres);

#ifdef CH_COMPILER_NAME
  nres = snprintf(str, n, "Compiler:     %s\r\n", CH_COMPILER_NAME);
  cli_print_long(str, n, nres);
#endif

  nres = snprintf(str, n, "Architecture: %s\r\n", CH_ARCHITECTURE_NAME);
  cli_print_long(str, n, nres);

#ifdef CH_CORE_VARIANT_NAME
  nres = snprintf(str, n, "Core Variant: %s\r\n", CH_CORE_VARIANT_NAME);
  cli_print_long(str, n, nres);
#endif

#ifdef CH_PORT_INFO
  nres = snprintf(str, n, "Port Info:    %s\r\n", CH_PORT_INFO);
  cli_print_long(str, n, nres);
#endif

#ifdef PLATFORM_NAME
  nres = snprintf(str, n, "Platform:     %s\r\n", PLATFORM_NAME);
  cli_print_long(str, n, nres);
#endif

#ifdef BOARD_NAME
  nres = snprintf(str, n, "Board:        %s\r\n", BOARD_NAME);
  cli_print_long(str, n, nres);
#endif

#ifdef __DATE__
#ifdef __TIME__
  nres = snprintf(str, n, "Build time:   %s%s%s\r\n", __DATE__, " - ", __TIME__);
  cli_print_long(str, n, nres);
#endif
#endif

  return NULL;
}

/**
 *
 */
Thread* ps_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  (void)argc;
  (void)argv;
  Thread *curr = NULL;

#if !CH_USE_REGISTRY
  cli_print("In order to use this function you must set CH_USE_REGISTRY to TRUE\n\r");
  return NULL;

#else
  curr = chRegFirstThread();

  cli_print("name\t\tstate\tprio\ttime\n\r");
  cli_print("------------------------------------------\n\r");
  while (curr->p_refs > 0){
    cli_print(curr->p_name);
    cli_print("\t");
    //cli_print(curr->p_state);
    //cli_print(curr->p_prio);
    //cli_print(curr->p_time);
    cli_print("\n\r");
    curr = chRegNextThread(curr);
  }
  return NULL;
#endif
}





