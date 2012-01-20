#define AIRPLANE_MODE    FALSE

/*
 *      Для аналоговых серв ширина импульса должна быть
 *      в пределах 1.0 - 2.0 мс. Середина - 1.5 мс.
 *      Период - 20 мс.
 */

#include "servo.h"
#include "message.h"
#include "main.h"
#include "eeprom.h"
#include "irq_storm.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern LogItem log_item;
extern BinarySemaphore link_thd_sem;
extern Mailbox eeprommanager_mb;
extern Mailbox tolink_mb;

extern uint8_t servo_settings_xbee_buf[SERVO_SETTINGS_SIZE];
extern uint8_t servo_settings_eeprom_buf[SERVO_SETTINGS_SIZE];



/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
#define AILERONP  (&(servo0cfg))
#define ELEVATORP (&(servo1cfg))
#define RUDDERP   (&(servo2cfg))
#define THROTTLEP (&(motorcfg))

// смещения данных в eeprom для каждой сервы относительно начала блока серв в блоке настроек
#define AILERON_OFFSET  0
#define ELEVATOR_OFFSET (AILERON_OFFSET  + EEPROM_SERVO_SIZE)
#define RUDDER_OFFSET   (ELEVATOR_OFFSET + EEPROM_SERVO_SIZE)
#define THROTTLE_OFFSET (RUDDER_OFFSET   + EEPROM_SERVO_SIZE)

//#define SERVO_MIN_LIMIT 2000
//#define SERVO_MAX_LIMIT 4000
#define SERVO_MIN_LIMIT 0UL
#define SERVO_MAX_LIMIT RELOAD_VAL

// периодичность проверки наличия новых данных для серв
#define SERVOSAVE_PERIOD 1000

#if AIRPLANE_MODE
static ServoConfig motorcfg = { // TIM3
    &PWMD3,
    2,
    2000,
    4000,
    0,
    3000
};

static ServoConfig servo0cfg = {// TIM3
    &PWMD3,
		3,
    2000,
    4000,
		0,
		3000
};
#else /* AIRPLANE_MODE */
static ServoConfig motorcfg = { // TIM3
    &PWMD3,
    2,
    SERVO_MIN_LIMIT,
    SERVO_MAX_LIMIT,
    0,
    3000
};

static ServoConfig servo0cfg = {// TIM3
    &PWMD3,
    3,
    SERVO_MIN_LIMIT,
    SERVO_MAX_LIMIT,
    0,
    3000
};
#endif /* AIRPLANE_MODE */

static ServoConfig servo1cfg = { // TIM4
    &PWMD4,
		2,
    2000,
    4000,
		0,
		3000
};

static ServoConfig servo2cfg = { // TIM4
    &PWMD4,
		3,
		2000,
		4000,
		0,
		3000
};


// массив указателей не конфиги серв для упрощения применения настроек
static ServoConfig *servo_cfg_array[4] = {AILERONP, ELEVATORP, RUDDERP, THROTTLEP};

/* Флаговый регистр.
 * биты:
 * 0 -- 1 означает, что свалились новые коэффициенты, которые прошли валидацию, но еще не записаны в EEPROM
 * 1 -- 1 означает, что в настоящий момент данные вычитываются из EEPROM
 * 2 --
 * 3 --*/
static uint8_t servo_flags = 0;
static VirtualTimer servosave_vt;                             // таймер для отложенной записи настроек серв в EEPROM
static EepromReq eeprom_servo_req = {
    NULL,
    NULL,
    SERVO_SETTINGS_SIZE,
    EEPROM_SERVO_OFFSET
};


/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

static uint32_t oddcheck; // счетчик для делителя частоты отправления данных
#define DIVIDER 1
// Коллбэк вызывается, когда счетчик досчитывает до нуля
inline static void pwm3cb(PWMDriver *pwmp){
	(void)pwmp;
	oddcheck++;
	if((oddcheck & (DIVIDER - 1)) == (DIVIDER - 1)){
	  chSysLockFromIsr();
	  chBSemSignalI(&link_thd_sem);// пробуждение потока отправки сообщения
	  chSysUnlockFromIsr();
	}
}


// Struct with settings for PWM
const PWMConfig pwm3cfg = {
    PWM_FREQ,
    RELOAD_VAL,
    pwm3cb,
    {
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}
    },
    0,
#if STM32_PWM_USE_ADVANCED
    0
#endif
};


// Struct with settings for PWM
const PWMConfig pwm4cfg = {
    PWM_FREQ,
    RELOAD_VAL,
    NULL,//pwm4cb,
    {
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL},
      {PWM_OUTPUT_ACTIVE_HIGH, NULL}
    },
    0,
