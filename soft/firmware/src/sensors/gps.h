#include <stdlib.h>
#include "ch.h"
#include "hal.h"

#ifndef GPS_H_
#define GPS_H_

/* From standard: A sentence may contain up to 80 characters plus "$" and CR/LF.
 * так же вычтем первые 5 символов, которые мы не сохраняем в буфер*/
#define GPS_MSG_LEN 75


#define GP_TALKER    (('G' << 8)  + 'P')
#define GGA_SENTENCE (('G' << 16) + ('G' << 8) + 'A')
#define RMC_SENTENCE (('R' << 16) + ('M' << 8) + 'C')

// установка выдачи только GGA & RMC
#define GPS_MSG_STR ((const uint8_t *)("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n"))
#define GPS_MSG_STR_LEN 51
// подтверждение
//$PMTK001,314,3*36

// время между фиксацией координат в милисекундах
#define GPS_FIX_PERIOD_STR ((const uint8_t *)("$PMTK300,200,0,0,0,0*2F\r\n"))
#define GPS_FIX_PERIOD_STR_LEN 25
// подтверждение
// $PMTK001,300,3*33

// установка скорости обмена
#define GPS_HI_BAUDRATE_STR ((const uint8_t *)("$PMTK251,57600*2C\r\n"))
#define GPS_HI_BAUDRATE_STR_LEN 19

#define GPS_DEFAULT_BAUDRATE 9600
#define GPS_HI_BAUDRATE 57600

/* рассчет количества милисекунд, необходимых для отправки заданного количества
 байт на заданном бодрейте. 13 - это количество бод в одном байте (взято
 с запасом). 2 - это дополнительные запасные милисекунды */
#define byte2msec(bytes, baudrate) (((bytes * 13 * 1000) / baudrate) + 2)

/* фукнции подачи/отдачи питания на GPS */
#define gps_power_on()  {palClearPad(GPIOE, GPIOE_GPS_PWR_EN);}
#define gps_power_off() {palSetPad(GPIOE, GPIOE_GPS_PWR_EN);


void GPSInit(void);



#endif /* GPS_H_ */
