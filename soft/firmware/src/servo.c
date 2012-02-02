/*
 *      Для аналоговых серв ширина импульса должна быть
 *      в пределах 1000 - 2000 uS. Середина - 1500 uS.
 *      Период - 20 mS.
 */

#include "servo.h"
#include "message.h"
#include "main.h"
#include "eeprom.h"
#include "parameters.h"
#include "link.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalParam_t global_data[];
//extern Mailbox tolink_mb;
extern Mailbox manual_control_mb;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
/* Пример расчета:
   При частоте тактирования счетчика ШИМ 2МГц, период одного такта - 0.5мкс.
   Чтобы получить 20мс (стандартная частота сервоприводов) - надо в счетчик
   ШИМ загружать значение 20 * 1000 / 0.5 = 40000 */
#define PWM_FREQ      1000000 /* 1MHz частота тактирования счетчика ШИМ */
/* Значение регистра автоперезагрузки (период повторения импульсов) для самолета */
#define RELOAD_PLANE  20000
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

//static const PWMConfig pwm1carcfg = {
//    PWM_FREQ,
//    RELOAD_CAR,
//    NULL, //pwm1cb,
//    {
//      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
//      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
//      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
//      {PWM_OUTPUT_ACTIVE_HIGH, NULL}
//    },
//    0,
//};

/**
 * массив конфигов серв
 */
static const ServoConfig servocfg_array[] = {
    {&PWMD1, 0},
    {&PWMD1, 1},
    {&PWMD1, 2},
    {&PWMD1, 3},
    {&PWMD4, 0},
    {&PWMD4, 1},
    {&PWMD4, 2},
    {&PWMD4, 3},
};

/* смещение блока настроек серв в глобальном блоке настроек */
static int16_t servoblock_offset;
static uint16_t SERVO_COUNT = (sizeof(servocfg_array) / sizeof(ServoConfig));

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Рассчитывает значение, которое надо загрузить в регистры ШИМа
 * на основании зачений минимума, максимума и нейтрали
 * @param[in]   n     номер сервы, нумерация с 1.
 * @param[in]   angle отклонение сервы в условных единицах 0..255
 */
void ServoSetAngle(uint16_t n, uint8_t angle){
  uint16_t len = 0;
  uint16_t min = 0;
  uint16_t max = 0;
  uint16_t neutral = 0;
  uint16_t val = 0;
  uint16_t i = servoblock_offset + (n-1) * 3;

  min = global_data[i].value;
  max = global_data[i+1].value;
  neutral = global_data[i+2].value;

  if (angle > 128){
    len = max - neutral;
    val = neutral + (((len * angle) >> 7) - len);
  }
  else{
    len = neutral - min;
    val = neutral - (len - ((len * angle) >> 7));
  }
  pwmEnableChannel(servocfg_array[n-1].pwmp, servocfg_array[n-1].pwmchannel, val);
}

/**
 * Поток для обслуживания серв
 */
static WORKING_AREA(ServoThreadWA, 512);
static msg_t ServoThread(void *arg){
  chRegSetThreadName("Servo");
  (void)arg;
  msg_t tmp;
  mavlink_bart_manual_control_t *control = NULL;

  while (TRUE) {
    chMBFetch(&manual_control_mb, &tmp, TIME_INFINITE);
    control = (((Mail*)tmp)->payload);

    ServoSetAngle(1, control->servo1);
    ServoSetAngle(2, control->servo2);
    ServoSetAngle(3, control->servo3);
    ServoSetAngle(4, control->servo4);
    ServoSetAngle(5, control->servo5);
    ServoSetAngle(6, control->servo6);
    ServoSetAngle(7, control->servo7);
    ServoSetAngle(8, control->servo8);

    /* данные обработаны */
    ((Mail*)tmp)->payload = NULL;
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/* для установки газа/тормоза машинки, размазанного на 2 канала */
//void CarThrottle(uint8_t angle){
//  uint8_t dz = 32; /* мертвая зона */
//  uint32_t throttle = 0;
//  uint32_t break_ = 0;
//
//  throttle = __USAT((angle - (128 + dz/2)), 8);
//  throttle = (throttle * SERVO_MAX) / (128 - dz/2);
//  break_   = (SERVO_MAX * angle) / (128 - dz/2);
//  break_   = __USAT((SERVO_MAX - break_), 16);
//
//  cartrottlecfg.value = (uint16_t)(throttle & 0xFFFF);
//  carbreakcfg.value   = (uint16_t)(break_   & 0xFFFF);
//
//  servo_refresh(&cartrottlecfg);
//  servo_refresh(&carbreakcfg);
//}

/**
 * Устанавливает нейтральные значения
 */
void ServoNeutral(void){
  uint32_t i = 0;
  for (i = 1; i < SERVO_COUNT+1; i++)
    ServoSetAngle(i, 128);
}


void ServoInit(void){

  /* determine offset */
  servoblock_offset = key_value_search("SERVO_1_min", global_data);
  if (servoblock_offset == -1)
    chDbgPanic("key not found");

  /* эти 2 строки нужны только чтобы избавиться от варнинга */
//  pwmStart(&PWMD1, &pwm1carcfg);
//  pwmStop(&PWMD1);

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