#if STM32_PWM_USE_ADVANCED
    0
#endif
};



static void servosave_vt_cb(void *par){
  (void)par;
  chVTSetI(&servosave_vt, MS2ST(SERVOSAVE_PERIOD), &servosave_vt_cb, NULL);

  if((servo_flags & 0x01) != 0x01) // свежака нету
    return;
  if(eeprom_servo_req.bufp != 0) // EEPROM еще не обработал старые данные
    return;
  else{
    eeprom_servo_req.bufp = servo_settings_xbee_buf;
    eeprom_servo_req.len  = SERVO_SETTINGS_SIZE;
    eeprom_servo_req.addr = EEPROM_SERVO_OFFSET;
    chMBPostI(&eeprommanager_mb, (msg_t)&eeprom_servo_req);   /* отправка запроса на запись*/
    servo_flags &= ~(0x01);
  }
}

/**
 * Вычитывает данные из EEPROM в буфер
 * @param [in] указатель на буфер, в который надо сложить данные
 * @return статус завершения
 */
uint8_t Servo_ReadFromEeprom(uint8_t *buf){
  msg_t status;
  int8_t timeout = 16;

  eeprom_servo_req.bufp = buf;
  eeprom_servo_req.len  = SERVO_SETTINGS_SIZE | 0x8000; // установим бит чтения
  eeprom_servo_req.addr = EEPROM_SERVO_OFFSET;
  status = chMBPost(&eeprommanager_mb, (msg_t)&eeprom_servo_req, MS2ST(2000));   /* отправка запроса на чтение */
  if (status != RDY_OK){
    return 1;
  }
  else{
    while(eeprom_servo_req.bufp != 0 && timeout > 0){
      chThdSleepMilliseconds(1);
      timeout--;
    }
    if (timeout > 0)
      return 0;
    else
      return 1;
  }
}

/**
 * Берет из буфера данные, проверяет их на вшивость.
 * Если проверка пройдена - загружает в структуры серв калибровочные коээфициенты
 *
 * @param buf -- указатель на буфер с коэффициентами для серв
 * @param eeprom_refresh -- если TRUE, значит надо обновить значения в EEPROM
 */
#if AIRPLANE_MODE
static uint8_t Servo_SettingsApply(uint8_t *buf, bool_t eeprom_refresh){
  uint8_t i = 0, status = 0, n = 0;
  pwmcnt_t tmp = 0;

  for (i = 0; i<4; i++){
    /* min */
    n = i * 6;
    tmp = (buf[n] << 8) + buf[n+1];
    if((tmp < SERVO_MIN_LIMIT) || (tmp > SERVO_MAX_LIMIT)){
      servo_cfg_array[i]->min = SERVO_MIN_LIMIT;
      status++;
    }
    else
      servo_cfg_array[i]->min = tmp;

    /* max */
    n += 2;
    tmp = (buf[n] << 8) + buf[n+1];
    if( (tmp < (servo_cfg_array[i]->min)) || (tmp > SERVO_MAX_LIMIT) ){
      servo_cfg_array[i]->max = SERVO_MAX_LIMIT;
      status++;
    }
    else
      servo_cfg_array[i]->max = tmp;

    /* neutral */
    n += 2;
    tmp = (buf[n] << 8) + buf[n+1];
    if ( (tmp < servo_cfg_array[i]->min) || (tmp > servo_cfg_array[i]->max)){
      servo_cfg_array[i]->neutral = (servo_cfg_array[i]->max + servo_cfg_array[i]->min) / 2;
      status++;
    }
    else
      servo_cfg_array[i]->neutral = tmp;
  }

  if (status == 0){/* валидация пройдена */
    for(i = 0; i<SERVO_SETTINGS_SIZE; i++){
      servo_settings_xbee_buf[i] = buf[i];}
    if (eeprom_refresh)
      servo_flags |= 0x01;
  }

  return status;
}

#else /* AIRPLANE_MODE */
uint8_t Servo_SettingsApply(uint8_t *buf, bool_t eeprom_refresh){
  uint8_t i = 0, status = 0, n = 0;

  for (i = 0; i<4; i++){
    n = i * 6;
    servo_cfg_array[i]->min = (buf[n] << 8) + buf[n+1];           /* min */
    n += 2;
    servo_cfg_array[i]->max = (buf[n] << 8) + buf[n+1];           /* max */
    n += 2;
    servo_cfg_array[i]->neutral = (buf[n] << 8) + buf[n+1];       /* neutral */
  }

  for(i = 0; i<SERVO_SETTINGS_SIZE; i++){
    servo_settings_xbee_buf[i] = buf[i];}
  if (eeprom_refresh)
    servo_flags |= 0x01;

  return status;
}
#endif /* AIRPLANE_MODE */


