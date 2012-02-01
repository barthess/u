

/*
 *      Для аналоговых серв ширина импульса должна быть
 *      в пределах 1.0 - 2.0 мс. Середина - 1.5 мс.
 *      Период - 20 мс.
 */

#include "servo.h"
#include "message.h"
#include "main.h"
#include "eeprom.h"

#include "mavlink.h"
#include "bart.h"
#include "common.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
//extern uint32_t GlobalFlags;
extern RawData raw_data;
//extern Mailbox tolink_mb;
//extern mavlink_system_t mavlink_system;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SERVO_MIN 2000
#define SERVO_MAX 4000

/* При частоте тактирования счетчика ШИМ 2МГц, период одного такта - 0.5мкс.
   Чтобы получить 20мс (стандартная частота сервоприводов) - надо в счетчик
   ШИМ загружать значение 20 * 1000 / 0.5 = 40000 */
#define PWM_FREQ      2000000 /* 2MHz частота тактирования счетчика ШИМ */
/* Значение регистра автоперезагрузки (период повторения импульсов) для самолета */
#define RELOAD_PLANE  40000
/* Значение регистра автоперезагрузки (период повторения импульсов) для машинки */
#define RELOAD_CAR    SERVO_MAX

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

static const PWMConfig pwm1cfg = {
    PWM_FREQ,
    RELOAD_PLANE,
    NULL, //pwm1cb,
    {
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}
    },
    0,
};

static const PWMConfig pwm4cfg = {
    PWM_FREQ,
    RELOAD_PLANE,
    NULL,//pwm4cb,
    {
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}
    },
    0,
};

static const PWMConfig pwm1carcfg = {
    PWM_FREQ,
    RELOAD_CAR,
    NULL, //pwm1cb,
    {
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}
    },
    0,
};

/* конфиги для самолета */
static ServoConfig servo1cfg = { // TIM1
    &PWMD1,
    0,
    SERVO_MIN,
    SERVO_MAX,
    0,
    3000
};
static ServoConfig servo2cfg = {// TIM1
    &PWMD1,
		1,
		SERVO_MIN,
		SERVO_MAX,
		0,
		3000
};
static ServoConfig servo3cfg = { // TIM1
    &PWMD1,
    2,
    SERVO_MIN,
    SERVO_MAX,
    0,
    3000
};
static ServoConfig servo4cfg = {// TIM1
    &PWMD1,
    3,
    SERVO_MIN,
    SERVO_MAX,
    0,
    3000
};
static ServoConfig servo5cfg = { // TIM4
    &PWMD4,
    0,
    2000,
    4000,
    0,
    3000
};
static ServoConfig servo6cfg = {// TIM4
    &PWMD4,
    1,
    2000,
    4000,
    0,
    3000
};
static ServoConfig servo7cfg = { // TIM4
    &PWMD4,
    2,
    SERVO_MIN,
    SERVO_MAX,
    0,
    3000
};
static ServoConfig servo8cfg = {// TIM4
    &PWMD4,
    3,
    SERVO_MIN,
    SERVO_MAX,
    0,
    3000
};

/* конфиги для машинки */
static ServoConfig cartrottlecfg = { // TIM1
    &PWMD1,
    0,
    0,
    SERVO_MAX,
    0,
    0
};
static ServoConfig carbreakcfg = {// TIM1
    &PWMD1,
    1,
    0,
    SERVO_MAX,
    0,
    0
};

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
#define servo_refresh(scfg) \
  {pwmEnableChannel((scfg)->pwmp, (scfg)->pwmchannel, (scfg)->current);}

/**
 * Apply new settings to servo config.
 */
/*
static void servo_set_tune(ServoConfig *scfg, uint8_t *buf){
  uint8_t n = 0;

  scfg->min = (buf[n] << 8) + buf[n+1];
  n += 2;
  scfg->max = (buf[n] << 8) + buf[n+1];
  n += 2;
  scfg->neutral = (buf[n] << 8) + buf[n+1];
}
static void servo_get_tune(ServoConfig *scfg, uint8_t *buf){
  uint8_t n = 0;

  buf[n]   = (uint8_t)((scfg->min) >> 8);
  buf[n+1] = (uint8_t)((scfg->min) & 0xFF);
  n += 2;
  buf[n]   = (uint8_t)((scfg->max) >> 8);
  buf[n+1] = (uint8_t)((scfg->max) & 0xFF);
  n += 2;
  buf[n]   = (uint8_t)((scfg->neutral) >> 8);
  buf[n+1] = (uint8_t)((scfg->neutral) & 0xFF);
  n += 2;
}
*/

