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


// TODO: корректировать гироскопы с помощью ПИД-регулирующего алгоритма




/* длина буфера для результатов АЦП. Мнемонически - количество рядов
 * прямоугольной матрицы, каждый ряд - conversion group */
#define ADC_BUF_DEPTH 1

/*
 * количество каналов:
 * 1  гироскоп_Х
 * 2  гироскоп_У
 * 3  гироскоп_Й
 * 4  ток бортсети
 * 5  напряжение борт-сери
 * 6  джойстик
 */
#define ADC_CH_NUM 6

//battery, current, Z, y, x, joy
// где лежат текущие значения АЦП
#define JOY_ADC_OFFSET     0
#define VOLTAGE_ADC_OFFSET 1
#define CURRENT_ADC_OFFSET 2
#define GYRO_ADC_X_OFFSET  3
#define GYRO_ADC_Y_OFFSET  4
#define GYRO_ADC_Z_OFFSET  5

/* промежутки между получениями данных гироскопов в микросекундах
 * Расшифровку см. в каментах к коллбэку АЦП */
#define GYRO_ADC_PERIOD (28 * 6 * 8 * 3)

/* промежутки между рассылкой данных АЦП в миллисекундах */
#define NORMAL_ADC_PERIOD  10  // стандартная частота обновления данных


void ADCInit_pns(void);


#endif /* ADC_H_ */
// vim:sw=2:ai 
