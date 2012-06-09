#include <stdlib.h>
#include <math.h>

#include "ch.h"
#include "hal.h"

#include "i2c_local.h"
#include "utils.h"
#include "imu.h"
#include "itg3200.h"
#include "sensors.h"
#include "message.h"
#include "param.h"
#include "main.h"
#include "link.h"
#include "logger.h"
#include "timekeeping.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define itg3200addr   0b1101000
#define PI            3.14159265f

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;
extern Mailbox logwriter_mb;
extern RawData raw_data;
extern CompensatedData comp_data;
extern EventSource init_event;
extern mavlink_system_t mavlink_system_struct;
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;

uint32_t imu_update_period;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[GYRO_RX_DEPTH];
static uint8_t txbuf[GYRO_TX_DEPTH];

// счетчик для выставки нулей
static uint32_t zero_cnt = 0;

/* индексы в структуре с параметрами */
static uint32_t awg_samplescnt;

/* указатели на коэффициенты */
static float *xpol, *ypol, *zpol, *xsens, *ysens, *zsens;

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
 * Определение смещения нулей.
 */
void gyrozeroing(void){
  if (zero_cnt > 0){
    raw_data.xgyro_zero += raw_data.xgyro;
    raw_data.ygyro_zero += raw_data.ygyro;
    raw_data.zgyro_zero += raw_data.zgyro;
    zero_cnt--;
    return;
  }
  else{
    clearGlobalFlag(GYRO_CAL_FLAG);
    mavlink_system_struct.state = MAV_STATE_STANDBY;
  }
}

/**
 * пересчет из сырых значений в рад/сек
 */
static float calc_gyro_rate(int32_t raw, float sens){
  float tmp = (float)raw;
  tmp /= (float)awg_samplescnt;
  tmp /= sens;
  tmp *= (PI / 180.0);
  return tmp;
}

/**
 * Получение приращения угла исходя из угловой скорости и временем между выборками
 */
static float get_degrees(float raw){
  float t = (float)imu_update_period / 1000000.0;
  return raw * ((t * 180) / PI);
}

/**
 * Поток для опроса хероскопа
 */
static WORKING_AREA(PollGyroThreadWA, 256);
static msg_t PollGyroThread(void *semp){
  chRegSetThreadName("PollGyro");

  /* variables for regulate log writing frequency */
  uint32_t i = 0;
  const uint32_t decimator = 0b11;

  int32_t gyroX, gyroY, gyroZ;
  msg_t sem_status = RDY_OK;

  EventListener self_el;
  chEvtRegister(&init_event, &self_el, INIT_FAKE_EVID);

  while (TRUE) {
    sem_status = chBSemWaitTimeout((BinarySemaphore*)semp, MS2ST(20));

    txbuf[0] = GYRO_OUT_DATA;     // register address
    if ((i2c_transmit(itg3200addr, txbuf, 1, rxbuf, 8) == RDY_OK) && (sem_status == RDY_OK)){
      raw_data.gyro_temp  = complement2signed(rxbuf[0], rxbuf[1]);
      raw_data.xgyro      = complement2signed(rxbuf[2], rxbuf[3]);
      raw_data.ygyro      = complement2signed(rxbuf[4], rxbuf[5]);
      raw_data.zgyro      = complement2signed(rxbuf[6], rxbuf[7]);

      if (GlobalFlags & GYRO_CAL_FLAG)
        gyrozeroing();
      else{
        /* correct placement (we need to swap just x and y axis) and advance to zero offset */
        gyroX = ((int32_t)raw_data.ygyro) * awg_samplescnt - raw_data.ygyro_zero;
        gyroY = ((int32_t)raw_data.xgyro) * awg_samplescnt - raw_data.xgyro_zero;
        gyroZ = ((int32_t)raw_data.zgyro) * awg_samplescnt - raw_data.zgyro_zero;

        /* adjust rotation direction */
        gyroX *= *xpol;
        gyroY *= *ypol;
        gyroZ *= *zpol;

        /* fill debug struct */
        mavlink_raw_imu_struct.xgyro = gyroX;
        mavlink_raw_imu_struct.ygyro = gyroY;
        mavlink_raw_imu_struct.zgyro = gyroZ;
        mavlink_raw_imu_struct.time_usec = pnsGetTimeUnixUsec();

        /* now get angular velocity in rad/sec */
        comp_data.xgyro = calc_gyro_rate(gyroX, *xsens);
        comp_data.ygyro = calc_gyro_rate(gyroY, *ysens);
        comp_data.zgyro = calc_gyro_rate(gyroZ, *zsens);

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

        /* say to IMU "we have fresh data "*/
        chBSemSignal(imusync_semp);

        /* save data to logfile */
        if (((i & decimator) == decimator) &&
                (chThdSelf()->p_epending & EVENT_MASK(LOGGER_READY_EVID))){
          log_write_schedule(MAVLINK_MSG_ID_RAW_IMU);
          log_write_schedule(MAVLINK_MSG_ID_SCALED_IMU);
          i++;
        }
      }
    }
    else{
      //TODO: event GyroFail
      /* this values denote failed */
      raw_data.gyro_temp = -32768;
      raw_data.xgyro = -32768;
      raw_data.ygyro = -32768;
      raw_data.zgyro = -32768;
    }

    if (chThdSelf()->p_epending & EVENT_MASK(SIGHALT_EVID))
      chThdExit(RDY_OK);
  }
  return 0;
}


