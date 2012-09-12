#include <stdlib.h>

#include "uav.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define mma8451addr       0b0011100
#define ACCEL_SEM_TMO     MS2ST(100)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern RawData raw_data;
extern CompensatedData comp_data;
extern uint32_t GlobalFlags;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[ACCEL_RX_DEPTH];
static uint8_t txbuf[ACCEL_TX_DEPTH];

/* указатели в структуре с параметрами */
static int32_t const  *xoffset, *yoffset, *zoffset;
static int32_t const  *xpol,    *ypol,    *zpol;
static uint32_t const *xsens,   *ysens,   *zsens;
static uint32_t const *still_thr;

static bool_t DeviceStill = FALSE;

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
static void process_accel_data(uint8_t *rxbuf){
  int16_t prevx, prevy, prevz;
  uint32_t delta;

  /* save previouse values */
  prevx = raw_data.xacc;
  prevy = raw_data.yacc;
  prevz = raw_data.zacc;

  raw_data.xacc = complement2signed(rxbuf[1], rxbuf[2]);
  raw_data.yacc = complement2signed(rxbuf[3], rxbuf[4]);
  raw_data.zacc = complement2signed(rxbuf[5], rxbuf[6]);

  delta  = (prevx - raw_data.xacc) * (prevx - raw_data.xacc);
  delta += (prevy - raw_data.yacc) * (prevy - raw_data.yacc);
  delta += (prevz - raw_data.zacc) * (prevz - raw_data.zacc);
  if (delta > *still_thr)
    DeviceStill = FALSE;

  /* there is no need of correcting of placement. Just get milli g */
  mavlink_raw_imu_struct.xacc = raw_data.xacc * *xpol;
  mavlink_raw_imu_struct.yacc = raw_data.yacc * *ypol;
  mavlink_raw_imu_struct.zacc = raw_data.zacc * *zpol;

  comp_data.xacc = (1000 * (((int32_t)raw_data.xacc) * *xpol + *xoffset)) / *xsens;
  comp_data.yacc = (1000 * (((int32_t)raw_data.yacc) * *ypol + *yoffset)) / *ysens;
  comp_data.zacc = (1000 * (((int32_t)raw_data.zacc) * *zpol + *zoffset)) / *zsens;

  /* fill scaled debug struct */
  mavlink_scaled_imu_struct.xacc = comp_data.xacc;
  mavlink_scaled_imu_struct.yacc = comp_data.yacc;
  mavlink_scaled_imu_struct.zacc = comp_data.zacc;
}

/**
 *
 */
static WORKING_AREA(PollAccelThreadWA, 256);
static msg_t PollAccelThread(void *semp){
  chRegSetThreadName("PollAccel");

  msg_t sem_status = RDY_OK;
  int32_t retry = 10;

  while (TRUE) {
    sem_status = chBSemWaitTimeout((BinarySemaphore*)semp, ACCEL_SEM_TMO);
    if (sem_status != RDY_OK){
      retry--;
      chDbgAssert(retry > 0, "PollAccelThread(), #1",
          "probably no interrupts from accelerometer");
    }

    txbuf[0] = ACCEL_STATUS;
    i2c_transmit(mma8451addr, txbuf, 1, rxbuf, 7);
    process_accel_data(rxbuf);

    if (GlobalFlags & SIGHALT_FLAG)
      chThdExit(RDY_OK);
  }
  return 0;
}

/**
 *
 */
static void search_indexes(void){
  xoffset   = ValueSearch("ACC_xoffset");
  yoffset   = ValueSearch("ACC_yoffset");
  zoffset   = ValueSearch("ACC_zoffset");
  xpol      = ValueSearch("ACC_xpol");
  ypol      = ValueSearch("ACC_ypol");
  zpol      = ValueSearch("ACC_zpol");
  xsens     = ValueSearch("ACC_xsens");
  ysens     = ValueSearch("ACC_ysens");
  zsens     = ValueSearch("ACC_zsens");
  still_thr = ValueSearch("IMU_still_thr");
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
bool_t is_device_still(void){
  return DeviceStill;
}

/**
 * Raise still flag
 */
void device_still_clear(void){
  DeviceStill = TRUE;
}

/**
 *
 */
void init_mma8451(BinarySemaphore *mma8451_semp){

  search_indexes();

  /* Помни о том, что большинство конфигурационных регистров нельзя менять
   в активном режиме, надо сначала свалить девайс в STANDBY. */

  // TODO: run autodiagnostic

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint32_t i = 0;
    for (i = 0; i < ACCEL_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < ACCEL_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  txbuf[0] = ACCEL_WHOAMI;
  i2c_transmit(mma8451addr, txbuf, 1, rxbuf, 1);
  chDbgAssert(rxbuf[0] == ACCEL_WHOAMI_VALUE, "init_mma8451(), #1",
                                    "accelerometer did not respond");

  txbuf[0] = ACCEL_CTRL_REG2;
  txbuf[1] = 0b100000; //Reset
  i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(8);

  txbuf[0] = ACCEL_CTRL_REG1;
  txbuf[1] = 0b0; //set standby to allow configure device
  i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(2);

  txbuf[0] = ACCEL_XYZ_DATA_CFG;
  txbuf[1] = (uint8_t)(ACCEL_SENS >> 2);
  i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(2);

  txbuf[0] = ACCEL_CTRL_REG2;
  txbuf[1] = 0b10; //High Resolution
  txbuf[2] = 0b10; //Interrupt active high
  txbuf[3] = 0b01; //Interrupt on data ready
  i2c_transmit(mma8451addr, txbuf, 4, rxbuf, 0);
  chThdSleepMilliseconds(2);

  txbuf[0] = ACCEL_CTRL_REG1;
  txbuf[1] = 0b11101; //100Hz, low noice, active
  //txbuf[1] = 0b11001; //100Hz, normal noice, active
  //txbuf[1] = 0b100101; //50Hz, low noice, active
  i2c_transmit(mma8451addr, txbuf, 2, rxbuf, 0);
  chThdSleepMilliseconds(2);

  chThdCreateStatic(PollAccelThreadWA,
          sizeof(PollAccelThreadWA),
          I2C_THREADS_PRIO,
          PollAccelThread,
          mma8451_semp);
  chThdSleepMilliseconds(1);
}


