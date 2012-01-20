/*
 * servo.h
 *
 *  Created on: 04.01.2011
 *      Author: barthess
 *
 *      Надстройка над PWMDriver для управления сервами.
 *
 *      Поскольку двигатель управляется точно так же,
 *      как и все сервы - он тоже считается сервой.
 *
 */

#include "ch.h"
#include "hal.h"

#ifndef SERVO_H_
#define SERVO_H_


#define SERVO_COUNT 4
// количество байт для хранения настроек всех серв
#define SERVO_SETTINGS_SIZE (3 * SERVO_COUNT * (sizeof(pwmcnt_t)))

/**
 * При частоте тактирования счетчика ШИМ 2МГц, период одного такта - 0.5мкс.
 * Чтобы получить 20мс (стандартная частота сервоприводов) - надо в счетчик
 * ШИМ загружать значение 20 * 1000 / 0.5 = 40000
 */
#define PWM_FREQ   2000000 /* 2MHz частота тактирования счетчика ШИМ */
#define RELOAD_VAL 40000   /* Значение регистра автоперезагрузки (период ШИМ) */

#if !(ENABLE_IRQ_STORM)
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