/**
 * Read settings from servo config to buffer.
 *//*
static void servo_get_tune_to_mavlink(void){
  servo_struct.servo1min     = servo1cfg.min;
  servo_struct.servo1max     = servo1cfg.max;
  servo_struct.servo1neutral = servo1cfg.neutral;
  servo_struct.servo2min     = servo2cfg.min;
  servo_struct.servo2max     = servo2cfg.max;
  servo_struct.servo2neutral = servo2cfg.neutral;
  servo_struct.servo3min     = servo3cfg.min;
  servo_struct.servo3max     = servo3cfg.max;
  servo_struct.servo3neutral = servo3cfg.neutral;
  servo_struct.servo4min     = servo4cfg.min;
  servo_struct.servo4max     = servo4cfg.max;
  servo_struct.servo4neutral = servo4cfg.neutral;
  servo_struct.servo5min     = servo5cfg.min;
  servo_struct.servo5max     = servo5cfg.max;
  servo_struct.servo5neutral = servo5cfg.neutral;
  servo_struct.servo6min     = servo6cfg.min;
  servo_struct.servo6max     = servo6cfg.max;
  servo_struct.servo6neutral = servo6cfg.neutral;
  servo_struct.servo7min     = servo7cfg.min;
  servo_struct.servo7max     = servo7cfg.max;
  servo_struct.servo7neutral = servo7cfg.neutral;
  servo_struct.servo8min     = servo8cfg.min;
  servo_struct.servo8max     = servo8cfg.max;
  servo_struct.servo8neutral = servo8cfg.neutral;
}*/

/*
 * Устанавливает угол сервы (поле current в структуре конфига)
 * Затем обновляет регистры счетчика. Новое значение вступает в силу
 * в следующий период счетчика.
 * [in] angle - то, что свалилось по каналу управления (1 байт)
 *      *scfg - указатель на нужную нам серву
 */
static void servo_set_angle(ServoConfig *scfg, uint8_t angle){
  uint16_t len = 0;
  /* Для реализации неравномерного расхода рулей диапазоны регулирования
   * разбиваются на 2 участка: выше середины и ниже середины. */
  if (angle > 128){
  	len = scfg->max - scfg->neutral;
  	scfg->current = scfg->neutral + (((len * angle) >> 7) - len);
  }
  else{
    len = scfg->neutral - scfg->min;
    scfg->current = scfg->neutral - (len - ((len * angle) >> 7));
  }

  /* refresh PWM */
  servo_refresh(scfg);
}

/**
 * Поток для обслуживания серв
 */
static WORKING_AREA(ServoThreadWA, 256);
static msg_t ServoThread(void *arg){
  chRegSetThreadName("Servo");
  (void)arg;

  while (TRUE) {
    chThdSleepMilliseconds(1000);
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/* для установки газа/тормоза машинки, размазанного на 2 канала */
void CarThrottle(uint8_t angle){
  uint8_t dz = 32; /* мертвая зона */
  uint32_t throttle = 0;
  uint32_t break_ = 0;

  throttle = __USAT((angle - (128 + dz/2)), 8);
  throttle = (throttle * SERVO_MAX) / (128 - dz/2);
  break_   = (SERVO_MAX * angle) / (128 - dz/2);
  break_   = __USAT((SERVO_MAX - break_), 16);

  cartrottlecfg.current = (uint16_t)(throttle & 0xFFFF);
  carbreakcfg.current   = (uint16_t)(break_   & 0xFFFF);

  servo_refresh(&cartrottlecfg);
  servo_refresh(&carbreakcfg);
}

/**
 * Устанавливает нейтральные значения
 */
void ServoNeutral(void){
  Servo1SetAngle(128);
  Servo2SetAngle(128);
  Servo3SetAngle(128);
  Servo4SetAngle(128);
  Servo5SetAngle(128);
  Servo6SetAngle(128);
  Servo7SetAngle(128);
  Servo8SetAngle(128);
}


void ServoInit(void){

  /* этот 2 строки нужны только чтобы избавиться от варнинга */
  pwmStart(&PWMD1, &pwm1carcfg);
  pwmStop(&PWMD1);

  /* по умолчанию ШИМы запускаются с самолетными конфигами */
	pwmStart(&PWMD1, &pwm1cfg);
	pwmStart(&PWMD4, &pwm4cfg);

	ServoNeutral();   /* запуск серв в нейтральном положении */

  chThdCreateStatic(ServoThreadWA,
          sizeof(ServoThreadWA),
          NORMALPRIO,
          ServoThread,
          NULL);
}

/* внешний API */
void Servo1SetAngle(uint8_t angle){
  servo_set_angle(&servo1cfg, angle);
  raw_data.servo1 = servo1cfg.current;
}
void Servo2SetAngle(uint8_t angle){
  servo_set_angle(&servo2cfg, angle);
  raw_data.servo2 = servo2cfg.current;
}
void Servo3SetAngle(uint8_t angle){
  servo_set_angle(&servo3cfg, angle);
  raw_data.servo3 = servo3cfg.current;
}
void Servo4SetAngle(uint8_t angle){
  servo_set_angle(&servo4cfg, angle);
  raw_data.servo4 = servo4cfg.current;
}
void Servo5SetAngle(uint8_t angle){
  servo_set_angle(&servo5cfg, angle);
  raw_data.servo5 = servo5cfg.current;
}
void Servo6SetAngle(uint8_t angle){
  servo_set_angle(&servo6cfg, angle);
  raw_data.servo6 = servo6cfg.current;
}
void Servo7SetAngle(uint8_t angle){
  servo_set_angle(&servo7cfg, angle);
  raw_data.servo7 = servo7cfg.current;
}
void Servo8SetAngle(uint8_t angle){
  servo_set_angle(&servo8cfg, angle);
  raw_data.servo8 = servo8cfg.current;
}
