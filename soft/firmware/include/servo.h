#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_

// ������������ ������������ ��� ������ �����
struct ServoConfig{
  PWMDriver     *pwmp;      // ���-�����
  pwmchannel_t  pwmchannel; // �� ����� �� ���-������� ������� ����� �����. ��������� � ����
  pwmcnt_t      min;
  pwmcnt_t      max;
	pwmcnt_t      current;    // ������� ���� ���������� - "�����" �������� ��������
	pwmcnt_t      neutral;    // ��������. ����� ��������� ��� ���������� �������������� ������� �����
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
