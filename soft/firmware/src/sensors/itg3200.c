#include <stdlib.h>
#include <math.h>

#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "utils.h"
#include "imu.h"
#include "itg3200.h"
#include "message.h"
#include "param.h"
#include "main.h"
#include "link.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define itg3200addr   0b1101000
#define PI            3.141592653589793238462643383279502884197f

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;

extern RawData raw_data;
extern CompensatedData comp_data;
extern BinarySemaphore itg3200_sem;
extern BinarySemaphore imu_sem;
//extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern GlobalParam_t global_data[];

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[GYRO_RX_DEPTH];
static uint8_t txbuf[GYRO_TX_DEPTH];

// ������� ��� �������� �����
static uint32_t zero_cnt = 0;

/* ������� � ��������� � ����������� */
static uint32_t xsens_index, ysens_index, zsens_index;
static uint32_t xpol_index,  ypol_index,  zpol_index;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * ����������� �������� �����.
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
    clearGlobalFlag(GYRO_CAL);
  }
}

/**
 * �������� �� ����� �������� � ���/���
 */
static float calc_gyro_rate(int32_t raw, float sens){
  float tmp = (float)raw;
  tmp /= (float)GYRO_AVG_SAMPLES_CNT;
  tmp /= sens;
  tmp *= (PI / 180.0);
  return tmp;
}

/**
 * ����� ��� ������ ���������
 */
static WORKING_AREA(PollGyroThreadWA, 512);
static msg_t PollGyroThread(void *arg){
  chRegSetThreadName("PollGyro");
  (void)arg;

  int32_t gyroX, gyroY, gyroZ;
  msg_t sem_status = RDY_OK;

  while (TRUE) {
    sem_status = chBSemWaitTimeout(&itg3200_sem, MS2ST(20));

    txbuf[0] = GYRO_OUT_DATA;     // register address
    if (i2c_transmit(itg3200addr, txbuf, 1, rxbuf, 8) == RDY_OK && sem_status == RDY_OK){
      raw_data.gyro_temp  = complement2signed(rxbuf[0], rxbuf[1]);
      raw_data.xgyro      = complement2signed(rxbuf[2], rxbuf[3]);
      raw_data.ygyro      = complement2signed(rxbuf[4], rxbuf[5]);
      raw_data.zgyro      = complement2signed(rxbuf[6], rxbuf[7]);

      if (GlobalFlags & GYRO_CAL)
        gyrozeroing();
      else{
        /* correct placement (we need to swap just x and y axis)
         * and advance to zero offset */
        gyroX = ((int32_t)raw_data.ygyro) * GYRO_AVG_SAMPLES_CNT - raw_data.ygyro_zero;
        gyroY = ((int32_t)raw_data.xgyro) * GYRO_AVG_SAMPLES_CNT - raw_data.xgyro_zero;
        gyroZ = ((int32_t)raw_data.zgyro) * GYRO_AVG_SAMPLES_CNT - raw_data.zgyro_zero;
        /* adjust rotation direction */
        gyroX *= global_data[xpol_index].value;
        gyroY *= global_data[ypol_index].value;
        gyroZ *= global_data[zpol_index].value;
        /* now get angular velocity in rad/sec */
        comp_data.xgyrorate = calc_gyro_rate(gyroX, global_data[xsens_index].value);
        comp_data.ygyrorate = calc_gyro_rate(gyroY, global_data[ysens_index].value);
        comp_data.zgyrorate = calc_gyro_rate(gyroZ, global_data[zsens_index].value);

        /* say to IMU "we have fresh data "*/
        chBSemSignal(&imu_sem);
      }
    }
    else{
      //TODO: event GyroFail
      /* ��������, ��������������� � ���� */
      raw_data.gyro_temp = -32768;
      raw_data.xgyro = -32768;
      raw_data.ygyro = -32768;
      raw_data.zgyro = -32768;
    }
  }
  return 0;
}


/**
 *  perform searching of indexes
 */
static void search_indexes(void){
  int32_t i = -1;

  i = key_value_search("GYRO_xsens");
  if (i == -1)
    chDbgPanic("key not found");
  else
    xsens_index = i;

  i = key_value_search("GYRO_ysens");
  if (i == -1)
    chDbgPanic("key not found");
  else
    ysens_index = i;

  i = key_value_search("GYRO_zsens");
  if (i == -1)
    chDbgPanic("key not found");
  else
    zsens_index = i;

  i = key_value_search("GYRO_xpol");
  if (i == -1)
    chDbgPanic("key not found");
  else
    xpol_index = i;

  i = key_value_search("GYRO_ypol");
  if (i == -1)
    chDbgPanic("key not found");
  else
    ypol_index = i;

  i = key_value_search("GYRO_zpol");
  if (i == -1)
    chDbgPanic("key not found");
  else
    zpol_index = i;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 *
 */
void init_itg3200(void){
  int32_t i = -1;

  search_indexes();

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    i = 0;
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
  txbuf[2] = GYRO_DLPF_CFG | GYRO_FS_SEL; /* �������� ��������� � ������� ����� ����������� ������� */
  txbuf[3] = 0b110001; /* configure and enable interrupts */
  while (i2c_transmit(itg3200addr, txbuf, 4, rxbuf, 0) != RDY_OK)
    ;

  chThdCreateStatic(PollGyroThreadWA,
          sizeof(PollGyroThreadWA),
          I2C_THREADS_PRIO + 1,
          PollGyroThread,
          NULL);

  gyro_refresh_zeros();
}

/**
 * ���������� ������������ ���� � �������� ���������� ������.
 */
void gyro_refresh_zeros(void){

  chSysLock();

  raw_data.xgyro_zero = 0;
  raw_data.ygyro_zero = 0;
  raw_data.zgyro_zero = 0;

  zero_cnt = GYRO_AVG_SAMPLES_CNT;
  GlobalFlags |= GYRO_CAL;

  chSysUnlock();
}

