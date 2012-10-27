#include "uav.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern Mailbox tolink_mb;

extern mavlink_system_t       mavlink_system_struct;
extern mavlink_heartbeat_t    mavlink_heartbeat_struct;
extern mavlink_sys_status_t   mavlink_sys_status_struct;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define HEART_BEAT_PERIOD   MS2ST(1000)

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* указатель на Idle поток. Оттуда мы будем брать данные для расчета загрузки проца */
static Thread *IdleThread_p = NULL;

/* переменные для оценки загруженности процессора */
static uint32_t last_sys_ticks = 0;
static uint32_t last_idle_ticks = 0;

static BinarySemaphore blink_sem;
static uint32_t BlinkCnt = 0;
static systime_t offtime = 10, ontime = 10;

/* timer for RPM counting */
static VirtualTimer haltdisarm_vt;

/* how much time led is ON during one period */
static systime_t led_flash_time;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * посылает heartbeat пакеты и моргает светодиодиком
 */
static WORKING_AREA(SanityControlThreadWA, 80);
static msg_t SanityControlThread(void *arg) {
  chRegSetThreadName("Sanity");
  (void)arg;

  BinarySemaphore sanity_sem;     /* to sync with tlm sender */
  chBSemInit(&sanity_sem, FALSE); /* semaphore is not taken */

  Mail heartbeat_mail = {NULL, MAVLINK_MSG_ID_HEARTBEAT, &sanity_sem};

  mavlink_heartbeat_struct.autopilot = MAV_AUTOPILOT_GENERIC;
  mavlink_heartbeat_struct.custom_mode = 0;

  while (TRUE) {
    palSetPad(GPIOB, GPIOB_LED_B);
    chThdSleep(HEART_BEAT_PERIOD - led_flash_time);

    /* fill data fields and send struct to message box */
    chBSemWaitTimeout(&sanity_sem, MS2ST(1));
    if (GlobalFlags.tlm_link_ready){
      mavlink_heartbeat_struct.type           = mavlink_system_struct.type;
      mavlink_heartbeat_struct.base_mode      = mavlink_system_struct.mode;
      mavlink_heartbeat_struct.system_status  = mavlink_system_struct.state;
      heartbeat_mail.payload = &mavlink_heartbeat_struct;
      chMBPost(&tolink_mb, (msg_t)&heartbeat_mail, TIME_IMMEDIATE);
    }
    chBSemSignal(&sanity_sem);
    log_write_schedule(MAVLINK_MSG_ID_HEARTBEAT, NULL, 0);

    palClearPad(GPIOB, GPIOB_LED_B); /* blink*/
    chThdSleep(led_flash_time);
    mavlink_sys_status_struct.load = get_cpu_load();

    if (GlobalFlags.sighalt){
      palClearPad(GPIOB, GPIOB_LED_B);
      palClearPad(GPIOB, GPIOB_LED_R);
      xbee_reset_assert();
      chThdExit(RDY_OK);
    }
  }
  return 0;
}

/**
 * Blinker thread for red LED.
 */
static WORKING_AREA(RedBlinkThreadWA, 48);
static msg_t RedBlinkThread(void *arg) {
  chRegSetThreadName("RedBlink");
  (void)arg;

  while(TRUE){
    chBSemWait(&blink_sem);
    while(BlinkCnt){
      palClearPad(GPIOB, GPIOB_LED_R);
      chThdSleep(ontime);
      palSetPad(GPIOB, GPIOB_LED_R);
      chThdSleep(offtime);
      BlinkCnt--;
    }
  }
  return 0;
}

/**
 * Disarm halting on panic and changing it to soft reset.
 * Note. This functions is for using only in case of emergency in autonomouse flight.
 */
static void haltdisarm_vt_cb(void *par){
  (void)par;
  chSysLockFromIsr();
  setGlobalFlagI(GlobalFlags.allow_softreset);
  chSysUnlockFromIsr();
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
void SanityControlInit(void){

  if (was_softreset())
    led_flash_time = MS2ST(850);  /* error flash time */
  else
    led_flash_time = MS2ST(50);   /* normal flash time */

  chBSemInit(&blink_sem,  TRUE);
  IdleThread_p = chSysGetIdleThread();
  chThdCreateStatic(SanityControlThreadWA,
          sizeof(SanityControlThreadWA),
          NORMALPRIO,
          SanityControlThread,
          NULL);
  chThdCreateStatic(RedBlinkThreadWA,
          sizeof(RedBlinkThreadWA),
          NORMALPRIO - 10,
          RedBlinkThread,
          NULL);

  /* start virtual timer for panic halt disarmig */
  chSysLock();
  chVTSetI(&haltdisarm_vt, S2ST(HALT_DISARM_TMO_SEC), &haltdisarm_vt_cb, NULL);
  chSysUnlock();

  /* write "message" to log */
  if (was_softreset())
    bkpSoftResetCnt++;
}

/**
 * Schedule blink sequence.
 * [in] count of blinks and time intervals in sytem ticks
 */
void SheduleBlink(uint32_t cnt, uint32_t on, uint32_t off){
  const systime_t max = MS2ST(500);

  chSysLock()
  if (off > max)
    offtime = max;
  else
    offtime = off;
  if (on > max)
    ontime = max;
  else
    ontime = on;
  BlinkCnt = cnt;
  chSysUnlock();

  chBSemSignal(&blink_sem);
}

/**
 * Рассчитывает загрузку проца.
 * Возвращает десятые доли процента.
 */
uint16_t get_cpu_load(void){

  uint32_t i, s; /* "мгновенные" значения количества тиков idle, system */

  /* получаем мгновенное значение счетчика из Idle */
  if (chThdGetTicks(IdleThread_p) >= last_idle_ticks)
    i = chThdGetTicks(IdleThread_p) - last_idle_ticks;
  else /* overflow */
    i = chThdGetTicks(IdleThread_p) + (0xFFFFFFFF - last_idle_ticks);

  last_idle_ticks = chThdGetTicks(IdleThread_p);

  /* получаем мгновенное значение счетчика из системы */
  s = GetTimeInterval(&last_sys_ticks);

  return ((s - i) * 1000) / s;
}

