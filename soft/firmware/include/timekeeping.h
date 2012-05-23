#ifndef TIMEKEEPING_H_
#define TIMEKEEPING_H_

#include <time.h>

#include "cli.h"

void TimekeepingInit(void);
uint64_t pnsGetTimeUnixUsec(void);

Thread* date_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);

#endif /* TIMEKEEPING_H_ */
