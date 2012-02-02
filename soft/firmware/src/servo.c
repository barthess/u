/*
 *      ��� ���������� ���� ������ �������� ������ ����
 *      � �������� 1000 - 2000 uS. �������� - 1500 uS.
 *      ������ - 20 mS.
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
/* ������ �������:
   ��� ������� ������������ �������� ��� 2���, ������ ������ ����� - 0.5���.
   ����� �������� 20�� (����������� ������� �������������) - ���� � �������
   ��� ��������� �������� 20 * 1000 / 0.5 = 40000 */
#define PWM_FREQ      1000000 /* 1MHz ������� ������������ �������� ��� */
/* �������� �������� ���������������� (������ ���������� ���������) ��� �������� */
#define RELOAD_PLANE  20000
/* �������� �������� ���������������� (������ ���������� ���������) ��� ������� */
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
 * ������ �������� ����
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

/* �������� ����� �������� ���� � ���������� ����� �������� */
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
 * ������������ ��������, ������� ���� ��������� � �������� ����
 * �� ��������� ������� ��������, ��������� � ��������
 * @param[in]   n     ����� �����, ��������� � 1.
 * @param[in]   angle ���������� ����� � �������� �������� 0..255
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
 * ����� ��� ������������ ����
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

    /* ������ ���������� */
    ((Mail*)tmp)->payload = NULL;
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/* ��� ��������� ����/������� �������, ������������ �� 2 ������ */
//void CarThrottle(uint8_t angle){
//  uint8_t dz = 32; /* ������� ���� */
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
 * ������������� ����������� ��������
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

  /* ��� 2 ������ ����� ������ ����� ���������� �� �������� */
//  pwmStart(&PWMD1, &pwm1carcfg);
//  pwmStop(&PWMD1);

  /* �� ��������� ���� ����������� � ����������� ��������� */
	pwmStart(&PWMD1, &pwm1cfg);
	pwmStart(&PWMD4, &pwm4cfg);

	ServoNeutral();   /* ������ ���� � ����������� ��������� */

  chThdCreateStatic(ServoThreadWA,
          sizeof(ServoThreadWA),
          NORMALPRIO,
          ServoThread,
          NULL);
}


