#ifndef CLI_CMD_H_
#define CLI_CMD_H_

#include "../microrl/src/config.h"

Thread* ps_clicmd(int argc, const char * const * argv);
Thread* uname_clicmd(int argc, const char * const * argv);
Thread* help_clicmd(int argc, const char * const * argv);
Thread* clear_clicmd(int argc, const char * const * argv);
Thread* list_clicmd(int argc, const char * const * argv);
Thread* loop_clicmd(int argc, const char * const * argv);
Thread* echo_clicmd(int argc, const char * const * argv);
Thread* reboot_clicmd(int argc, const char * const * argv);
Thread* sleep_clicmd(int argc, const char * const * argv);
Thread* selftest_clicmd(int argc, const char * const * argv);


#endif /* CLI_CMD_H_ */
