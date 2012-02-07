#include <string.h>
#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "../microrl/src/config.h"
#include "../microrl/src/microrl.h"
#include "chprintf.h"

#include "main.h"

extern MemoryHeap LinkThdHeap;


void microrl_set_sigint_callback (microrl_t * this, void (*sigintf)(void));


/*
AVR platform specific implementation routines (for Atmega8, rewrite for your MC)
*/
#define _AVR_DEMO_VER "1.0"

// definition commands word
#define _CMD_HELP   "help"
#define _CMD_INFO   "info"
#define _CMD_CLEAR  "clear"

#define _NUM_OF_CMD 3

//available  commands
char * keyworld [] = {_CMD_HELP, _CMD_INFO, _CMD_CLEAR};

// array for comletion
char * compl_world [_NUM_OF_CMD + 1];


//*****************************************************************************
static SerialDriver *shell_sdp;

//*****************************************************************************
void print (char *str){
  int i = 0;
  while (str[i] != 0) {
    sdPut(shell_sdp, str[i]);
    i++;
  }
}

//*****************************************************************************
char get_char (void){
  return sdGet(shell_sdp);
}

//*****************************************************************************
void print_help (void)
{
  print ("Use TAB key for completion\n\rCommands:\n\r");
  print ("\tclear               - this help\n\r");
  print ("\tclear               - clear screen\n\r");
}

//*****************************************************************************
// execute callback for microrl library
// do what you want here, but don't write to argv!!! read only!!
int execute (int argc, const char * const * argv)
{
  int i = 0;
  // just iterate through argv word and compare it with your commands
  while (i < argc) {
    if (strcmp (argv[i], _CMD_HELP) == 0) {
      print ("microrl v");
      print (MICRORL_LIB_VER);
      print (" library AVR DEMO v");
      print (_AVR_DEMO_VER);
      print("\n\r");
      print_help ();        // print help
    }
    else if (strcmp (argv[i], _CMD_CLEAR) == 0) {
      print ("\033[2J");    // ESC seq for clear entire screen
      print ("\033[H");     // ESC seq for move cursor at left-top corner
    }
    else {
      print ("command: '");
      print ((char*)argv[i]);
      print ("' Not found.\n\r");
    }
    i++;
  }
  return 0;
}

#ifdef _USE_COMPLETE
//*****************************************************************************
// completion callback for microrl library
char ** complet (int argc, const char * const * argv)
{
  int j = 0;

  compl_world [0] = NULL;

  // if there is token in cmdline
  if (argc == 1) {
    // get last entered token
    char * bit = (char*)argv [argc-1];
    // iterate through our available token and match it
    for (int i = 0; i < _NUM_OF_CMD; i++) {
      // if token is matched (text is part of our token starting from 0 char)
      if (strstr(keyworld [i], bit) == keyworld [i]) {
        // add it to completion set
        compl_world [j++] = keyworld [i];
      }
    }
  }
  else { // if there is no token in cmdline, just print all available token
    for (; j < _NUM_OF_CMD; j++) {
      compl_world[j] = keyworld [j];
    }
  }

  // note! last ptr in array always must be NULL!!!
  compl_world [j] = NULL;
  // return set of variants
  return compl_world;
}
#endif

//*****************************************************************************
void sigint (void)
{
  print ("^C catched!\n\r");
}




static WORKING_AREA(ShellThreadWA, 2048);
static msg_t ShellThread(void *arg){
  chRegSetThreadName("Shell");

  /* init static pointer for serial driver with received pointer */
  shell_sdp = (SerialDriver *)arg;

  // create and init microrl object
  microrl_t microrl_shell;
  microrl_init (&microrl_shell, print);

  // set callback for execute
  microrl_set_execute_callback(&microrl_shell, execute);
  // set callback for completion (optionally)
  microrl_set_complite_callback(&microrl_shell, complet);
  // set callback for ctrl+c handling (optionally)

  microrl_set_sigint_callback(&microrl_shell, sigint);

  while (TRUE) {
    // put received char from stdin to microrl lib
    char c = sdGet(shell_sdp);
    microrl_insert_char (&microrl_shell, c);
  }
  return 0;
}









void SpawnShellThread(SerialDriver *arg){

  chThdCreateFromHeap(&LinkThdHeap,
          sizeof(ShellThreadWA),
          LINK_THREADS_PRIO,
          ShellThread,
          arg);
}







