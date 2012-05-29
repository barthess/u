#ifndef BKP_H_
#define BKP_H_

void bkpSaveGpsLongitude(uint32_t n);
uint32_t bkpLoadGpsLongitude(void);

void bkpSaveGpsLatitude(uint32_t n);
uint32_t bkpLoadGpsLatitude(void);

void bkpSaveGpsAltitude(uint32_t n);
uint32_t bkpLoadGpsAltitude(void);

#endif /* BKP_H_ */
