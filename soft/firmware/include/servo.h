#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_


#define SERVO_MIN 1000
#define SERVO_MAX 2000

#define Servo0Set(angle) {ServoSetAngle(0, angle);}
#define Servo1Set(angle) {ServoSetAngle(1, angle);}
#define Servo2Set(angle) {ServoSetAngle(2, angle);}
#define Servo3Set(angle) {ServoSetAngle(3, angle);}
#define Servo4Set(angle) {ServoSetAngle(4, angle);}
#define Servo5Set(angle) {ServoSetAngle(5, angle);}
#define Servo6Set(angle) {ServoSetAngle(6, angle);}
#define Servo7Set(angle) {ServoSetAngle(7, angle);}


// персональная конфигурация для каждой сервы
struct ServoConfig{
  PWMDriver     *pwmp;      // ШИМ-таймер
  pwmchannel_t  pwmchannel; // на каком из ШИМ-каналов таймера висит серва. НУМЕРАЦИЯ С НУЛЯ
};
typedef struct ServoConfig ServoConfig;


void ServoInit(void);
void ServoNeutral(void);
void ServoSetAngle(uint16_t n, uint8_t angle);
void ServoCarThrottleSet(uint8_t angle);


#endif /* SERVO_H_ */
