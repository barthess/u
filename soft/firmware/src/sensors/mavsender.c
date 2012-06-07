#include "ch.h"
#include "hal.h"

#include "mavsender.h"
#include "param.h"
#include "message.h"
#include "main.h"
#include "sanity.h"
#include "timekeeping.h"

/**
 * Код посылает данные на землю путем постинга сообщений в почтовый ящик
 * для этого предназначенный. Отдельный тред на каждый тип сообщения -
 * overkill. При нехватке оперативной памяти все это придется переписать
 * на один поток со своим "шедулером".
 */

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SYS_STATUS_3D_GYRO    ((uint32_t)1 << 0)
#define SYS_STATUS_3D_ACCEL   ((uint32_t)1 << 1)
#define SYS_STATUS_3D_MAG     ((uint32_t)1 << 2)
#define SYS_STATUS_ABS_PRES   ((uint32_t)1 << 3)
#define SYS_STATUS_DIFF_PRES  ((uint32_t)1 << 4)
#define SYS_STATUS_GPS        ((uint32_t)1 << 5)

/* Sieze of working area for sending threads */
#define SEND_THD_SIZE 96

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;
extern EventSource modem_event;

extern mavlink_raw_pressure_t        mavlink_raw_pressure_struct;
extern mavlink_raw_imu_t             mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t          mavlink_scaled_imu_struct;
extern mavlink_sys_status_t          mavlink_sys_status_struct;
extern mavlink_global_position_int_t mavlink_global_position_int_struct;
extern mavlink_attitude_t            mavlink_attitude_struct;
extern mavlink_scaled_pressure_t     mavlink_scaled_pressure_struct;
extern mavlink_vfr_hud_t             mavlink_vfr_hud_struct; /* воздушная и земляная скорости */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static float  *raw_imu,
              *raw_press,
              *scal_imu,
              *scal_press,
              *attitude,
              *vfr_hud,
              *gps_int,
              *sys_status;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 *
 */
static WORKING_AREA(RAW_IMU_SenderThreadWA, SEND_THD_SIZE);
static msg_t RAW_IMU_SenderThread(void *arg) {
  chRegSetThreadName("Sender_RAW_IMU");
  (void)arg;

  Mail raw_imu_mail = {NULL, MAVLINK_MSG_ID_RAW_IMU, NULL};
  struct EventListener self_el;
  chEvtRegister(&modem_event, &self_el, MODEM_READY);

  chEvtWaitOne(EVENT_MASK(MODEM_READY));

  while (TRUE) {
    chThdSleepMilliseconds(*raw_imu);
    if ((raw_imu_mail.payload == NULL) && (*raw_imu != SEND_OFF)){
      mavlink_raw_imu_struct.time_usec = pnsGetTimeUnixUsec();
      raw_imu_mail.payload = &mavlink_raw_imu_struct;
      chMBPost(&tolink_mb, (msg_t)&raw_imu_mail, TIME_IMMEDIATE);
    }
  }
  return 0;
}

/**
 *
 */
static WORKING_AREA(ScaledImuSenderThreadWA, SEND_THD_SIZE);
static msg_t ScaledImuSenderThread(void *arg) {
  chRegSetThreadName("Sender_SCALED_IMU");
  (void)arg;

  Mail scaled_imu_mail = {NULL, MAVLINK_MSG_ID_SCALED_IMU, NULL};
  struct EventListener self_el;
  chEvtRegister(&modem_event, &self_el, MODEM_READY);

  chEvtWaitOne(EVENT_MASK(MODEM_READY));

  while (TRUE) {
    chThdSleepMilliseconds(*scal_imu);
    if ((scaled_imu_mail.payload == NULL) && (*scal_imu != SEND_OFF)){
      mavlink_scaled_imu_struct.time_boot_ms = TIME_BOOT_MS;
      scaled_imu_mail.payload = &mavlink_scaled_imu_struct;
      chMBPost(&tolink_mb, (msg_t)&scaled_imu_mail, TIME_IMMEDIATE);
    }
  }
  return 0;
}

/**
 *
 */
