
#include "uav.h"
#include "global_flags.h"
#include "fault_handlers.h"

#include "message.hpp"
#include "timekeeping.hpp"
#include "bkp.hpp"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern uint32_t LastResetFlags;

extern mavlink_system_t       mavlink_system_struct;
extern mavlink_heartbeat_t    mavlink_out_heartbeat_struct;
extern mavlink_sys_status_t   mavlink_out_sys_status_struct;

extern EventSource event_mavlink_out_heartbeat;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define HEART_BEAT_PERIOD   MS2ST(1000)

/* how much time led is ON during flash */
#define BLUE_LED_ON_TIME    MS2ST(50)
#define BLUE_LED_OFF_TIME   MS2ST(100)

#define SYS_STATUS_3D_GYRO    ((uint32_t)1 << 0) /* for stub */
#define SYS_STATUS_3D_ACCEL   ((uint32_t)1 << 1) /* for stub */
#define SYS_STATUS_3D_MAG     ((uint32_t)1 << 2) /* for stub */
#define SYS_STATUS_ABS_PRES   ((uint32_t)1 << 3) /* for stub */
#define SYS_STATUS_DIFF_PRES  ((uint32_t)1 << 4) /* for stub */
#define SYS_STATUS_GPS        ((uint32_t)1 << 5) /* for stub */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static chibios_rt::BinarySemaphore blink_sem(true);
static uint32_t BlinkCnt = 0;
static systime_t offtime = 10, ontime = 10;

static uint32_t BlinksCount;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

static void blue_blinker(void){
  uint32_t n = BlinksCount;
  while (n > 0){
    palClearPad(GPIOB, GPIOB_LED_B); /* blink*/
    chThdSleep(BLUE_LED_ON_TIME);
    palSetPad(GPIOB, GPIOB_LED_B);
    chThdSleep(BLUE_LED_OFF_TIME);
    n--;
  }
}

/**
 * посылает heartbeat пакеты и моргает светодиодиком
 */
static WORKING_AREA(SanityControlThreadWA, 128);
__attribute__ ((__noreturn__))
static msg_t SanityControlThread(void *arg) {
  chRegSetThreadName("Sanity");
  (void)arg;

  mavlink_out_heartbeat_struct.autopilot = MAV_AUTOPILOT_GENERIC;
  mavlink_out_heartbeat_struct.custom_mode = 0;

  systime_t t = chTimeNow();

  while (TRUE) {
    t += HEART_BEAT_PERIOD;

    /* fill data fields */
    if (GlobalFlags.tlm_link_ready){
      mavlink_out_heartbeat_struct.type           = mavlink_system_struct.type;
      mavlink_out_heartbeat_struct.base_mode      = mavlink_system_struct.mode;
      mavlink_out_heartbeat_struct.system_status  = mavlink_system_struct.state;
      chEvtBroadcastFlags(&event_mavlink_out_heartbeat, EVMSK_MAVLINK_OUT_HEARTBEAT);

      /* stub */
      mavlink_out_sys_status_struct.onboard_control_sensors_present = (
              SYS_STATUS_3D_GYRO | SYS_STATUS_3D_ACCEL | SYS_STATUS_3D_MAG |
              SYS_STATUS_ABS_PRES | SYS_STATUS_DIFF_PRES | SYS_STATUS_GPS);
      mavlink_out_sys_status_struct.onboard_control_sensors_enabled = mavlink_out_sys_status_struct.onboard_control_sensors_present;
      mavlink_out_sys_status_struct.onboard_control_sensors_health  = mavlink_out_sys_status_struct.onboard_control_sensors_present;
    }

    chDbgPanic("uncomment next line");
    //log_write_schedule(MAVLINK_MSG_ID_HEARTBEAT, NULL, 0);

    mavlink_out_sys_status_struct.load = getCpuLoad();
    /* how many times device was soft resetted */
    mavlink_out_sys_status_struct.errors_count1 = bkpSoftResetCnt;
    /* reset flags */
    mavlink_out_sys_status_struct.errors_count2 = LastResetFlags >> 24;
    if (GlobalFlags.sighalt){
      palClearPad(GPIOB, GPIOB_LED_B);
      palClearPad(GPIOB, GPIOB_LED_R);
      xbee_reset_assert();
      chThdExit(RDY_OK);
    }

    blue_blinker();
    chThdSleepUntil(t);
  }
}

/**
 * Blinker thread for red LED.
 */
static WORKING_AREA(RedBlinkThreadWA, 64);
static msg_t RedBlinkThread(void *arg) {
  chRegSetThreadName("RedBlink");
  (void)arg;

  while(TRUE){
    blink_sem.wait();
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
    BlinksCount = 4;
  else
    BlinksCount = 1;

  /* write soft reset event to "log" and clean it in case of pad reset */
  if (was_softreset())
    bkpSoftResetCnt++;

  /**/
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
}

/**
 * Schedule blink sequence.
 * [in] count of blinks and time intervals in sytem ticks
 */
void SheduleRedBlink(uint32_t cnt, uint32_t on, uint32_t off){
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

  blink_sem.signal();
}




