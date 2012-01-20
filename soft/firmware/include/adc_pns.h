/*
 * sensors.h
 *
 *  Created on: 17.03.2011
 *      Author: barthess
 */

#include <stdlib.h>
#include "ch.h"
#include "hal.h"

#ifndef ADC_H_
#define ADC_H_


// TODO: �������������� ��������� � ������� ���-������������� ���������




/* ����� ������ ��� ����������� ���. ������������ - ���������� �����
 * ������������� �������, ������ ��� - conversion group */
#define ADC_BUF_DEPTH 1

/*
 * ���������� �������:
 * 1  ��������_�
 * 2  ��������_�
 * 3  ��������_�
 * 4  ��� ��������
 * 5  ���������� ����-����
 * 6  ��������
 */
#define ADC_CH_NUM 6

//battery, current, Z, y, x, joy
// ��� ����� ������� �������� ���
#define JOY_ADC_OFFSET     0
#define VOLTAGE_ADC_OFFSET 1
#define CURRENT_ADC_OFFSET 2
#define GYRO_ADC_X_OFFSET  3
#define GYRO_ADC_Y_OFFSET  4
#define GYRO_ADC_Z_OFFSET  5

/* ���������� ����� ����������� ������ ���������� � �������������
 * ����������� ��. � �������� � �������� ��� */
#define GYRO_ADC_PERIOD (28 * 6 * 8 * 3)

/* ���������� ����� ��������� ������ ��� � ������������� */
#define NORMAL_ADC_PERIOD  10  // ����������� ������� ���������� ������


void ADCInit_pns(void);


#endif /* ADC_H_ */
// vim:sw=2:ai 
