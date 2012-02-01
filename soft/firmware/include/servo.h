#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_


#define SERVO_MIN 1000
#define SERVO_MAX 2000


// ������������ ������������ ��� ������ �����
struct ServoConfig{
  PWMDriver     *pwmp;      // ���-������
  pwmchannel_t  pwmchannel; // �� ����� �� ���-������� ������� ����� �����. ��������� � ����
};
typedef struct ServoConfig ServoConfig;


void ServoInit(void);
void ServoNeutral(void);
void ServoSetAngle(uint16_t n, uint8_t angle);
void CarThrottle(uint8_t angle);


#endif /* SERVO_H_ */
