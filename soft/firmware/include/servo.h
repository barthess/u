/*
 * servo.h
 *
 *  Created on: 04.01.2011
 *      Author: barthess
 *
 *      ���������� ��� PWMDriver ��� ���������� �������.
 *
 *      ��������� ��������� ����������� ����� ��� ��,
 *      ��� � ��� ����� - �� ���� ��������� ������.
 *
 */

#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_


#define SERVO_COUNT 4
// ���������� ���� ��� �������� �������� ���� ����
#define SERVO_SETTINGS_SIZE (3 * SERVO_COUNT * (sizeof(pwmcnt_t)))

/**
 * ��� ������� ������������ �������� ��� 2���, ������ ������ ����� - 0.5���.
 * ����� �������� 20�� (����������� ������� �������������) - ���� � �������
 * ��� ��������� �������� 20 * 1000 / 0.5 = 40000
 */
#define PWM_FREQ   2000000 /* 2MHz ������� ������������ �������� ��� */
#define RELOAD_VAL 40000   /* �������� �������� ���������������� (������ ���) */

#if !(ENABLE_IRQ_STORM)
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
#endif

void ServoInit(void);
uint8_t Servo_ReadFromEeprom(uint8_t *buf);
uint8_t Servo_SettingsApply(uint8_t *buf, bool_t eeprom_refresh);
void set_elevator(uint8_t angle);
void set_throttle(uint8_t angle);
void set_rudder(uint8_t angle);
void set_aileron(uint8_t angle);
void Servo_NeutralSet(void);


#endif /* SERVO_H_ */
