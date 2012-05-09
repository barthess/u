#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "sensors.h"
#include "i2c_pns.h"
#include "utils.h"
#include "mma8451.h"
#include "message.h"
#include "param.h"
#include "main.h"
#include "link.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define mma8451addr 0b0011100

#define XPOL          (global_data[xpol_index].value)
#define YPOL          (global_data[ypol_index].value)
#define ZPOL          (global_data[zpol_index].value)

#define XSENS         (global_data[xsens_index].value)
#define YSENS         (global_data[ysens_index].value)
#define ZSENS         (global_data[zsens_index].value)

#define XOFFSET       (global_data[xoffset_index].value)
#define YOFFSET       (global_data[yoffset_index].value)
#define ZOFFSET       (global_data[zoffset_index].value)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern GlobalParam_t global_data[];
extern RawData raw_data;
extern CompensatedData comp_data;
extern EventSource pwrmgmt_event;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[ACCEL_RX_DEPTH];
static uint8_t txbuf[ACCEL_TX_DEPTH];

/* индексы в структуре с параметрами */
static uint32_t xoffset_index, yoffset_index, zoffset_index;
static uint32_t xsens_index,   ysens_index,   zsens_index;
static uint32_t xpol_index,    ypol_index,    zpol_index;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/* Поток для запроса акселерометра */
static WORKING_AREA(PollAccelThreadWA, 512);
static msg_t PollAccelThread(void *semp){
  chRegSetThreadName("PollAccel");

  msg_t sem_status = RDY_OK;

  struct EventListener self_el;
  chEvtRegister(&pwrmgmt_event, &self_el, PWRMGMT_SIGHALT_EVID);

  while (TRUE) {
    sem_status = chBSemWaitTimeout((BinarySemaphore*)semp, MS2ST(20));
    txbuf[0] = ACCEL_STATUS;
    if ((i2c_transmit(mma8451addr, txbuf, 1, rxbuf, 7) == RDY_OK) && (sem_status == RDY_OK)){
      raw_data.xacc = complement2signed(rxbuf[1], rxbuf[2]);
      raw_data.yacc = complement2signed(rxbuf[3], rxbuf[4]);
      raw_data.zacc = complement2signed(rxbuf[5], rxbuf[6]);

      /* there is no need of correcting of placement. Just get milli g */
      mavlink_raw_imu_struct.xacc = raw_data.xacc * XPOL;
      mavlink_raw_imu_struct.yacc = raw_data.yacc * YPOL;
      mavlink_raw_imu_struct.zacc = raw_data.zacc * ZPOL;
      comp_data.xacc = 1000 * (((int32_t)raw_data.xacc) * XPOL + XOFFSET) / XSENS;
      comp_data.yacc = 1000 * (((int32_t)raw_data.yacc) * YPOL + YOFFSET) / YSENS;
      comp_data.zacc = 1000 * (((int32_t)raw_data.zacc) * ZPOL + ZOFFSET) / ZSENS;

      /* fill scaled debug struct */
      mavlink_scaled_imu_struct.xacc = comp_data.xacc;
      mavlink_scaled_imu_struct.yacc = comp_data.yacc;
      mavlink_scaled_imu_struct.zacc = comp_data.zacc;
    }
    else{
      raw_data.xacc = -32768;
      raw_data.yacc = -32768;
      raw_data.zacc = -32768;
      mavlink_raw_imu_struct.xacc = -32768;
      mavlink_raw_imu_struct.yacc = -32768;
      mavlink_raw_imu_struct.zacc = -32768;
      mavlink_scaled_imu_struct.xacc = -32768;
      mavlink_scaled_imu_struct.yacc = -32768;
      mavlink_scaled_imu_struct.zacc = -32768;
    }

    if (chThdSelf()->p_epending & EVENT_MASK(PWRMGMT_SIGHALT_EVID))
      chThdExit(RDY_OK);
  }
  return 0;
}

/**
 * Поиск индексов в массиве настроек
 */
static void search_indexes(void){
  int32_t i = -1;

  kvs(ACC, xoffset);
  kvs(ACC, yoffset);
  kvs(ACC, zoffset);
  kvs(ACC, xsens);
  kvs(ACC, ysens);
  kvs(ACC, zsens);
  kvs(ACC, xpol);
  kvs(ACC, ypol);
  kvs(ACC, zpol);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void init_mma8451(BinarySemaphore *mma8451_semp){

  search_indexes();

  /* Помни о том, что большинство конфигурационных регистров нельзя менять
   в активном режиме, надо сначала свалить девайс в STANDBY. */

  // TODO: сначала вообще убедиться, что девайс отвечает путем запроса его WHOAMI
  // TODO: запустить в нем самодиагностику

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint32_t i = 0;
    for (i = 0; i < ACCEL_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < ACCEL_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  txbuf[0] = ACCEL_CTRL_REG2;
  txbuf[1] = 0b100000; //Reset
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(4);
  txbuf[0] = ACCEL_CTRL_REG1;
  txbuf[1] = 0b0; //set standby to allow configure device
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(4);
  txbuf[0] = ACCEL_XYZ_DATA_CFG;
  txbuf[1] = (uint8_t)(ACCEL_SENS >> 2);
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(4);
  txbuf[0] = ACCEL_CTRL_REG2;
  txbuf[1] = 0b10; //High Resolution
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(4);
  txbuf[0] = ACCEL_CTRL_REG3;
  txbuf[1] = 0b10; //Interrupt active high
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(4);
  txbuf[0] = ACCEL_CTRL_REG4;
  txbuf[1] = 0b01; //Interrupt on data ready
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(4);
  txbuf[0] = ACCEL_CTRL_REG1;
  //txbuf[1] = 0b11101; //100Hz, low noice, active
  //txbuf[1] = 0b11001; //100Hz, normal noice, active
  txbuf[1] = 0b100101; //50Hz, low noice, active
  while (i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  chThdCreateStatic(PollAccelThreadWA,
          sizeof(PollAccelThreadWA),
          I2C_THREADS_PRIO,
          PollAccelThread,
          mma8451_semp);
  chThdSleepMilliseconds(1);
}


