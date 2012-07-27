/*
 *      Для аналоговых серв ширина импульса должна быть
 *      в пределах 1000 - 2000 uS. Середина - 1500 uS.
 *      Период - 20 mS.
 */

#include "uav.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalParam_t global_data[];
extern mavlink_system_t mavlink_system_struct;

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

static const PWMConfig pwm1plane_cfg = {
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

static const PWMConfig pwm4plane_cfg = {
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

static const PWMConfig pwm1car_cfg = {
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
static int32_t servoblock_index = -1;

/* размер мертвой зоны, актуален только для ручного управления */
static uint32_t *car_dz;

/**/
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
 * @param[in]   n     номер сервы, нумерация с 0.
 * @param[in]   angle отклонение сервы в условных единицах 0..255
 */
void ServoSetAngle(uint16_t n, uint8_t angle){
  uint16_t len = 0;
  uint16_t min = 0;
  uint16_t max = 0;
  uint16_t neutral = 0;
  uint16_t val = 0;
  uint16_t i = servoblock_index + (n) * 3;

  min = global_data[i].value.u32 & 0xFFFF;
  max = global_data[i+1].value.u32 & 0xFFFF;
  neutral = global_data[i+2].value.u32 & 0xFFFF;

  if (angle > 128){
    len = max - neutral;
    val = neutral + (((len * angle) >> 7) - len);
  }
  else{
    len = neutral - min;
    val = neutral - (len - ((len * angle) >> 7));
  }
  pwmEnableChannel(servocfg_array[n].pwmp, servocfg_array[n].pwmchannel, val);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/* car throttle/break spreaded on 2 channels */
void ServoCarThrottleSet(uint8_t angle){
  uint32_t throttle = 0;
  uint32_t break_   = 0;
  uint8_t dz = 0;

  dz = (uint8_t)*car_dz;
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    throttle = __USAT((angle - (128 + dz/2)), 8);
    throttle = (throttle * SERVO_MAX) / (128 - dz/2);
    break_   = (SERVO_MAX * angle) / (128 - dz/2);
    break_   = __USAT((SERVO_MAX - break_), 16);

    Servo6Set((uint16_t)(throttle & 0xFFFF));
    Servo7Set((uint16_t)(break_   & 0xFFFF));
  }
  else
    return;
}

/**
 *
 */
void ServoNeutral(void){
  uint32_t i = 0;
  for (i = 0; i < SERVO_COUNT; i++)
    ServoSetAngle(i, 128);
}


void ServoInit(void){

  servoblock_index = _key_index_search("SERVO_1_min");
  if (servoblock_index == -1)
    chDbgPanic("key not found");

  car_dz = ValueSearch("SERVO_car_dz");

  /* this channel allways run in plane mode */
  pwmStart(&PWMD4, &pwm4plane_cfg);

  /* this in different modes */
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER)
    pwmStart(&PWMD1, &pwm1car_cfg);
  else
    pwmStart(&PWMD1, &pwm1plane_cfg);

	ServoNeutral();
}


