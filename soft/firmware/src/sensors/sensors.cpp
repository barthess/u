#include "uav.h"
#include "sensors.hpp"
#include "global_flags.h"
#include "adc_local.hpp"
#include "exti_local.hpp"
#include "gps.hpp"
#include "imu.hpp"

#include "tmp75.hpp"
#include "itg3200.hpp"
#include "lsm303.hpp"
#include "mma8451.hpp"
#include "bmp085.hpp"
#include "max1236.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define GYRO_TIMEOUT        MS2ST(100)
#define ACCEL_SEM_TMO       MS2ST(100)
#define BMP085_SEM_TMO      MS2ST(100)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
RawData raw_data;
CompensatedData comp_data;
extern GlobalFlags_t GlobalFlags;

extern chibios_rt::BinarySemaphore itg3200_sem;
extern chibios_rt::BinarySemaphore lsm303_sem;
extern chibios_rt::BinarySemaphore mma8451_sem;
extern chibios_rt::BinarySemaphore bmp085_sem;
extern chibios_rt::BinarySemaphore imu_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static TMP75    tmp75(&I2CD2,   tmp75addr);
static ITG3200  itg3200(&I2CD2, itg3200addr);
static LSM303   lsm303(&I2CD2,  lsm303magaddr);
static MMA8451  mma8451(&I2CD2, mma8451addr);
static BMP085   bmp085(&I2CD2,  bmp085addr);
static MAX1236  max1236(&I2CD2, max1236addr);

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
static WORKING_AREA(PollTmp75ThreadWA, 256);
static msg_t PollTmp75Thread(void *arg){
  chRegSetThreadName("Tmp75");
  (void)arg;

  tmp75.start();
  while (!chThdShouldTerminate()) {
    chThdSleepMilliseconds(2000);
    tmp75.update();
  }
  tmp75.stop();
  chThdExit(0);
  return 0;
}

/**
 *
 */
static WORKING_AREA(PollItg3200ThreadWA, 400);
static msg_t PollItg3200Thread(void *arg){
  (void)arg;
  chRegSetThreadName("Itg3200");
  msg_t sem_status = RDY_OK;
  int32_t retry = 10;

  itg3200.start();

  while (TRUE) {
    sem_status = itg3200_sem.waitTimeout(GYRO_TIMEOUT);
    if (sem_status != RDY_OK){
      retry--;
      chDbgAssert(retry > 0, "PollGyroThread(), #1", "no interrupts from gyro");
    }
    itg3200.update();
    imu_sem.signal();
  }

  itg3200.stop();
  chThdExit(0);
  return 0;
}

/**
 *
 */
static WORKING_AREA(PollLsmThreadWA, 512); /* large stack need for sphere calc */
static msg_t PollLsmThread(void *arg){
  (void)arg;
  chRegSetThreadName("Lsm303");

  lsm303.start();

  while (!chThdShouldTerminate()){
    lsm303.update();
    lsm303_sem.waitTimeout(MS2ST(200));
  }

  lsm303.stop();
  chThdExit(0);
  return 0;
}

/**
 *
 */
static WORKING_AREA(PollAccelThreadWA, 256);
static msg_t PollAccelThread(void *arg){
  (void)arg;
  chRegSetThreadName("Mma8451");

  msg_t sem_status = RDY_OK;
  int32_t retry = 10;

  mma8451.start();

  while (!chThdShouldTerminate()) {
    sem_status = mma8451_sem.waitTimeout(ACCEL_SEM_TMO);
    if (sem_status != RDY_OK){
      retry--;
      chDbgAssert(retry > 0, "PollAccelThread(), #1",
            "probably no interrupts from accelerometer");
    }
    mma8451.update();
  }

  mma8451.stop();
  chThdExit(0);
  return 0;
}

/**
 * Polling thread
 */
static WORKING_AREA(PollBaroThreadWA, 256);
static msg_t PollBaroThread(void *arg){
  (void)arg;

  chRegSetThreadName("Bmp085");
  int32_t retry = 20;
  msg_t sem_status = RDY_OK;

  bmp085.start();
  while (!chThdShouldTerminate()) {
    sem_status = bmp085_sem.waitTimeout(BMP085_SEM_TMO);
    if (sem_status != RDY_OK){
      retry--;
      chDbgAssert(retry > 0, "PollAccelThread(), #1",
          "probably no interrupts from pressure sensor");
    }
    bmp085.update();
  }

  bmp085.stop();
  chThdExit(0);
  return 0;
}

/**
 *
 */
static WORKING_AREA(PollMax1236ThreadWA, 256);
static msg_t PollMax1236Thread(void *arg) {
  chRegSetThreadName("Max1236");
  (void)arg;

  max1236.start();
  while (!chThdShouldTerminate()) {
    chThdSleepMilliseconds(20);
    max1236.update();
  }

  max1236.stop();
  chThdExit(0);
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void SensorsInit(void){
  chDbgCheck(GlobalFlags.i2c_ready == 1, "bus not ready");

  /* EXTI start. REMEMBER! I2C slaves and RTC need EXTI.*/
  ExtiInitLocal();
  ADCInit_local();

  /* start different I2C sensors */
  chThdCreateStatic(PollAccelThreadWA,
          sizeof(PollAccelThreadWA),
          I2C_THREADS_PRIO,
          PollAccelThread,
          NULL);

  chThdCreateStatic(PollTmp75ThreadWA,
          sizeof(PollTmp75ThreadWA),
          I2C_THREADS_PRIO,
          PollTmp75Thread,
          NULL);

  chThdCreateStatic(PollItg3200ThreadWA,
          sizeof(PollItg3200ThreadWA),
          I2C_THREADS_PRIO,
          PollItg3200Thread,
          NULL);

  chThdCreateStatic(PollMax1236ThreadWA,
          sizeof(PollMax1236ThreadWA),
          I2C_THREADS_PRIO,
          PollMax1236Thread,
          NULL);

  chThdCreateStatic(PollLsmThreadWA,
          sizeof(PollLsmThreadWA),
          I2C_THREADS_PRIO,
          PollLsmThread,
          NULL);

  chThdCreateStatic(PollBaroThreadWA,
          sizeof(PollBaroThreadWA),
          I2C_THREADS_PRIO,
          PollBaroThread,
          NULL);

  ImuInit(&imu_sem);
  GPSInit();
}