/*
 * Устанавливает угол сервы
 * [in] angle - то, что свалилось по каналу управления (1 байт)
 *      *servop - указатель на нужную нам серву
 */
static void Servo_AngleCalc(uint8_t angle, ServoConfig *servop){
  uint16_t len = 0;
  /* Для реализации неравномерного расхода рулей диапазоны регулирования
   * разбиваются на 2 участка: выше середины и ниже середины. */
  if (angle > 128){
  	len = servop->max - servop->neutral;
  	servop->current = servop->neutral + (((len * angle) >> 7) - len);
  }
  else{
    len = servop->neutral - servop->min;
    servop->current = servop->neutral - (len - ((len * angle) >> 7));
  }
  // старый код для равномерного расхода рулей
  //servop->angle = servop->min + (((servop->max - servop->min) * angle) / 0xFF);
}

/* Освежение значений в регистрах ШИМов */
#define Servo_refresh(servop){                                                \
  pwmEnableChannel(servop->pwmp, servop->pwmchannel, servop->current);        \
}

void set_elevator(uint8_t angle){
  Servo_AngleCalc(angle, ELEVATORP);
  Servo_refresh(ELEVATORP);
  raw_data.elevator = ELEVATORP->current;
  log_item.elevator = ELEVATORP->current;
}
void set_rudder(uint8_t angle){
  Servo_AngleCalc(angle, RUDDERP);
  Servo_refresh(RUDDERP);
  raw_data.rudder = RUDDERP->current;
  log_item.rudder = RUDDERP->current;
}
#if AIRPLANE_MODE
void set_aileron(uint8_t angle){
  Servo_AngleCalc(angle, AILERONP);
  Servo_refresh(AILERONP);
  raw_data.aileron = AILERONP->current;
  log_item.aileron = AILERONP->current;
}
void set_throttle(uint8_t angle){
  Servo_AngleCalc(angle, THROTTLEP);
  Servo_refresh(THROTTLEP);
  raw_data.throttle = THROTTLEP->current;
  log_item.throttle = THROTTLEP->current;
}
#else
void set_aileron(uint8_t angle){
  (void)angle;
}
void set_throttle(uint8_t angle){
  uint8_t dz = 32; /* мертвая зона */
  uint32_t throttle = 0;
  uint32_t break_ = 0;

  throttle = __USAT((angle - (128 + dz/2)), 8);
  throttle = (throttle * SERVO_MAX_LIMIT) / (128 - dz/2);
  break_ = (SERVO_MAX_LIMIT * angle) / (128 - dz/2);
  break_ = __USAT((SERVO_MAX_LIMIT - break_), 16);

  THROTTLEP->current = (uint16_t)(throttle & 0xFFFF);
  AILERONP->current  = (uint16_t)(break_   & 0xFFFF);

  Servo_refresh(THROTTLEP);
  Servo_refresh(AILERONP);

  raw_data.throttle = THROTTLEP->current;
  log_item.throttle = THROTTLEP->current;
  raw_data.aileron  = AILERONP->current;
  log_item.aileron  = AILERONP->current;
}
#endif

/**
 * Устанавливает нейтральные значения
 */
inline void Servo_NeutralSet(void){
  set_aileron (128);
  set_elevator(128);
#if AIRPLANE_MODE
  set_throttle(0);
#else
  set_throttle(128);
#endif
  set_rudder  (128);
}


inline void ServoInit(){
  msg_t status = 0;

  status = Servo_ReadFromEeprom(servo_settings_eeprom_buf);
  chDbgCheck((status == 0), "can not read servo settings from EEPROM");

  Servo_SettingsApply(servo_settings_eeprom_buf, FALSE);

	pwmStart(&PWMD3, &pwm3cfg);
	pwmStart(&PWMD4, &pwm4cfg);

	Servo_NeutralSet();   /* настройка серв на нейтральное положение */

  Servo_refresh(ELEVATORP);
  Servo_refresh(THROTTLEP);
  Servo_refresh(RUDDERP);
  Servo_refresh(AILERONP);

  chSysLock();
  chVTSetI(&servosave_vt, MS2ST(SERVOSAVE_PERIOD), &servosave_vt_cb, NULL);
  chSysUnlock();
}


