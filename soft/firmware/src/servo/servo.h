#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_


#define SERVO_MIN 1000
#define SERVO_MAX 2000

struct ServoConfig{
  PWMDriver     *pwmp;
  pwmchannel_t  pwmchannel; // what channel use servo. Enumeration from 0
};
typedef struct ServoConfig ServoConfig;


void Servo0Set(uint8_t angle);
void Servo1Set(uint8_t angle);
void Servo2Set(uint8_t angle);
void Servo3Set(uint8_t angle);
void Servo4Set(uint8_t angle);
void Servo5Set(uint8_t angle);
void Servo6Set(uint8_t angle);
void Servo7Set(uint8_t angle);
void ServoCarThrustSet(uint8_t angle);

void ServoInit(void);

#endif /* SERVO_H_ */