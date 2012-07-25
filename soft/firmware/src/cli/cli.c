#include <string.h>
#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "../microrl/src/microrl.h"
#include "chprintf.h"

#include "main.h"
#include "param.h"
#include "cli.h"
#include "cli_cmd.h"
#include "timekeeping.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define _NUM_OF_CMD (sizeof(chibiutils)/sizeof(ShellCmd_t))

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern MemoryHeap LinkThdHeap;
extern GlobalParam_t global_data[];

/*
 *******************************************************************************
 * PROTOTYPES
 *******************************************************************************
 */
int recursive_execute(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* logout_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

static ShellCmd_t chibiutils[] = {
    {"ps",        &ps_cmd,        NULL},
    {"uname",     &uname_cmd,     NULL},
    {"help",      &help_cmd,      NULL},
    {"clear",     &clear_cmd,     NULL},
    {"list",      &list_cmd,      NULL},
    {"loop",      &loop_cmd,      NULL},
    {"echo",      &echo_cmd,      NULL},
    {"date",      &date_cmd,      NULL},
    {"reboot",    &reboot_cmd,    NULL},
    {"sleep",     &sleep_cmd,     NULL},
    {"selftest",  &selftest_cmd,  NULL},
    {"sensor",    &sensor_cmd,    NULL},
    {"logout",    &logout_cmd,    NULL},
    //{"man",       &man_cmd,       NULL},
    //{"kill",    &kill_func,   NULL},
    {NULL,      NULL,         NULL}/* end marker */
};

static SerialDriver *shell_sdp;

// array for comletion
static char *compl_world[_NUM_OF_CMD + 1];

/* thread pointer to currently executing command */
static Thread *current_cmd_tp = NULL;

/* pointer to shell thread */
static Thread *shell_tp = NULL;

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */

/**
 * Search value (pointer to function) by key (name string)
 */
int32_t cmd_search(const char* key, const ShellCmd_t *cmdarray){
  uint32_t i = 0;

  while (cmdarray[i].name != NULL){
    if (strcmp(key, cmdarray[i].name) == 0)
      return i;
    i++;
  }
  return -1;
}

/**
 * Print routine
 */
void cli_print(const char *str){
  int i = 0;
  while (str[i] != 0) {
    sdPut(shell_sdp, str[i]);
    i++;
  }
}

/**
 * Read routine
 */
char get_char (void){
  return sdGet(shell_sdp);
}


//*****************************************************************************
// execute callback for microrl library
// do what you want here, but don't write to argv!!! read only!!
int execute (int argc, const char * const * argv){
  if (recursive_execute(argc, argv, chibiutils) == -1){
    cli_print ("command: '");
    cli_print ((char*)argv[0]);
    cli_print ("' Not found.\n\r");
  }
  return 0;
}

int recursive_execute(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  int i = 0;

  /* search first token */
  i = cmd_search(argv[0], cmdarray);

  /* search token in cmd array */
  if (i != -1){
    if (argc > 1)
      current_cmd_tp = cmdarray[i].func(argc - 1, &argv[1], cmdarray);
    else
      current_cmd_tp = cmdarray[i].func(argc - 1, NULL, cmdarray);
  }
  return i;
}



#ifdef _USE_COMPLETE
//*****************************************************************************
// completion callback for microrl library
char ** complete(int argc, const char * const * argv)
{
  int j = 0;
  int i = 0;

  compl_world[0] = NULL;

  // if there is token in cmdline
  if (argc == 1) {
    // get last entered token
    char * bit = (char*)argv [argc-1];
    // iterate through our available token and match it
    while (chibiutils[i].name != NULL){
      if (strstr(chibiutils[i].name, bit) == chibiutils[i].name)
        compl_world[j++] = chibiutils[i].name;
      i++;
    }
  }
  else { // if there is no token in cmdline, just print all available token
    while (chibiutils[j].name != NULL){
      compl_world[j] = chibiutils[j].name;
      j++;
    }
  }

  // note! last ptr in array always must be NULL!!!
  compl_world[j] = NULL;
  // return set of variants
  return compl_world;
}
#endif


/**
 *
 */
void sigint (void){
  if (current_cmd_tp != NULL){
    chThdTerminate(current_cmd_tp);
    chThdWait(current_cmd_tp);
    current_cmd_tp = NULL;
  }
  cli_print("^C pressed. Exiting...");
  cli_print(ENDL);
}

/**
 * Thread function
 */
static WORKING_AREA(ShellThreadWA, 2048);
static msg_t ShellThread(void *arg){
  chRegSetThreadName("Shell");

  /* init static pointer for serial driver with received pointer */
  shell_sdp = (SerialDriver *)arg;

  // create and init microrl object
  microrl_t microrl_shell;
  cli_print("@@*** Super cool device, version 1.2.3, for help type help... ***@@\r\n");
  microrl_init(&microrl_shell, cli_print);

  // set callback for execute
  microrl_set_execute_callback(&microrl_shell, execute);

  // set callback for completion (optionally)
  microrl_set_complete_callback(&microrl_shell, complete);

  // set callback for ctrl+c handling (optionally)
  microrl_set_sigint_callback(&microrl_shell, sigint);

  while (TRUE){
    // put received char from stdin to microrl lib
    msg_t c = sdGetTimeout(shell_sdp, MS2ST(50));
    if (c != Q_TIMEOUT)
      microrl_insert_char(&microrl_shell, (char)c);

    /* умираем по всем правилам, не забываем убить потомков */
    if (chThdShouldTerminate()){
      if ((current_cmd_tp != NULL) && (current_cmd_tp->p_state != THD_STATE_FINAL)){
        chThdTerminate(current_cmd_tp);
        chThdWait(current_cmd_tp);
      }
      chThdExit(0);
    }
  }
  return 0;
}

Thread* logout_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argc;
  (void)argv;
  (void)cmdarray;

  int sh_enable_index = -1;

  sh_enable_index = _key_index_search("SH_enable");
  if (sh_enable_index == -1)
    chDbgPanic("not found");
  else
    global_data[sh_enable_index].value.u32 = 0;

  return NULL;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 *
 */
void KillShellThreads(void){
  chThdTerminate(shell_tp);
  chThdWait(shell_tp);
}

/**
 *
 */
void SpawnShellThreads(SerialDriver *arg){

  shell_tp = chThdCreateFromHeap(&LinkThdHeap,
                            sizeof(ShellThreadWA),
                            LINK_THREADS_PRIO,
                            ShellThread,
                            arg);
}







