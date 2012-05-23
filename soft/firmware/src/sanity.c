
/* ������ �� ���������� �������� �������.*/

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"
#include "link.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;
extern uint32_t GlobalFlags;
extern EventSource pwrmgmt_event;
extern mavlink_system_t mavlink_system_struct;

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
/* ��������� �� Idle �����. ������ �� ����� ����� ������ ��� ������� �������� ����� */
static Thread *IdleThread_p = NULL;

/* ���������� ��� ������ ������������� ���������� */
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
 * �������� heartbeat ������ � ������� �������������
 */
static WORKING_AREA(SanityControlThreadWA, 256);
static msg_t SanityControlThread(void *arg) {
  chRegSetThreadName("Sanity");
  (void)arg;

  struct EventListener self_el;
  chEvtRegister(&pwrmgmt_event, &self_el, PWRMGMT_SIGHALT_EVID);

  mavlink_heartbeat_t mavlink_heartbeat_struct;
  Mail heartbeat_mail = {NULL, MAVLINK_MSG_ID_HEARTBEAT, NULL};

  mavlink_heartbeat_struct.autopilot = MAV_AUTOPILOT_GENERIC;
  mavlink_heartbeat_struct.type = mavlink_system_struct.type;
  mavlink_heartbeat_struct.custom_mode = 0;

  while (TRUE) {
    palSetPad(GPIOB, GPIOB_LED_B);
    chThdSleepMilliseconds(950);

    if (heartbeat_mail.payload == NULL){
      mavlink_heartbeat_struct.base_mode = mavlink_system_struct.mode;
      mavlink_heartbeat_struct.system_status = mavlink_system_struct.state;
      heartbeat_mail.payload = &mavlink_heartbeat_struct;
      chMBPost(&tolink_mb, (msg_t)&heartbeat_mail, TIME_IMMEDIATE);

      palClearPad(GPIOB, GPIOB_LED_B); /* blink*/
      chThdSleepMilliseconds(50);
    }

    /* ���� ����������� ����� ���������� ������� �������� ���������� */
    if (GlobalFlags & GYRO_CAL_FLAG)
      palClearPad(GPIOB, GPIOB_LED_R);
    else
      palSetPad(GPIOB, GPIOB_LED_R);

    if (chThdSelf()->p_epending & EVENT_MASK(PWRMGMT_SIGHALT_EVID)){
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
 * ������������ �������� �����.
 * ���������� ������� ���� ��������.
 */
uint16_t get_cpu_load(void){

  uint32_t i, s; /* "����������" �������� ���������� ����� idle, system */

  /* �������� ���������� �������� �������� �� Idle */
  if (chThdGetTicks(IdleThread_p) >= last_idle_ticks)
    i = chThdGetTicks(IdleThread_p) - last_idle_ticks;
  else /* ��������� ������������ */
    i = chThdGetTicks(IdleThread_p) + (0xFFFFFFFF - last_idle_ticks);

  /* �������� ���������� �������� �������� �� ������� */
  if (chTimeNow() >= last_sys_ticks)
    s = chTimeNow() - last_sys_ticks;
  else /* ��������� ������������ */
    s = chTimeNow() + (0xFFFFFFFF - last_sys_ticks);

  /* ��������� �������� */
  last_idle_ticks = chThdGetTicks(IdleThread_p);
  last_sys_ticks = chTimeNow();

  return ((s - i) * 1000) / s;
}




