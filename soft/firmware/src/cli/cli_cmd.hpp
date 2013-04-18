#ifndef CLI_CMD_H_
#define CLI_CMD_H_

#include "../microrl/src/config.h"

Thread* ps_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
Thread* uname_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
Thread* clear_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
Thread* list_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
Thread* loop_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
Thread* echo_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
Thread* reboot_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
Thread* sleep_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
Thread* selftest_clicmd(int argc, const char * const * argv, SerialDriver *sdp);


#endif /* CLI_CMD_H_ */
