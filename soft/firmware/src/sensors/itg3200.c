#include <stdlib.h>
#include <math.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define itg3200addr   0b1101000
#define GYRO_TIMEOUT  MS2ST(50)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern CompensatedData comp_data;

extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern mavlink_system_t mavlink_system_struct;

uint32_t GyroUpdatePeriodUs; /* uS */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[GYRO_RX_DEPTH];
static uint8_t txbuf[GYRO_TX_DEPTH];

/* указатели на коэффициенты */
static float    const *xsens,     *ysens,     *zsens;
static int32_t  const *xpol,      *ypol,      *zpol;
static int32_t  const *x_zerosum, *y_zerosum, *z_zerosum;
static uint32_t const *zerocnt,   *sortmtrx;

/* семафор для синхронизации инерциалки с хероскопом */
static BinarySemaphore *imusync_semp = NULL;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 * пересчет из сырых значений в рад/сек
 */
static float calc_gyro_rate(int32_t raw, float sens){
  float tmp = (float)raw;
  tmp /= (float)*zerocnt;
  tmp /= sens;
  tmp *= (PI / 180.0);
  return tmp;
}

/**
 * Получение приращения угла исходя из угловой скорости и временем между выборками
 */
static float get_degrees(float raw){
  float t = (float)GyroUpdatePeriodUs / 1000000.0;
  return raw * ((t * 180) / PI);
}

/**
 *
 */
static void process_gyro_data(uint8_t *rxbuf){
  int32_t rawgyro[3];
  int32_t gyro[3];
  bool_t  status;

  //rawgyrotemp  = complement2signed(rxbuf[0], rxbuf[1]);
  rawgyro[0] = complement2signed(rxbuf[2], rxbuf[3]);
  rawgyro[1] = complement2signed(rxbuf[4], rxbuf[5]);
  rawgyro[2] = complement2signed(rxbuf[6], rxbuf[7]);

  sorti_3values(rawgyro, gyro, *sortmtrx);

  /* update statistic for zeros */
  status = gyro_stat_update(gyro[0], gyro[1], gyro[2]);

  /* correct zero offset */
  gyro[0] = gyro[0] * *zerocnt - *x_zerosum;
  gyro[1] = gyro[1] * *zerocnt - *y_zerosum;
  gyro[2] = gyro[2] * *zerocnt - *z_zerosum;

  /* adjust rotation direction */
  gyro[0] *= *xpol;
  gyro[1] *= *ypol;
  gyro[2] *= *zpol;

  /* fill debug struct */
  mavlink_raw_imu_struct.xgyro = gyro[0];
  mavlink_raw_imu_struct.ygyro = gyro[1];
  mavlink_raw_imu_struct.zgyro = gyro[2];
  mavlink_raw_imu_struct.time_usec = pnsGetTimeUnixUsec();

  /* now get angular velocity in rad/sec */
  comp_data.xgyro = calc_gyro_rate(gyro[0], *xsens);
  comp_data.ygyro = calc_gyro_rate(gyro[1], *ysens);
  comp_data.zgyro = calc_gyro_rate(gyro[2], *zsens);

  /* calc summary angle for debug purpose */
  comp_data.xgyro_angle += get_degrees(comp_data.xgyro);
  comp_data.ygyro_angle += get_degrees(comp_data.ygyro);
  comp_data.zgyro_angle += get_degrees(comp_data.zgyro);

  /* fill scaled debug struct */
//        mavlink_scaled_imu_struct.xgyro = (int16_t)(1000 * comp_data.xgyro);
//        mavlink_scaled_imu_struct.ygyro = (int16_t)(1000 * comp_data.ygyro);
//        mavlink_scaled_imu_struct.zgyro = (int16_t)(1000 * comp_data.zgyro);
  mavlink_scaled_imu_struct.xgyro = (int16_t)(10 * comp_data.xgyro_angle);
  mavlink_scaled_imu_struct.ygyro = (int16_t)(10 * comp_data.ygyro_angle);
  mavlink_scaled_imu_struct.zgyro = (int16_t)(10 * comp_data.zgyro_angle);
  mavlink_scaled_imu_struct.time_boot_ms = TIME_BOOT_MS;

  if (status == GYRO_STAT_UNCHANGED)
    chBSemSignal(imusync_semp);/* say IMU "Hey, we have fresh data!"*/
}

