#ifndef CLI_CMD_H_
#define CLI_CMD_H_

#include "cli.h"
#include "../microrl/src/config.h"

void cli_print_long(const char * str, int n, int nres);

Thread* ps_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* uname_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* help_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* clear_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* list_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* loop_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* echo_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* reboot_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* sleep_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* selftest_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* sensor_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);


#endif /* CLI_CMD_H_ */
