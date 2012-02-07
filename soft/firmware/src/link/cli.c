#include <string.h>
#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "../microrl/src/microrl.h"
#include "chprintf.h"

#include "main.h"
#include "cli.h"


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
static SerialDriver *shell_sdp;

/*
 *******************************************************************************
 * PROTOTYPES
 *******************************************************************************
 */
void microrl_set_sigint_callback (microrl_t * this, void (*sigintf)(void));

/*
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 */
void print(char *str){
  int i = 0;
  while (str[i] != 0) {
    sdPut(shell_sdp, str[i]);
    i++;
  }
}

char get_char (void){
  return sdGet(shell_sdp);
}

void print_help (void)
{
  print ("Use TAB key for completion\n\rCommand:\n\r");
  print ("\tversion {microrl | demo} - print version of microrl lib or version of this demo src\n\r");
  print ("\thelp  - this message\n\r");
  print ("\tclear - clear screen\n\r");
  print ("\tlist  - list all commands in tree\n\r");
  print ("\tname [string] - print 'name' value if no 'string', set name value to 'string' if 'string' present\n\r");
  print ("\tlisp - dummy command for demonstation auto-completion, while inputed 'l+<TAB>'\n\r");
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

void ps_func(int argc, const char * const * argv);
void uname_func(int argc, const char * const * argv);
void man_func(int argc, const char * const * argv);
void help_func(int argc, const char * const * argv);
void clear_func(int argc, const char * const * argv);
void list_func(int argc, const char * const * argv);
void lisp_func(int argc, const char * const * argv);
void echo_func(int argc, const char * const * argv);


ShellCmd_t chibiutils[] = {
    {"ps",      &ps_func,     NULL},
    {"uname",   &uname_func,  NULL},
    {"man",     &man_func,    NULL},
    {"help",    &help_func,   NULL},
    {"clear",   &clear_func,  NULL},
    {"list",    &list_func,   NULL},
    {"lisp",    &lisp_func,   NULL},
    {"echo",    &echo_func,   NULL},
    //{"kill",    &kill_func,   NULL},
    //{"reboot",    &reboot_func,   NULL},
    //{"poweroff",    &poweroff_func,   NULL},
    //{"logout",    &logout_func,   NULL},
    //{"test",    &test_func,   NULL},
    {NULL,      NULL,         NULL}/* end marker */
};

#define _NUM_OF_CMD (sizeof(chibiutils)/sizeof(ShellCmd_t))




void clear_func(int argc, const char * const * argv){
  (void)argc;
  (void)argv;
  print ("\033[2J");    // ESC seq for clear entire screen
  print ("\033[H");     // ESC seq for move cursor at left-top corner
}

void list_func(int argc, const char * const * argv){
  (void)argc;
  (void)argv;
  int i = 0;

  print("available commands:\n\r");
  while(chibiutils[i].name != NULL){
    print("\t");
    print(chibiutils[i].name);
    print("\n\r");
    i++;
  }
}

void echo_func(int argc, const char * const * argv){
  int i = 0;

  while (i < argc)
    print(argv[i++]);

  print("\n\r");
}

void help_func(int argc, const char * const * argv){
  (void)argc;
  (void)argv;
  print_help();
}

void lisp_func(int argc, const char * const * argv){
  (void)argc;
  (void)argv;
  print("this is test dummy\n\r");
}

void ps_func(int argc, const char * const * argv){(void)argc; (void)argv; print("stub\n\r");}
void uname_func(int argc, const char * const * argv){(void)argc; (void)argv; print("stub\n\r");}
void man_func(int argc, const char * const * argv){(void)argc; (void)argv; print("stub\n\r");}


int32_t cmd_search(const char* key, ShellCmd_t *cmdarray){
  uint32_t i = 0;

  while (cmdarray[i].name != NULL){
    if (strcmp(key, cmdarray[i].name) == 0)
      return i;
    i++;
  }
  return -1;
}






// array for comletion
char * compl_world [_NUM_OF_CMD + 1];





//*****************************************************************************
// execute callback for microrl library
// do what you want here, but don't write to argv!!! read only!!
int execute (int argc, const char * const * argv)
{
  /* search first token */
  int i = 0;
  i = cmd_search(argv[0], chibiutils);
  if (i != -1)
    /* pass next arguments to worker function */
    chibiutils[i].func(argc - 1, &argv[1]);
  else{
    print ("command: '");
    print ((char*)argv[0]);
    print ("' Not found.\n\r");
  }
  return 0;
}


#ifdef _USE_COMPLETE
//*****************************************************************************
// completion callback for microrl library
char ** complet (int argc, const char * const * argv)
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
  microrl_init(&microrl_shell, print);

  // set callback for execute
  microrl_set_execute_callback(&microrl_shell, execute);

  // set callback for completion (optionally)
  microrl_set_complite_callback(&microrl_shell, complet);

  // set callback for ctrl+c handling (optionally)
  microrl_set_sigint_callback(&microrl_shell, sigint);

  while (TRUE){
    // put received char from stdin to microrl lib
    char c = sdGet(shell_sdp);
    microrl_insert_char(&microrl_shell, c);
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







