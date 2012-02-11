#ifndef TIMEKEEPING_H_
#define TIMEKEEPING_H_

#include <time.h>

#include "cli.h"

void TimekeepingInit(void);
void tm2bcd(struct tm *timp, RTCTime *timespec);
void bcd2tm(struct tm *timp, uint32_t tv_time, uint32_t tv_date);

Thread* date_cmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray);

#endif /* TIMEKEEPING_H_ */
