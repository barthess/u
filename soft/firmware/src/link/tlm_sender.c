#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SYS_STATUS_3D_GYRO    ((uint32_t)1 << 0) /* for stub */
#define SYS_STATUS_3D_ACCEL   ((uint32_t)1 << 1) /* for stub */
#define SYS_STATUS_3D_MAG     ((uint32_t)1 << 2) /* for stub */
#define SYS_STATUS_ABS_PRES   ((uint32_t)1 << 3) /* for stub */
#define SYS_STATUS_DIFF_PRES  ((uint32_t)1 << 4) /* for stub */
#define SYS_STATUS_GPS        ((uint32_t)1 << 5) /* for stub */

#define TLM_REGISTRY_LEN (sizeof(Registy)/sizeof(tlm_registry_t))

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;

extern mavlink_raw_pressure_t           mavlink_raw_pressure_struct;
extern mavlink_raw_imu_t                mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t             mavlink_scaled_imu_struct;
extern mavlink_sys_status_t             mavlink_sys_status_struct;
extern mavlink_global_position_int_t    mavlink_global_position_int_struct;
extern mavlink_attitude_t               mavlink_attitude_struct;
extern mavlink_scaled_pressure_t        mavlink_scaled_pressure_struct;
extern mavlink_vfr_hud_t                mavlink_vfr_hud_struct; /* воздушная и земляная скорости */
extern mavlink_local_position_ned_t     mavlink_local_position_ned_struct;
extern mavlink_nav_controller_output_t  mavlink_nav_controller_output_struct;



static tlm_registry_t Registy[10];

/**
 *
 */
static time_t get_sleep_time(void){
  time_t t;
  uint32_t i;

  t = Registy[0].next_dealine; /* just take first available */
  i = 0;
  while (i < TLM_REGISTRY_LEN){
    /* determine how much to sleep */
    if (t > Registy[i].next_dealine)
      t = Registy[i].next_dealine;
    i++;
  }
  return t;
}

/**
 * refresh deadlines according sleeped time
 */
static void refresh_deadlines(time_t t){
  uint32_t i = 0;
  while (i < TLM_REGISTRY_LEN){
    Registy[i].next_dealine -= t;
    if (Registy[i].next_dealine == 0){
      if (*(Registy[i].sleepperiod) != SEND_OFF){
        Registy[i].next_dealine = *(Registy[i].sleepperiod);
        if (GlobalFlags.tlm_link_ready)
          Registy[i].sender();
      }
      else
        Registy[i].next_dealine = 1200;
    }
    i++;
  }
}

/**
 * Update fields in mavlink structures that does not updates itself.
 */
static void update_tlm_data(void){
  return;
}

/**
 *
 */
static WORKING_AREA(TlmSenderThreadWA, 112);
static msg_t TlmSenderThread(void *arg) {
  chRegSetThreadName("TLM_Scheduler");
  (void)arg;

  time_t t = 5; /* milliseconds to sleep to next deadline */
  refresh_deadlines(t);

  while TRUE{ /* main infinite cycle */
    t = get_sleep_time();
    chThdSleepMilliseconds(t);
    update_tlm_data();
    refresh_deadlines(t);
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
void TlmSenderInit(void){
  Registy[0].sleepperiod = ValueSearch("T_raw_imu");
  Registy[1].sleepperiod = ValueSearch("T_scal_imu");
  Registy[2].sleepperiod = ValueSearch("T_raw_press");
  Registy[3].sleepperiod = ValueSearch("T_sys_status");
  Registy[4].sleepperiod = ValueSearch("T_gps_int");
  Registy[5].sleepperiod = ValueSearch("T_attitude");
  Registy[6].sleepperiod = ValueSearch("T_scal_press");
  Registy[7].sleepperiod = ValueSearch("T_vfr_hud");
  Registy[8].sleepperiod = ValueSearch("T_position_ned");
  Registy[9].sleepperiod = ValueSearch("T_nav_output");

  mavlink_sys_status_struct.onboard_control_sensors_present = (
              SYS_STATUS_3D_GYRO | SYS_STATUS_3D_ACCEL | SYS_STATUS_3D_MAG |
              SYS_STATUS_ABS_PRES | SYS_STATUS_DIFF_PRES | SYS_STATUS_GPS);
  mavlink_sys_status_struct.onboard_control_sensors_enabled = mavlink_sys_status_struct.onboard_control_sensors_present;
  mavlink_sys_status_struct.onboard_control_sensors_health  = mavlink_sys_status_struct.onboard_control_sensors_present;

  chThdCreateStatic(TlmSenderThreadWA,
          sizeof(TlmSenderThreadWA),
          LINK_THREADS_PRIO - 1,
          TlmSenderThread,
          NULL);
}





