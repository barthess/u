#ifndef TIMEKEEPING_H_
#define TIMEKEEPING_H_

#include "cli.hpp"

void TimekeepingInit(void);
uint64_t pnsGetTimeUnixUsec(void);
systime_t GetTimeInterval(systime_t *last);

Thread* date_clicmd(int argc, const char * const * argv, SerialDriver *sdp);
uint16_t getCpuLoad(void);

#endif /* TIMEKEEPING_H_ */
