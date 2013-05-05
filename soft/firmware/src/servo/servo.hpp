#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_


#define SERVO_MIN 1000
#define SERVO_MAX 2000

struct ServoConfig{
  PWMDriver       *pwmp;
  pwmchannel_t    pwmchannel; // what channel used by servo. Enumeration from 0
  const uint16_t  *min;
  const uint16_t  *max;
  const uint16_t  *neutr;
};
typedef struct ServoConfig ServoConfig;

#define ServoCarYawSet(v) {Servo7Set(v);}

void Servo0Set(uint8_t angle);
void Servo1Set(uint8_t angle);
void Servo2Set(uint8_t angle);
void Servo3Set(uint8_t angle);
void Servo4Set(uint8_t angle);
void Servo5Set(uint8_t angle);
void Servo6Set(uint8_t angle);
void Servo7Set(uint8_t angle);
void ServoCarThrustSet(uint8_t angle);
uint8_t float2thrust(float v);
uint8_t float2servo(float v);

void ServoInit(void);

#endif /* SERVO_H_ */
