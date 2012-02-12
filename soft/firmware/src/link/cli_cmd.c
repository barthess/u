#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ch.h"
#include "hal.h"

#include "main.h"
#include "cli.h"
#include "cli_cmd.h"


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
extern MemoryHeap LinkThdHeap;

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

Thread* clear_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  (void)argc;
  (void)argv;
  cli_print("\033[2J");    // ESC seq for clear entire screen
  cli_print("\033[H");     // ESC seq for move cursor at left-top corner
  return NULL;
}

Thread* list_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argc;
  (void)argv;
  int i = 0;

  cli_print("available commands:\n\r");
  while(cmdarray[i].name != NULL){
    cli_print("\t");
    cli_print(cmdarray[i].name);
    cli_print("\n\r");
    i++;
  }
  return NULL;
}

Thread* echo_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;

  int i = 0;

  while (i < argc)
    cli_print(argv[i++]);

  cli_print("\n\r");
  return NULL;
}

Thread* help_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  (void)argc;
  (void)argv;
  cli_print ("Use TAB key for completion\n\rCommand:\n\r");
  cli_print ("\tversion {microrl | demo} - print version of microrl lib or version of this demo src\n\r");
  cli_print ("\thelp  - this message\n\r");
  cli_print ("\tclear - clear screen\n\r");
  cli_print ("\tlist  - list all commands in tree\n\r");
  cli_print ("\tloop  - command to test ^C fucntionallity\n\r");
  cli_print ("\t        and for demonstation auto-completion, while inputed 'l+<TAB>'\n\r");
  return NULL;
}


static WORKING_AREA(LoopCmdThreadWA, 128);
static msg_t LoopCmdThread(void *arg){
  chRegSetThreadName("LoopCmd");
  (void)arg;
  int i = 10;

  while (i > 0){
    cli_print("This is loop function test. Press ^C to stop it.\n\r");
    chThdSleepMilliseconds(1000);
    i--;
    if (chThdShouldTerminate())
      chThdExit(0);
  }
  return 0;
}

Thread* loop_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  (void)argc;
  (void)argv;

  Thread *tp = chThdCreateFromHeap(&LinkThdHeap,
                                  sizeof(LoopCmdThreadWA),
                                  CMD_THREADS_PRIO - 1,
                                  LoopCmdThread,
                                  NULL);
  return tp;
}


Thread* reboot_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;
  cli_print("System going to reboot now...\r\n");
  chThdSleepMilliseconds(100);
  NVIC_SystemReset();
  return NULL;
}

Thread* sleep_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
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

Thread* selftest_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;

  cli_print("GPS - OK\r\nModem - OK\r\nEEPROM - OK\r\nStorage - OK\r\nServos - OK\r\n");
  return NULL;
}

Thread* sensor_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;
  cli_print("temperature is ... \n\r");
  return NULL;
}



/**
 * helper function
 */
void long_cli_print(const char * str, int n, int nres){
  cli_print(str);
  if (nres > n)
    cli_print("\n\r");
}

Thread* uname_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)cmdarray;
  (void)argc;
  (void)argv;

  int n = 64;
  int nres = 0;
  char str[n];

  nres = snprintf(str, n, "Kernel:       %s\r\n", CH_KERNEL_VERSION);
  long_cli_print(str, n, nres);

#ifdef CH_COMPILER_NAME
  nres = snprintf(str, n, "Compiler:     %s\r\n", CH_COMPILER_NAME);
  long_cli_print(str, n, nres);
#endif

  nres = snprintf(str, n, "Architecture: %s\r\n", CH_ARCHITECTURE_NAME);
  long_cli_print(str, n, nres);

#ifdef CH_CORE_VARIANT_NAME
  nres = snprintf(str, n, "Core Variant: %s\r\n", CH_CORE_VARIANT_NAME);
  long_cli_print(str, n, nres);
#endif

#ifdef CH_PORT_INFO
  nres = snprintf(str, n, "Port Info:    %s\r\n", CH_PORT_INFO);
  long_cli_print(str, n, nres);
#endif

#ifdef PLATFORM_NAME
  nres = snprintf(str, n, "Platform:     %s\r\n", PLATFORM_NAME);
  long_cli_print(str, n, nres);
#endif

#ifdef BOARD_NAME
  nres = snprintf(str, n, "Board:        %s\r\n", BOARD_NAME);
  long_cli_print(str, n, nres);
#endif

#ifdef __DATE__
#ifdef __TIME__
  nres = snprintf(str, n, "Build time:   %s%s%s\r\n", __DATE__, " - ", __TIME__);
  long_cli_print(str, n, nres);
#endif
#endif

  return NULL;
}





Thread* ps_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
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
    cli_print("\n\r");
    curr = chRegNextThread(curr);
  }
  return NULL;
#endif
}





