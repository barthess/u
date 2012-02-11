#ifndef CLI_H_
#define CLI_H_

/**
 * Shell command structure
 */
typedef struct ShellCmd_t ShellCmd_t;

/**
 * Fucnction executing command job.
 */
typedef Thread* (*cmdfunction_t)(int argc, const char * const * argv, const ShellCmd_t *cmdarray);


struct ShellCmd_t{
  /**
   * Printable command name. Must be zero terminated string
   */
  char *name;
  /**
   * Function binded to command
   */
  const cmdfunction_t func;
  /**
   * Pointer to structure with subcommands. May be NULL.
   */
  const ShellCmd_t *subcmd;
};

void cli_print(const char *str);
char get_char (void);

void CliInit(void);
void SpawnShellThread(SerialDriver *sdp);


#endif /* CLI_H_ */
