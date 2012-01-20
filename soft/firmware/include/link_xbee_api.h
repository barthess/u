#include "ch.h"
#include "main.h"
#include "message.h"

#ifndef LINK_H_
#define LINK_H_

/* максимальная скорость модема даже слегка недостаточна - пакеты все равно не
 * все приходят из-за внутренних задержек */
#define BAUDRATE_XBEE 115200

#define xbee_reset_assert() {palClearPad(GPIOE, GPIOE_XBEE_RESET);}
#define xbee_reset_clear()  {palSetPad(GPIOE, GPIOE_XBEE_RESET);}

#define xbee_sleep_assert() {palClearPad(GPIOE, GPIOE_XBEE_SLEEP);}
#define xbee_sleep_clear()  {palSetPad(GPIOE, GPIOE_XBEE_RESET);}

void LinkInitXbeeApi(void);


#endif /* LINK_H_ */
