#ifndef CLI_H_
#define CLI_H_

/**
 * Shell command structure
 */
typedef struct ShellCmd_t ShellCmd_t;

/**
 * Fucnction executing command job.
 * @return    Pointer to created thread. Must be NULL if no thread crated.
 */
typedef Thread* (*cmdfunction_t)(int argc, const char * const * argv, SerialDriver *sdp);

/**
 *
 */
struct ShellCmd_t{
  /**
   * Printable command name. Must be zero terminated string without spaces
   */
  char *name;
  /**
   * Function bounded to command
   */
  const cmdfunction_t func;
  /**
   * Short command description for help message.
   */
  char *help;
};


void cli_print(const char *str);
void cli_put(char chr);
void cli_println(const char *str);
char get_char (void);
void cli_print_long(const char * str, int n, int nres);

void CliInit(void);
void SpawnShellThreads(SerialDriver *sdp);
void KillShellThreads(void);

#endif /* CLI_H_ */
