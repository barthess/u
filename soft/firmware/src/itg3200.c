#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "dsp.h"
#include "imu.h"
#include "itg3200.h"
#include "message.h"
#include "main.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define itg3200addr 0b1101000

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;
extern RawData raw_data;
extern BinarySemaphore itg3200_sem;
extern BinarySemaphore imu_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[GYRO_RX_DEPTH];
static uint8_t txbuf[GYRO_TX_DEPTH];

// счетчик для выставки нулей
static uint32_t zero_cnt = 0;
// счетчик для интегрирования
static uint32_t gyrosamplecnt = 0;

// массив собранных значений для рассчета интеграла
static int32_t gxv[4] = {0,0,0,0};
static int32_t gyv[4] = {0,0,0,0};
static int32_t gzv[4] = {0,0,0,0};

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Определение спещения нулей.
 */
void gyrozeroing(void){
  if (zero_cnt > 0){
    raw_data.gyro_xAvg += raw_data.gyro_x;
    raw_data.gyro_yAvg += raw_data.gyro_y;
    raw_data.gyro_zAvg += raw_data.gyro_z;
    zero_cnt--;
    return;
  }
  else{
    clearGlobalFlag(GYRO_CAL);
  }
}

/**
 * Функция рассчета интеграла гироскопов по времени.
 * За каждый заход надо насобирать 3 новых точки,
 * 4-я точка -- это старая, она должна стать первой в следующем заходе.
 */
void gyro_get_angle(void){

  /* Математически упрощенная функция интегрирования Симпсоном 3/8.
   * Снижение читабельности в угоду производительности.
   * Вынесем за скобки некоторые множители в обработчике прерывания:
   * 3 - количество промежутков интегрирования
   * 8 - делитель из каноничной формулы можно внести в состав GYRO_AVG_SAMPLES_CNT */
  #define s38(a, b, c, d)      ((a) + 3*((b) + (c)) + (d))

  uint32_t i = 0;
  gyrosamplecnt++;

  i = gyrosamplecnt & 3;
  gxv[i] = raw_data.gyro_x * (GYRO_AVG_SAMPLES_CNT / 8);
  gyv[i] = raw_data.gyro_y * (GYRO_AVG_SAMPLES_CNT / 8);
  gzv[i] = raw_data.gyro_z * (GYRO_AVG_SAMPLES_CNT / 8);
  if (i == 3){
    raw_data.gyro_x_delta = 3 * (s38(gxv[0],gxv[1],gxv[2],gxv[3]) - raw_data.gyro_xAvg);
    raw_data.gyro_y_delta = 3 * (s38(gyv[0],gyv[1],gyv[2],gyv[3]) - raw_data.gyro_yAvg);
    raw_data.gyro_z_delta = 3 * (s38(gzv[0],gzv[1],gzv[2],gzv[3]) - raw_data.gyro_zAvg);
    gxv[0] = gxv[3];
    gyv[0] = gyv[3];
    gzv[0] = gzv[3];

    /* у нас готовы свежие дельты углов поворота - будим инерциалку */
    chBSemSignal(&imu_sem);
  }
  #undef s38
}

/**
 * Поток для опроса хероскопа
 */
static WORKING_AREA(PollGyroThreadWA, 256);
static msg_t PollGyroThread(void *arg){

  chRegSetThreadName("PollGyro");
  (void)arg;
  msg_t sem_status = RDY_OK;

  while (TRUE) {
    sem_status = chBSemWaitTimeout(&itg3200_sem, MS2ST(20));

    txbuf[0] = GYRO_OUT_DATA;     // register address
    if (i2c_transmit(itg3200addr, txbuf, 1, rxbuf, 8) == RDY_OK &&
                                            sem_status == RDY_OK){
      raw_data.gyro_temp = complement2signed(rxbuf[0], rxbuf[1]);
      raw_data.gyro_x    = complement2signed(rxbuf[2], rxbuf[3]);
      raw_data.gyro_y    = complement2signed(rxbuf[4], rxbuf[5]);
      raw_data.gyro_z    = complement2signed(rxbuf[6], rxbuf[7]);

      if (GlobalFlags & GYRO_CAL)
        gyrozeroing();
      else
        gyro_get_angle();
    }
    else{
      /* значения, сигнализирующие о сбое */
      raw_data.gyro_temp = -32768;
      raw_data.gyro_x    = -32768;
      raw_data.gyro_y    = -32768;
      raw_data.gyro_z    = -32768;
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
void init_itg3200(void){

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint8_t i = 0;
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
  txbuf[1] = 9; /* sample rate (1000 / (9 +1)) = 100Hz*/
  txbuf[2] = GYRO_DLPF_CFG | GYRO_FS_SEL; /* диапазон измерений и частота внутреннего фильтра */
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
 * Сбрасывает рассчитанные нули и проводит калибровку заново.
 */
void gyro_refresh_zeros(void){

  chSysLock();

  raw_data.gyro_xAvg = 0;
  raw_data.gyro_yAvg = 0;
  raw_data.gyro_zAvg = 0;

  zero_cnt = GYRO_AVG_SAMPLES_CNT;
  GlobalFlags |= GYRO_CAL;

  chSysUnlock();
}

