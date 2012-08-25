#ifndef BKP_H_
#define BKP_H_

void bkpSaveGpsLongitude(uint32_t n);
uint32_t bkpGetGpsLongitude(void);

void bkpSaveGpsLatitude(uint32_t n);
uint32_t bkpGetGpsLatitude(void);

void bkpSaveGpsAltitude(uint32_t n);
uint32_t bkpGetGpsAltitude(void);

#define bkpOdometer RTC->BKP3R

#endif /* BKP_H_ */