static WORKING_AREA(AttitudeSenderThreadWA, SEND_THD_SIZE);
static msg_t AttitudeSenderThread(void *arg) {
  chRegSetThreadName("Sender_ATTITUDE");
  (void)arg;

  Mail attitude_mail = {NULL, MAVLINK_MSG_ID_ATTITUDE, NULL};
  struct EventListener self_el;
  chEvtRegister(&modem_event, &self_el, MODEM_READY);

  chEvtWaitOne(EVENT_MASK(MODEM_READY));

  while (TRUE) {
    chThdSleepMilliseconds(*attitude);
    if ((attitude_mail.payload == NULL) && (*attitude != SEND_OFF)){
      mavlink_attitude_struct.time_boot_ms = TIME_BOOT_MS;
      attitude_mail.payload = &mavlink_attitude_struct;
      chMBPost(&tolink_mb, (msg_t)&attitude_mail, TIME_IMMEDIATE);
    }
  }
  return 0;
}

/**
 *
 */
static WORKING_AREA(RAW_PRESSURE_SenderThreadWA, SEND_THD_SIZE);
static msg_t RAW_PRESSURE_SenderThread(void *arg) {
  chRegSetThreadName("Sender_RAW_PRESSURE");
  (void)arg;

  Mail raw_pressure_mail = {NULL, MAVLINK_MSG_ID_RAW_PRESSURE, NULL};
  struct EventListener self_el;
  chEvtRegister(&modem_event, &self_el, MODEM_READY);

  chEvtWaitOne(EVENT_MASK(MODEM_READY));

  while (TRUE) {
    chThdSleepMilliseconds(*raw_press);
    if ((raw_pressure_mail.payload == NULL) && (*raw_press != SEND_OFF)){
      mavlink_raw_pressure_struct.time_usec = pnsGetTimeUnixUsec();
      raw_pressure_mail.payload = &mavlink_raw_pressure_struct;
      chMBPost(&tolink_mb, (msg_t)&raw_pressure_mail, TIME_IMMEDIATE);
    }
  }
  return 0;
}


/**
 *
 */
static WORKING_AREA(VFR_HUD_SenderThreadWA, SEND_THD_SIZE);
static msg_t VFR_HUD_SenderThread(void *arg) {
  chRegSetThreadName("Sender_VFR_HUD");
  (void)arg;

  Mail vfr_hud_mail = {NULL, MAVLINK_MSG_ID_VFR_HUD, NULL};
  struct EventListener self_el;
  chEvtRegister(&modem_event, &self_el, MODEM_READY);

  chEvtWaitOne(EVENT_MASK(MODEM_READY));

  while (TRUE) {
    chThdSleepMilliseconds(*vfr_hud);
    if ((vfr_hud_mail.payload == NULL) && (*vfr_hud != SEND_OFF)){
      vfr_hud_mail.payload = &mavlink_vfr_hud_struct;
      chMBPost(&tolink_mb, (msg_t)&vfr_hud_mail, TIME_IMMEDIATE);
    }
  }
  return 0;
}


/**
 *
 */
static WORKING_AREA(GPS_INT_SenderThreadWA, SEND_THD_SIZE);
static msg_t GPS_INT_SenderThread(void *arg) {
  chRegSetThreadName("Sender_GPS_INT");
  (void)arg;

  Mail global_position_int_mail = {NULL, MAVLINK_MSG_ID_GLOBAL_POSITION_INT, NULL};
  struct EventListener self_el;
  chEvtRegister(&modem_event, &self_el, MODEM_READY);

  chEvtWaitOne(EVENT_MASK(MODEM_READY));

  while (TRUE) {
    chThdSleepMilliseconds(*gps_int);
    if ((global_position_int_mail.payload == NULL) && (*gps_int != SEND_OFF)){
      mavlink_global_position_int_struct.time_boot_ms = TIME_BOOT_MS;
      global_position_int_mail.payload = &mavlink_global_position_int_struct;
      chMBPost(&tolink_mb, (msg_t)&global_position_int_mail, TIME_IMMEDIATE);
    }
  }
  return 0;
}

/**
 *
 */
static WORKING_AREA(SCAL_PRESS_SenderThreadWA, SEND_THD_SIZE);
static msg_t SCAL_PRESS_SenderThread(void *arg) {
  chRegSetThreadName("Sender_GPS_INT");
  (void)arg;

  Mail scaled_pressure_mail = {NULL, MAVLINK_MSG_ID_SCALED_PRESSURE, NULL};
  struct EventListener self_el;
  chEvtRegister(&modem_event, &self_el, MODEM_READY);

  chEvtWaitOne(EVENT_MASK(MODEM_READY));

  while (TRUE) {
    chThdSleepMilliseconds(*scal_press);
    if ((scaled_pressure_mail.payload == NULL) && (*scal_press != SEND_OFF)){
      mavlink_scaled_pressure_struct.time_boot_ms = TIME_BOOT_MS;
      scaled_pressure_mail.payload = &mavlink_scaled_pressure_struct;
      chMBPost(&tolink_mb, (msg_t)&scaled_pressure_mail, TIME_IMMEDIATE);
    }
  }
  return 0;
}


