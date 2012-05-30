#include "ch.h"
#include "hal.h"

#include "mavsender.h"
#include "param.h"
#include "message.h"
#include "main.h"
#include "sanity.h"
#include "timekeeping.h"

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

#define RAW_IMU               (global_data[raw_imu_index].value)
#define RAW_PRESS             (global_data[raw_press_index].value)
#define SCAL_IMU              (global_data[scal_imu_index].value)
#define SCAL_PRESS            (global_data[scal_press_index].value)
#define ATTITUDE              (global_data[attitude_index].value)
#define VFR_HUD               (global_data[vfr_hud_index].value)
#define GPS_INT               (global_data[gps_int_index].value)
#define SYS_STATUS            (global_data[sys_status_index].value)

/* Sieze of working area for sending threads */
#define SEND_THD_SIZE 96

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;
extern Mailbox logwriter_mb;
extern GlobalParam_t global_data[];
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
static uint32_t raw_imu_index,
                raw_press_index,
                scal_imu_index,
                scal_press_index,
                attitude_index,
                vfr_hud_index,
                gps_int_index,
                sys_status_index;

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
    chThdSleepMilliseconds(RAW_IMU);
    if ((raw_imu_mail.payload == NULL) && (RAW_IMU != SEND_OFF)){
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
    chThdSleepMilliseconds(SCAL_IMU);
    if ((scaled_imu_mail.payload == NULL) && (SCAL_IMU != SEND_OFF)){
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
    chThdSleepMilliseconds(ATTITUDE);
    if ((attitude_mail.payload == NULL) && (ATTITUDE != SEND_OFF)){
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
    chThdSleepMilliseconds(RAW_PRESS);
    if ((raw_pressure_mail.payload == NULL) && (RAW_PRESS != SEND_OFF)){
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
    chThdSleepMilliseconds(VFR_HUD);
    if ((vfr_hud_mail.payload == NULL) && (VFR_HUD != SEND_OFF)){
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
    chThdSleepMilliseconds(GPS_INT);
    if ((global_position_int_mail.payload == NULL) && (GPS_INT != SEND_OFF)){
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
    chThdSleepMilliseconds(SCAL_PRESS);
    if ((scaled_pressure_mail.payload == NULL) && (SCAL_PRESS != SEND_OFF)){
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
    chThdSleepMilliseconds(SYS_STATUS);
    if ((sys_status_mail.payload == NULL) && (SYS_STATUS != SEND_OFF)){


      mavlink_sys_status_struct.load = get_cpu_load();

      sys_status_mail.payload = &mavlink_sys_status_struct;
      chMBPost(&tolink_mb, (msg_t)&sys_status_mail, TIME_IMMEDIATE);
    }
  }
  return 0;
}

/**
 *
 */
static WORKING_AREA(logThreadWA, 256);
static msg_t logThread(void *arg) {
  chRegSetThreadName("log");
  (void)arg;

  uint8_t teststr[] = "|this is test message++++++++++\r\n";
  Mail test = {NULL, sizeof(teststr) - 1, NULL};

  while (TRUE) {
    chThdSleepMilliseconds(20);
    if (test.payload == NULL){
      test.payload = teststr;
      chMBPost(&logwriter_mb, (msg_t)&test, TIME_INFINITE);
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
  int32_t i = -1;

  kvs(T, raw_imu);
  kvs(T, scal_imu);
  kvs(T, raw_press);
  kvs(T, scal_press);
  kvs(T, attitude);
  kvs(T, vfr_hud);
  kvs(T, gps_int);
  kvs(T, sys_status);

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

  chThdCreateStatic(logThreadWA,
          sizeof(logThreadWA),
          LINK_THREADS_PRIO - 1,
          logThread,
          NULL);
}


