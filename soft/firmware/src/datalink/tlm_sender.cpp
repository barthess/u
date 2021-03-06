/* 
!!! Atomatically generated by
src/link/gen_tlm_sender.py
Do not edit it manually. 
*/
#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "param_registry.hpp"
/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define start_raw_imu_vt() {chVTSetI(&raw_imu_vt, MS2ST(*raw_imu), &raw_imu_vtcb, NULL);}
#define start_scal_imu_vt() {chVTSetI(&scal_imu_vt, MS2ST(*scal_imu), &scal_imu_vtcb, NULL);}
#define start_raw_press_vt() {chVTSetI(&raw_press_vt, MS2ST(*raw_press), &raw_press_vtcb, NULL);}
#define start_sys_status_vt() {chVTSetI(&sys_status_vt, MS2ST(*sys_status), &sys_status_vtcb, NULL);}
#define start_gps_int_vt() {chVTSetI(&gps_int_vt, MS2ST(*gps_int), &gps_int_vtcb, NULL);}
#define start_attitude_vt() {chVTSetI(&attitude_vt, MS2ST(*attitude), &attitude_vtcb, NULL);}
#define start_scal_press_vt() {chVTSetI(&scal_press_vt, MS2ST(*scal_press), &scal_press_vtcb, NULL);}
#define start_vfr_hud_vt() {chVTSetI(&vfr_hud_vt, MS2ST(*vfr_hud), &vfr_hud_vtcb, NULL);}
#define start_position_ned_vt() {chVTSetI(&position_ned_vt, MS2ST(*position_ned), &position_ned_vtcb, NULL);}
#define start_nav_output_vt() {chVTSetI(&nav_output_vt, MS2ST(*nav_output), &nav_output_vtcb, NULL);}


/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern ParamRegistry param_registry;
extern GlobalFlags_t GlobalFlags;

extern EventSource event_mavlink_out_raw_imu;
extern EventSource event_mavlink_out_scaled_imu;
extern EventSource event_mavlink_out_raw_pressure;
extern EventSource event_mavlink_out_sys_status;
extern EventSource event_mavlink_out_global_position_int;
extern EventSource event_mavlink_out_attitude;
extern EventSource event_mavlink_out_scaled_pressure;
extern EventSource event_mavlink_out_vfr_hud;
extern EventSource event_mavlink_out_local_position_ned;
extern EventSource event_mavlink_out_nav_controller_output;


/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint32_t const *raw_imu;
static uint32_t const *scal_imu;
static uint32_t const *raw_press;
static uint32_t const *sys_status;
static uint32_t const *gps_int;
static uint32_t const *attitude;
static uint32_t const *scal_press;
static uint32_t const *vfr_hud;
static uint32_t const *position_ned;
static uint32_t const *nav_output;

static VirtualTimer raw_imu_vt;
static VirtualTimer scal_imu_vt;
static VirtualTimer raw_press_vt;
static VirtualTimer sys_status_vt;
static VirtualTimer gps_int_vt;
static VirtualTimer attitude_vt;
static VirtualTimer scal_press_vt;
static VirtualTimer vfr_hud_vt;
static VirtualTimer position_ned_vt;
static VirtualTimer nav_output_vt;

static uint32_t raw_imu_cached = SEND_OFF;
static uint32_t scal_imu_cached = SEND_OFF;
static uint32_t raw_press_cached = SEND_OFF;
static uint32_t sys_status_cached = SEND_OFF;
static uint32_t gps_int_cached = SEND_OFF;
static uint32_t attitude_cached = SEND_OFF;
static uint32_t scal_press_cached = SEND_OFF;
static uint32_t vfr_hud_cached = SEND_OFF;
static uint32_t position_ned_cached = SEND_OFF;
static uint32_t nav_output_cached = SEND_OFF;


/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
static void raw_imu_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_raw_imu, EVMSK_MAVLINK_OUT_RAW_IMU);
  raw_imu_cached = *raw_imu;
  if (*raw_imu != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_raw_imu_vt();
  chSysUnlockFromIsr();
}

static void scal_imu_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_scaled_imu, EVMSK_MAVLINK_OUT_SCALED_IMU);
  scal_imu_cached = *scal_imu;
  if (*scal_imu != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_scal_imu_vt();
  chSysUnlockFromIsr();
}

static void raw_press_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_raw_pressure, EVMSK_MAVLINK_OUT_RAW_PRESSURE);
  raw_press_cached = *raw_press;
  if (*raw_press != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_raw_press_vt();
  chSysUnlockFromIsr();
}

static void sys_status_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_sys_status, EVMSK_MAVLINK_OUT_SYS_STATUS);
  sys_status_cached = *sys_status;
  if (*sys_status != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_sys_status_vt();
  chSysUnlockFromIsr();
}

static void gps_int_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_global_position_int, EVMSK_MAVLINK_OUT_GLOBAL_POSITION_INT);
  gps_int_cached = *gps_int;
  if (*gps_int != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_gps_int_vt();
  chSysUnlockFromIsr();
}

static void attitude_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_attitude, EVMSK_MAVLINK_OUT_ATTITUDE);
  attitude_cached = *attitude;
  if (*attitude != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_attitude_vt();
  chSysUnlockFromIsr();
}

