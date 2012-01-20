#include "ch.h"
#include "main.h"
#include "message.h"

#ifndef LINK_H_
#define LINK_H_

/* максимальная скорость модема даже слегка недостаточна - пакеты все равно не
 * все приходят из-за внутренних задержек */
#define BAUDRATE_XBEE 115200

void LinkInitXbeeMav(void);


#endif /* LINK_H_ */
