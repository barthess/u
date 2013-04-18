#ifndef BKP_H_
#define BKP_H_

#define bkpGpsLongitude   RTC->BKP0R
#define bkpGpsLatitude    RTC->BKP1R
#define bkpGpsAltitude    RTC->BKP2R

#define bkpOdometer       RTC->BKP3R
#define bkpSoftResetCnt   RTC->BKP4R

#endif /* BKP_H_ */
