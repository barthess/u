#ifndef CLI_H_
#define CLI_H_


typedef void (*cmdfunction_t)(int argc, const char * const * argv);

/**
 * Shell command structure
 */
typedef struct ShellCmd_t ShellCmd_t;
struct ShellCmd_t{
  char *name;             /* printable command name */
  const cmdfunction_t func;     /* binded function */
  const ShellCmd_t *subcmdp;    /* pointer to structure with subcommands */
};



void CliInit(void);
void SpawnShellThread(SerialDriver *sdp);


#endif /* CLI_H_ */
