/*
 *      Для аналоговых серв ширина импульса должна быть
 *      в пределах 1000 - 2000 uS. Середина - 1500 uS.
 *      Период - 20 mS.
 */

#include "uav.h"
#include "global_flags.h"
#include "message.hpp"
#include "servo.hpp"
#include "param_registry.hpp"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern ParamRegistry param_registry;

extern mavlink_system_t mavlink_system_struct;
extern chibios_rt::BinarySemaphore servo_updated_sem;

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

/**/
//#define SERVO_COUNT = (sizeof(servocfg_array) / sizeof(ServoConfig));

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */
static void pwm4plane_cb(PWMDriver *pwmp);

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
    pwm4plane_cb,//callback,
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
static ServoConfig servocfg_array[] = {
    {&PWMD1, 0, NULL, NULL, NULL},
    {&PWMD1, 1, NULL, NULL, NULL},
    {&PWMD1, 2, NULL, NULL, NULL},
    {&PWMD1, 3, NULL, NULL, NULL},
    {&PWMD4, 0, NULL, NULL, NULL},
    {&PWMD4, 1, NULL, NULL, NULL},
    {&PWMD4, 2, NULL, NULL, NULL},
    {&PWMD4, 3, NULL, NULL, NULL},
};

/* размер мертвой зоны, актуален только для ручного управления */
static uint32_t const *car_dz;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Sincronize PID with servo update cycle.
 */
static void pwm4plane_cb(PWMDriver *pwmp){
  (void)pwmp;
  chSysLockFromIsr();
  servo_updated_sem.signalI();
  chSysUnlockFromIsr();
}

/**
 * Рассчитывает значение, которое надо загрузить в регистры ШИМа
 * на основании зачений минимума, максимума и нейтрали
 * @param[in]   n     номер сервы, нумерация с 0.
 * @param[in]   angle отклонение сервы в условных единицах 0..255
 */
static void _servo_set_angle(uint16_t i, uint8_t angle){
  uint16_t len = 0;
  uint16_t min = 0;
  uint16_t max = 0;
  uint16_t neutral = 0;
  uint16_t val = 0;

  min = *(servocfg_array[i].min);
  max = *(servocfg_array[i].max);
  neutral = *(servocfg_array[i].neutr);

  if (angle > 128){
    len = max - neutral;
    val = neutral + (((len * angle) >> 7) - len);
  }
  else{
    len = neutral - min;
    val = neutral - (len - ((len * angle) >> 7));
  }
  pwmEnableChannel(servocfg_array[i].pwmp, servocfg_array[i].pwmchannel, val);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

void Servo0Set(uint8_t angle) {
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    chDbgPanic("This fucntion can not be called in ground rover mode");
  }
  else{
    _servo_set_angle(0, angle);
  }
}

void Servo1Set(uint8_t angle) {
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    chDbgPanic("This fucntion can not be called in ground rover mode");
  }
  else{
    _servo_set_angle(1, angle);
  }
}

void Servo2Set(uint8_t angle) {
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    chDbgPanic("This fucntion can not be called in ground rover mode");
  }
  else{
    _servo_set_angle(2, angle);
  }
}

void Servo3Set(uint8_t angle) {
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    chDbgPanic("This fucntion can not be called in ground rover mode");
  }
  else{
    _servo_set_angle(3, angle);
  }
}

void Servo4Set(uint8_t angle) {
  _servo_set_angle(4, angle);
}

void Servo5Set(uint8_t angle) {
  _servo_set_angle(5, angle);
}

void Servo6Set(uint8_t angle) {
  _servo_set_angle(6, angle);
}

void Servo7Set(uint8_t angle) {
  _servo_set_angle(7, angle);
}

/* car throttle/break spreaded on 2 channels */
void ServoCarThrustSet(uint8_t angle){
  uint32_t throttle = 0;
  uint32_t break_   = 0;
  uint8_t dz = 0;

  dz = (uint8_t)*car_dz;
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER){
    throttle = __USAT((angle - (128 + dz/2)), 8);
    throttle = (throttle * SERVO_MAX) / (128 - dz/2);
    break_   = (SERVO_MAX * angle) / (128 - dz/2);
    break_   = __USAT((SERVO_MAX - break_), 16);

    pwmEnableChannel(servocfg_array[0].pwmp, servocfg_array[0].pwmchannel, 0);
    pwmEnableChannel(servocfg_array[1].pwmp, servocfg_array[1].pwmchannel, 0);
    pwmEnableChannel(servocfg_array[2].pwmp, servocfg_array[2].pwmchannel, (uint16_t)(throttle & 0xFFFF));
    pwmEnableChannel(servocfg_array[3].pwmp, servocfg_array[3].pwmchannel, (uint16_t)(break_   & 0xFFFF));

//    Servo6Set((uint16_t)(throttle & 0xFFFF));
//    Servo7Set((uint16_t)(break_   & 0xFFFF));
  }
  else
    chDbgPanic("This fucntion can not be called in fixed wing mode");
}

/**
 *
 */
void ServoInit(void){

  chDbgCheck(GlobalFlags.parameters_loaded == 1, "parameters not ready");

  char key_min[]   = "SERVO_0_min";
  char key_max[]   = "SERVO_0_max";
  char key_neutr[] = "SERVO_0_neutr";

  const uint8_t len = sizeof(servocfg_array) / sizeof(servocfg_array[0]);
  uint8_t i = 0;
  for (i=0; i<len; i++){
    key_min[6]   = i + '0';
    key_max[6]   = i + '0';
    key_neutr[6] = i + '0';
    servocfg_array[i].min   = (const uint16_t*)param_registry.valueSearch(key_min);
    servocfg_array[i].max   = (const uint16_t*)param_registry.valueSearch(key_max);
    servocfg_array[i].neutr = (const uint16_t*)param_registry.valueSearch(key_neutr);
  }

  car_dz = (const uint32_t*)param_registry.valueSearch("SERVO_car_dz");

  /* this channel can be run in different modes (plane and rover) */
  if (mavlink_system_struct.type == MAV_TYPE_GROUND_ROVER)
    pwmStart(&PWMD1, &pwm1car_cfg);
  else
    pwmStart(&PWMD1, &pwm1plane_cfg);

  /* this channel allways run in plane mode. It must be started _after_
   * PWM1 because of syncronization PID with them. */
  pwmStart(&PWMD4, &pwm4plane_cfg);
}


