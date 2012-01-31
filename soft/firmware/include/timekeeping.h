#ifndef TIMEKEEPING_H_
#define TIMEKEEPING_H_

#include <time.h>


void TimekeepingInit(void);
void tm2bcd(struct tm *timp, RTCTime *timespec);
void bcd2tm(struct tm *timp, uint32_t tv_time, uint32_t tv_date);


#endif /* TIMEKEEPING_H_ */
