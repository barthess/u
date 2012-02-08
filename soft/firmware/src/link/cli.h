#ifndef CLI_H_
#define CLI_H_

/**
 * Fucnction executing command job.
 */
typedef void (*cmdfunction_t)(int argc, const char * const * argv);

/**
 * Shell command structure
 */
typedef struct ShellCmd_t ShellCmd_t;
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



void CliInit(void);
void SpawnShellThread(SerialDriver *sdp);


#endif /* CLI_H_ */
