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
#define _NUM_OF_CMD (sizeof(chibiutils)/sizeof(ShellCmd_t))

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern MemoryHeap LinkThdHeap;

/*
 *******************************************************************************
 * PROTOTYPES
 *******************************************************************************
 */
int recursive_execute(int argc, const char * const * argv, const ShellCmd_t *cmdarray);

void ps_func(int argc, const char * const * argv);
void uname_func(int argc, const char * const * argv);
void man_func(int argc, const char * const * argv);
void help_func(int argc, const char * const * argv);
void clear_func(int argc, const char * const * argv);
void list_func(int argc, const char * const * argv);
void lisp_func(int argc, const char * const * argv);
void echo_func(int argc, const char * const * argv);

void git_func(int argc, const char * const * argv);
void git_stash_func(int argc, const char * const * argv);
void git_help_func(int argc, const char * const * argv);
void git_submodule_init_func(int argc, const char * const * argv);
void git_submodule_add_func(int argc, const char * const * argv);
void git_submodule_func(int argc, const char * const * argv);

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static ShellCmd_t git_submodule_commands[] = {
    {"init",  &git_submodule_init_func, NULL},
    {"add",   &git_submodule_add_func,  NULL},
    {NULL,    NULL,                     NULL}/* end marker */
};

static ShellCmd_t git_commands[] = {
    {"submodule", &git_submodule_func,  git_submodule_commands},
    {"stash",     &git_stash_func,      NULL},
    {"help",      &git_help_func,       NULL},
    {NULL,        NULL,                 NULL}/* end marker */
};

static ShellCmd_t chibiutils[] = {
    {"ps",      &ps_func,     NULL},
    {"uname",   &uname_func,  NULL},
    {"man",     &man_func,    NULL},
    {"help",    &help_func,   NULL},
    {"clear",   &clear_func,  NULL},
    {"list",    &list_func,   NULL},
    {"lisp",    &lisp_func,   NULL},
    {"echo",    &echo_func,   NULL},
    {"git",     &git_func,    git_commands}, /* for multiword command demonstration */
    //{"kill",    &kill_func,   NULL},
    //{"reboot",    &reboot_func,   NULL},
    //{"poweroff",    &poweroff_func,   NULL},
    //{"logout",    &logout_func,   NULL},
    //{"test",    &test_func,   NULL},
    {NULL,      NULL,         NULL}/* end marker */
};

static SerialDriver *shell_sdp;

// array for comletion
static char *compl_world[_NUM_OF_CMD + 1];

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
void print(const char *str){
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
  print ("Use TAB key for completion\n\rCommand:\n\r");
  print ("\tversion {microrl | demo} - print version of microrl lib or version of this demo src\n\r");
  print ("\thelp  - this message\n\r");
  print ("\tclear - clear screen\n\r");
  print ("\tlist  - list all commands in tree\n\r");
  print ("\tname [string] - print 'name' value if no 'string', set name value to 'string' if 'string' present\n\r");
  print ("\tlisp - dummy command for demonstation auto-completion, while inputed 'l+<TAB>'\n\r");
}

void lisp_func(int argc, const char * const * argv){
  (void)argc;
  (void)argv;
  print("this is test dummy\n\r");
}

void ps_func(int argc, const char * const * argv){(void)argc; (void)argv; print("stub\n\r");}
void uname_func(int argc, const char * const * argv){(void)argc; (void)argv; print("stub\n\r");}
void man_func(int argc, const char * const * argv){(void)argc; (void)argv; print("stub\n\r");}

void git_func(int argc, const char * const * argv){
  if(argc == 0){
    print("git: you must specify option or subcommand\n\r");
    return;
  }
  if (recursive_execute(argc, argv, git_commands) == -1){
    print("git: this is not subcommand but parameter \n\r");
  }
}

void git_submodule_func(int argc, const char * const * argv){
  if(argc == 0){
    print("git: you must specify option or subcommand\n\r");
    return;
  }
  print("git submodule execute\n\r");
  if (recursive_execute(argc, argv, git_submodule_commands) == -1){
    print("git: this is not subcommand but parameter \n\r");
  }
}

void git_submodule_init_func(int argc, const char * const * argv){
  (void)argc; (void)argv;
  print("git submodule init executin\n\r");
}
void git_submodule_add_func(int argc, const char * const * argv){
  (void)argc; (void)argv; print("git submodule add executing\n\r");
}

void git_stash_func(int argc, const char * const * argv){
  (void)argc; (void)argv; print("git stash\n\r");
}

void git_help_func(int argc, const char * const * argv){
  (void)argc; (void)argv; print("git help \n\r");
}

//*****************************************************************************
// execute callback for microrl library
// do what you want here, but don't write to argv!!! read only!!
int execute (int argc, const char * const * argv){
  if (recursive_execute(argc, argv, chibiutils) == -1){
    print ("command: '");
    print ((char*)argv[0]);
    print ("' Not found.\n\r");
  }
  return 0;
}

int recursive_execute(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  int i = 0;

  /* search first token */
  i = cmd_search(argv[0], cmdarray);

  /* search token in cmd array */
  if (i != -1){
    if (argc > 1){
      cmdarray[i].func(argc - 1, &argv[1]);
    }
    else{
      /* if there is no arguments for subcommand */
      cmdarray[i].func(argc - 1, NULL);
    }
  }
  return i;
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


/**
 *
 */
void sigint (void)
{
  print ("^C catched!\n\r");
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
  print("@@*** Super cool device, version 1.2.3, for help type help... ***@@\r\n");
  chThdSleepMilliseconds(100);

  microrl_init(&microrl_shell, print);
  chThdSleepMilliseconds(100);

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


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

void SpawnShellThread(SerialDriver *arg){

  chThdCreateFromHeap(&LinkThdHeap,
          sizeof(ShellThreadWA),
          LINK_THREADS_PRIO,
          ShellThread,
          arg);
}







