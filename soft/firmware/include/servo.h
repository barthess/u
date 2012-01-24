#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_

// персональная конфигурация для каждой сервы
struct ServoConfig{
  PWMDriver     *pwmp;      // ШИМ-канал
  pwmchannel_t  pwmchannel; // на каком из ШИМ-каналов таймера висит серва. НУМЕРАЦИЯ С НУЛЯ
  pwmcnt_t      min;
  pwmcnt_t      max;
	pwmcnt_t      current;    // текущий угол отклонения - "сырое" значение регистра
	pwmcnt_t      neutral;    // нейтраль. Может смещаться для реализации неравномерного расхода рулей
};
typedef struct ServoConfig ServoConfig;



void ServoInit(void);
void ServoNeutral(void);

void CarThrottle(uint8_t angle);

void Servo1SetAngle(uint8_t angle);
void Servo2SetAngle(uint8_t angle);
void Servo3SetAngle(uint8_t angle);
void Servo4SetAngle(uint8_t angle);
void Servo5SetAngle(uint8_t angle);
void Servo6SetAngle(uint8_t angle);
void Servo7SetAngle(uint8_t angle);
void Servo8SetAngle(uint8_t angle);


#endif /* SERVO_H_ */
