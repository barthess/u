#ifndef CLI_CMD_H_
#define CLI_CMD_H_

#include "cli.h"


Thread* ps_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* uname_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* help_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* clear_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* list_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* loop_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* echo_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* reboot_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* sleep_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* selftest_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);
Thread* sensor_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);


#endif /* CLI_CMD_H_ */
