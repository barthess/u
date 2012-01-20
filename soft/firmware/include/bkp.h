/*
 * bkp.h
 *
 *  Created on: 24.07.2011
 *      Author: barthess
 */

#ifndef BKP_H_
#define BKP_H_


#define BKP_DR_EEPROMLOG (BKP->DR1) // адрес последней записи лога
#define BKP_DR_ROUTEPOINTNUM (BKP->DR2) // тут хранится общее количество точек маршрута



void bkpInit(void);

#endif /* BKP_H_ */