/**
 *
 */
static WORKING_AREA(SYS_STAT_SenderThreadWA, SEND_THD_SIZE);
static msg_t SYS_STAT_SenderThread(void *arg) {
  chRegSetThreadName("Sender_SYS_STAT");
  (void)arg;

  Mail sys_status_mail = {NULL, MAVLINK_MSG_ID_SYS_STATUS, NULL};
  struct EventListener self_el;
  chEvtRegister(&modem_event, &self_el, MODEM_READY);

  chEvtWaitOne(EVENT_MASK(MODEM_READY));

  while (TRUE) {
    chThdSleepMilliseconds(*sys_status);
    if ((sys_status_mail.payload == NULL) && (*sys_status != SEND_OFF)){


      mavlink_sys_status_struct.load = get_cpu_load();

      sys_status_mail.payload = &mavlink_sys_status_struct;
      chMBPost(&tolink_mb, (msg_t)&sys_status_mail, TIME_IMMEDIATE);
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
void MavSenderInit(void){

  raw_imu     = ValueSearch("T_raw_imu");
  raw_press   = ValueSearch("T_raw_press");
  scal_imu    = ValueSearch("T_scal_imu");
  scal_press  = ValueSearch("T_scal_press");
  attitude    = ValueSearch("T_attitude");
  vfr_hud     = ValueSearch("T_vfr_hud");
  gps_int     = ValueSearch("T_gps_int");
  sys_status  = ValueSearch("T_sys_status");


  chThdCreateStatic(RAW_IMU_SenderThreadWA,
          sizeof(RAW_IMU_SenderThreadWA),
          LINK_THREADS_PRIO - 1,
          RAW_IMU_SenderThread,
          NULL);

  chThdCreateStatic(ScaledImuSenderThreadWA,
          sizeof(ScaledImuSenderThreadWA),
          LINK_THREADS_PRIO - 1,
          ScaledImuSenderThread,
          NULL);

  chThdCreateStatic(AttitudeSenderThreadWA,
          sizeof(AttitudeSenderThreadWA),
          LINK_THREADS_PRIO - 1,
          AttitudeSenderThread,
          NULL);

  chThdCreateStatic(RAW_PRESSURE_SenderThreadWA,
          sizeof(RAW_PRESSURE_SenderThreadWA),
          LINK_THREADS_PRIO - 1,
          RAW_PRESSURE_SenderThread,
          NULL);

  chThdCreateStatic(VFR_HUD_SenderThreadWA,
          sizeof(VFR_HUD_SenderThreadWA),
          LINK_THREADS_PRIO - 1,
          VFR_HUD_SenderThread,
          NULL);

  chThdCreateStatic(GPS_INT_SenderThreadWA,
          sizeof(GPS_INT_SenderThreadWA),
          LINK_THREADS_PRIO - 1,
          GPS_INT_SenderThread,
          NULL);

  chThdCreateStatic(SCAL_PRESS_SenderThreadWA,
          sizeof(SCAL_PRESS_SenderThreadWA),
          LINK_THREADS_PRIO - 1,
          SCAL_PRESS_SenderThread,
          NULL);

  mavlink_sys_status_struct.onboard_control_sensors_present = (
          SYS_STATUS_3D_GYRO | SYS_STATUS_3D_ACCEL | SYS_STATUS_3D_MAG |
          SYS_STATUS_ABS_PRES | SYS_STATUS_DIFF_PRES | SYS_STATUS_GPS);
  mavlink_sys_status_struct.onboard_control_sensors_enabled = mavlink_sys_status_struct.onboard_control_sensors_present;
  mavlink_sys_status_struct.onboard_control_sensors_health  = mavlink_sys_status_struct.onboard_control_sensors_present;
  chThdCreateStatic(SYS_STAT_SenderThreadWA,
          sizeof(SYS_STAT_SenderThreadWA),
          LINK_THREADS_PRIO - 1,
          SYS_STAT_SenderThread,
          NULL);
}