/**
 *  perform searching of indexes
 */
static void search_indexes(void){
  xsens = ValueSearch("GYRO_xsens");
  ysens = ValueSearch("GYRO_ysens");
  zsens = ValueSearch("GYRO_zsens");
  xpol = ValueSearch("GYRO_xpol");
  ypol = ValueSearch("GYRO_ypol");
  zpol = ValueSearch("GYRO_zpol");

  awg_samplescnt = floorf(*(ValueSearch("GYRO_zeroconut")));
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

  imusync_semp = imu_semp;

  // обнуление инкрементальных сумм
  comp_data.xgyro_angle = 0;
  comp_data.ygyro_angle = 0;
  comp_data.zgyro_angle = 0;

  search_indexes();

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint32_t i = 0;
    for (i = 0; i < GYRO_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < GYRO_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  txbuf[0] = GYRO_PWR_MGMT;
  txbuf[1] = 0b1000000; /* soft reset */
  while (i2c_transmit(itg3200addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;
  chThdSleepMilliseconds(55);

  txbuf[0] = GYRO_PWR_MGMT;
  txbuf[1] = 1; /* select clock source */
  while (i2c_transmit(itg3200addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;
  chThdSleepMilliseconds(2);

  txbuf[0] = GYRO_SMPLRT_DIV;
  txbuf[1] = 9; /* sample rate. Approximatelly (1000 / (9 + 1)) = 100Hz*/
  txbuf[2] = GYRO_DLPF_CFG | GYRO_FS_SEL; /* диапазон измерений и частота среза внутреннего фильтра */
  txbuf[3] = 0b110001; /* configure and enable interrupts */
  while (i2c_transmit(itg3200addr, txbuf, 4, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  chThdCreateStatic(PollGyroThreadWA,
          sizeof(PollGyroThreadWA),
          I2C_THREADS_PRIO + 2,
          PollGyroThread,
          itg3200_semp);
  chThdSleepMilliseconds(2);

  /* fireup calibration */
  mavlink_system_struct.state = MAV_STATE_CALIBRATING;
  setGlobalFlag(GYRO_CAL_FLAG);
  gyro_refresh_zeros();
}

/**
 * Сбрасывает рассчитанные нули и проводит калибровку заново.
 */
void gyro_refresh_zeros(void){
  raw_data.xgyro_zero = 0;
  raw_data.ygyro_zero = 0;
  raw_data.zgyro_zero = 0;
  zero_cnt = awg_samplescnt;
}