static void scal_press_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_scaled_pressure, EVMSK_MAVLINK_OUT_SCALED_PRESSURE);
  scal_press_cached = *scal_press;
  if (*scal_press != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_scal_press_vt();
  chSysUnlockFromIsr();
}

static void vfr_hud_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_vfr_hud, EVMSK_MAVLINK_OUT_VFR_HUD);
  vfr_hud_cached = *vfr_hud;
  if (*vfr_hud != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_vfr_hud_vt();
  chSysUnlockFromIsr();
}

static void position_ned_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_local_position_ned, EVMSK_MAVLINK_OUT_LOCAL_POSITION_NED);
  position_ned_cached = *position_ned;
  if (*position_ned != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_position_ned_vt();
  chSysUnlockFromIsr();
}

static void nav_output_vtcb(void *par){
  (void)par;
  chSysLockFromIsr();
  chEvtBroadcastFlagsI(&event_mavlink_out_nav_controller_output, EVMSK_MAVLINK_OUT_NAV_CONTROLLER_OUTPUT);
  nav_output_cached = *nav_output;
  if (*nav_output != SEND_OFF) // self restarting only if sending for this parameter not disabled
    start_nav_output_vt();
  chSysUnlockFromIsr();
}


/**
 * Listen events with new parameters
 * compare new values with old cached values
 * if changed - retune virtual timers
 */
static WORKING_AREA(TlmSenderThreadWA, 128);
static msg_t TlmSenderThread(void *arg) {
  chRegSetThreadName("TLM_Scheduler");
  (void)arg;

  while (!GlobalFlags.tlm_link_ready)
    chThdSleepMilliseconds(50);

  raw_imu = (const uint32_t*)param_registry.valueSearch("T_raw_imu");
  scal_imu = (const uint32_t*)param_registry.valueSearch("T_scal_imu");
  raw_press = (const uint32_t*)param_registry.valueSearch("T_raw_press");
  sys_status = (const uint32_t*)param_registry.valueSearch("T_sys_status");
  gps_int = (const uint32_t*)param_registry.valueSearch("T_gps_int");
  attitude = (const uint32_t*)param_registry.valueSearch("T_attitude");
  scal_press = (const uint32_t*)param_registry.valueSearch("T_scal_press");
  vfr_hud = (const uint32_t*)param_registry.valueSearch("T_vfr_hud");
  position_ned = (const uint32_t*)param_registry.valueSearch("T_position_ned");
  nav_output = (const uint32_t*)param_registry.valueSearch("T_nav_output");

  do{
    if ((raw_imu_cached == SEND_OFF) && (*raw_imu != SEND_OFF)){
      chSysLock();
      raw_imu_cached = *raw_imu;
      start_raw_imu_vt();
      chSysUnlock();
    }

    if ((scal_imu_cached == SEND_OFF) && (*scal_imu != SEND_OFF)){
      chSysLock();
      scal_imu_cached = *scal_imu;
      start_scal_imu_vt();
      chSysUnlock();
    }

    if ((raw_press_cached == SEND_OFF) && (*raw_press != SEND_OFF)){
      chSysLock();
      raw_press_cached = *raw_press;
      start_raw_press_vt();
      chSysUnlock();
    }

    if ((sys_status_cached == SEND_OFF) && (*sys_status != SEND_OFF)){
      chSysLock();
      sys_status_cached = *sys_status;
      start_sys_status_vt();
      chSysUnlock();
    }

    if ((gps_int_cached == SEND_OFF) && (*gps_int != SEND_OFF)){
      chSysLock();
      gps_int_cached = *gps_int;
      start_gps_int_vt();
      chSysUnlock();
    }

    if ((attitude_cached == SEND_OFF) && (*attitude != SEND_OFF)){
      chSysLock();
      attitude_cached = *attitude;
      start_attitude_vt();
      chSysUnlock();
    }

    if ((scal_press_cached == SEND_OFF) && (*scal_press != SEND_OFF)){
      chSysLock();
      scal_press_cached = *scal_press;
      start_scal_press_vt();
      chSysUnlock();
    }

    if ((vfr_hud_cached == SEND_OFF) && (*vfr_hud != SEND_OFF)){
      chSysLock();
      vfr_hud_cached = *vfr_hud;
      start_vfr_hud_vt();
      chSysUnlock();
    }

    if ((position_ned_cached == SEND_OFF) && (*position_ned != SEND_OFF)){
      chSysLock();
      position_ned_cached = *position_ned;
      start_position_ned_vt();
      chSysUnlock();
    }

    if ((nav_output_cached == SEND_OFF) && (*nav_output != SEND_OFF)){
      chSysLock();
      nav_output_cached = *nav_output;
      start_nav_output_vt();
      chSysUnlock();
    }

    chThdSleepMilliseconds(100);
  }while (!chThdShouldTerminate());

  chThdExit(0);
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
void TlmSenderInit(void){
  chThdCreateStatic(TlmSenderThreadWA,
          sizeof(TlmSenderThreadWA),
          LINK_THREADS_PRIO - 1,
          TlmSenderThread,
          NULL);
}
