#include "uav.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;
extern Mailbox tolink_mb;
extern Mailbox logwriter_mb;

extern mavlink_system_t       mavlink_system_struct;
extern mavlink_heartbeat_t    mavlink_heartbeat_struct;
extern mavlink_sys_status_t   mavlink_sys_status_struct;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

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
static WORKING_AREA(SanityControlThreadWA, 128);
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
    chThdSleepMilliseconds(950);

    /* fill data fields and send struct to message box */
    chBSemWaitTimeout(&sanity_sem, MS2ST(1));
    if (GlobalFlags & TLM_LINK_FLAG){
      mavlink_heartbeat_struct.type           = mavlink_system_struct.type;
      mavlink_heartbeat_struct.base_mode      = mavlink_system_struct.mode;
      mavlink_heartbeat_struct.system_status  = mavlink_system_struct.state;
      heartbeat_mail.payload = &mavlink_heartbeat_struct;
      chMBPost(&tolink_mb, (msg_t)&heartbeat_mail, TIME_IMMEDIATE);
    }
    chBSemSignal(&sanity_sem);

    if (chThdSelf()->p_epending & EVENT_MASK(LOGGER_READY_EVID))
      log_write_schedule(MAVLINK_MSG_ID_HEARTBEAT);

    palClearPad(GPIOB, GPIOB_LED_B); /* blink*/
    chThdSleepMilliseconds(50);
    mavlink_sys_status_struct.load = get_cpu_load();

    if (chThdSelf()->p_epending & EVENT_MASK(SIGHALT_EVID)){
      palClearPad(GPIOB, GPIOB_LED_B);
      palClearPad(GPIOB, GPIOB_LED_R);
      xbee_reset_assert();
      chThdExit(RDY_OK);
    }
  }
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void SanityControlInit(void){

  IdleThread_p = chSysGetIdleThread();

  chThdCreateStatic(SanityControlThreadWA,
          sizeof(SanityControlThreadWA),
          NORMALPRIO,
          SanityControlThread,
          NULL);
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
  else /* произошло переполнение */
    i = chThdGetTicks(IdleThread_p) + (0xFFFFFFFF - last_idle_ticks);
  /* обновляем счетчик */
    last_idle_ticks = chThdGetTicks(IdleThread_p);

  /* получаем мгновенное значение счетчика из системы */
  s = GetTimeInterval(&last_sys_ticks);

  return ((s - i) * 1000) / s;
}




