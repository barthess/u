#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_


#define SERVO_MIN 1000
#define SERVO_MAX 2000


// персональная конфигурация для каждой сервы
struct ServoConfig{
  PWMDriver     *pwmp;      // ШИМ-таймер
  pwmchannel_t  pwmchannel; // на каком из ШИМ-каналов таймера висит серва. НУМЕРАЦИЯ С НУЛЯ
};
typedef struct ServoConfig ServoConfig;


void ServoInit(void);
void ServoNeutral(void);
void ServoSetAngle(uint16_t n, uint8_t angle);
void CarThrottle(uint8_t angle);


#endif /* SERVO_H_ */
