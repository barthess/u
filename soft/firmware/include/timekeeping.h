#ifndef TIMEKEEPING_H_
#define TIMEKEEPING_H_

#include <time.h>

#include "cli.h"

void TimekeepingInit(void);
uint64_t pnsGetTimeUnixUsec(void);
systime_t GetTimeInterval(systime_t *last);

Thread* date_cmd(int argc, const char * const * argv);

#endif /* TIMEKEEPING_H_ */
