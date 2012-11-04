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
extern CompensatedData comp_data;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[ACCEL_RX_DEPTH];
static uint8_t txbuf[ACCEL_TX_DEPTH];

/* указатели в структуре с параметрами */
static int32_t  const *xoffset,   *yoffset,   *zoffset;
static int32_t  const *xpol,      *ypol,      *zpol;
static uint32_t const *xsens,     *ysens,     *zsens;
static uint32_t const *still_thr, *sortmtrx;

static bool_t DeviceStill = FALSE;

static int32_t Acc[3] = {0,0,0};
static int32_t prevAcc[3] = {0,0,0};/* variable to check still device or not */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Функция может только СБРОСИТЬ флаг неподвижности, взводить его нужно вручную.
 */
void __is_device_still(int32_t *prevAcc, int32_t *Acc){
  uint32_t delta = 0;

  if (!DeviceStill)
    return;

  for (uint32_t i = 0; i < 3; i++){
    delta += (prevAcc[i] - Acc[i]) * (prevAcc[i] - Acc[i]);
  }
  delta  = isqrt(delta);
  delta  = (delta * 1000000) / *xsens; // get acceleration delta in micro g
  if (delta > *still_thr){
    chSysLock();
    DeviceStill = FALSE;
    chSysUnlock();
  }
}

/**
 *
 */
static void process_accel_data(uint8_t *rxbuf){
  /* save previouse values */
  for (uint32_t i = 0; i < 3; i++)
    prevAcc[i] = Acc[i];

  int32_t  raw[3];
  raw[0] = complement2signed(rxbuf[1], rxbuf[2]);
  raw[1] = complement2signed(rxbuf[3], rxbuf[4]);
  raw[2] = complement2signed(rxbuf[5], rxbuf[6]);
  sorti_3values(raw, Acc, *sortmtrx);

  Acc[0] *= *xpol;
  Acc[1] *= *ypol;
  Acc[2] *= *zpol;

  __is_device_still(prevAcc, Acc);

  comp_data.xacc = (1000 * (Acc[0] + *xoffset)) / *xsens;
  comp_data.yacc = (1000 * (Acc[1] + *yoffset)) / *ysens;
  comp_data.zacc = (1000 * (Acc[2] + *zoffset)) / *zsens;

  /* fill scaled debug structures */
  mavlink_raw_imu_struct.xacc = Acc[0];
  mavlink_raw_imu_struct.yacc = Acc[1];
  mavlink_raw_imu_struct.zacc = Acc[2];
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
  }
  return 0;
}

/**
 *
 */
static void __search_indexes(void){
  sortmtrx  = ValueSearch("ACC_sortmtrx");

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

/**
 *
 */
static void __hard_init_short(void){
}

/**
 *
 */
static void __hard_init_full(void){
    /* Помни о том, что большинство конфигурационных регистров нельзя менять
   в активном режиме, надо сначала свалить девайс в STANDBY. */

  // TODO: run autodiagnostic

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
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
/**
 *
 */
void init_mma8451(BinarySemaphore *mma8451_semp){

  __search_indexes();

  if (need_full_init())
    __hard_init_full();
  else
    __hard_init_short();

  chThdCreateStatic(PollAccelThreadWA,
          sizeof(PollAccelThreadWA),
          I2C_THREADS_PRIO,
          PollAccelThread,
          mma8451_semp);
}

/**
 *
 */
bool_t IsDeviceStill(void){
  return DeviceStill;
}

/**
 * Raise still flag
 */
void DeviceStillSet(void){
  chSysLock();
  DeviceStill = TRUE;
  chSysUnlock();
}