/**
 * Поток для опроса хероскопа
 */
static WORKING_AREA(PollGyroThreadWA, 384);
static msg_t PollGyroThread(void *semp){
  chRegSetThreadName("PollGyro");

  msg_t sem_status = RDY_OK;
  int32_t retry = 10;

  /* variables for regulate log writing frequency */
  uint32_t i = 0;
  const uint32_t decimator = 0b11;

  while (TRUE) {
    sem_status = chBSemWaitTimeout((BinarySemaphore*)semp, GYRO_TIMEOUT);
    if (sem_status != RDY_OK){
      retry--;
      chDbgAssert(retry > 0, "PollGyroThread(), #1", "no interrupts from gyro");
    }
    txbuf[0] = GYRO_OUT_DATA;
    i2c_transmit(itg3200addr, txbuf, 1, rxbuf, 8);
    process_gyro_data(rxbuf);
    log_write_schedule(MAVLINK_MSG_ID_RAW_IMU, &i, decimator);
    i--; /* trick to avoid having one more variable for decimating */
    log_write_schedule(MAVLINK_MSG_ID_SCALED_IMU, &i, decimator);
  }
  return 0;
}

/**
 *
 */
static void __search_indexes(void){
  xsens     = ValueSearch("GYRO_xsens");
  ysens     = ValueSearch("GYRO_ysens");
  zsens     = ValueSearch("GYRO_zsens");

  xpol      = ValueSearch("GYRO_xpol");
  ypol      = ValueSearch("GYRO_ypol");
  zpol      = ValueSearch("GYRO_zpol");

  zerocnt   = ValueSearch("GYRO_zerocnt");
  sortmtrx  = ValueSearch("GYRO_sortmtrx");
  x_zerosum = ValueSearch("GYRO_x_zerosum");
  y_zerosum = ValueSearch("GYRO_y_zerosum");
  z_zerosum = ValueSearch("GYRO_z_zerosum");
}

/**
 *
 */
static void __hard_init_short(void){
}

/**
 *
 */
static void __hard_init_full(void){

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint32_t i = 0;
    for (i = 0; i < GYRO_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < GYRO_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  txbuf[0] = GYRO_PWR_MGMT;
  txbuf[1] = 0b1000000; /* soft reset */
  i2c_transmit(itg3200addr, txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(60);

//  txbuf[0] = GYRO_WHOAMI;
//  i2c_transmit(itg3200addr, txbuf, 1, rxbuf, 2);
//  chDbgCheck((rxbuf[0] >> 1) == GYRO_WHOAMI_VAL, "Wrong whoami respose");
//  chThdSleepMilliseconds(5);

  txbuf[0] = GYRO_PWR_MGMT;
  txbuf[1] = 1; /* select clock source */
  i2c_transmit(itg3200addr, txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(5);

  txbuf[0] = GYRO_SMPLRT_DIV;
  txbuf[1] = 9; /* sample rate. Approximatelly (1000 / (9 + 1)) = 100Hz*/
  txbuf[2] = GYRO_DLPF_CFG | GYRO_FS_SEL; /* диапазон измерений и частота среза внутреннего фильтра */
  //txbuf[3] = 0b00110001; /* configure and enable interrupts */
  txbuf[3] = 0b00010001; /* configure and enable interrupts */
  i2c_transmit(itg3200addr, txbuf, 4, rxbuf, 0);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
void init_itg3200(BinarySemaphore *itg3200_semp, BinarySemaphore *imu_semp){

  /* set close to real value. It can be updated later using EXTI module */
  GyroUpdatePeriodUs = 10000;

  imusync_semp = imu_semp;

  // обнуление инкрементальных сумм
  comp_data.xgyro_angle = 0;
  comp_data.ygyro_angle = 0;
  comp_data.zgyro_angle = 0;

  __search_indexes();

  if (need_full_init())
    __hard_init_full();
  else
    __hard_init_short();

  /* schedule calibration */
  GyroCalInit();
  if (need_full_init())
    setGlobalFlag(GlobalFlags.gyro_cal);
  else
    mavlink_system_struct.state = MAV_STATE_STANDBY;

  /**/
  chThdCreateStatic(PollGyroThreadWA,
          sizeof(PollGyroThreadWA),
          I2C_THREADS_PRIO,
          PollGyroThread,
          itg3200_semp);
}

