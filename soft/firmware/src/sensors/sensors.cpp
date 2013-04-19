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

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define GYRO_TIMEOUT        MS2ST(100)
#define ACCEL_SEM_TMO       MS2ST(100)

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

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static TMP75    tmp75(&I2CD2, tmp75addr);
static ITG3200  itg3200(&I2CD2, itg3200addr);
static LSM303   lsm303(&I2CD2, lsm303magaddr);
static MMA8451  mma8451(&I2CD2, mma8451addr);

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
static WORKING_AREA(PollGyroThreadWA, 400);
static msg_t PollGyroThread(void *arg){
  (void)arg;
  chRegSetThreadName("PollGyro");
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
  chRegSetThreadName("PollLsm303");

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
  chRegSetThreadName("PollAccel");

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

  chThdCreateStatic(PollGyroThreadWA,
          sizeof(PollGyroThreadWA),
          I2C_THREADS_PRIO,
          PollGyroThread,
          NULL);

//  init_max1236();
  chThdCreateStatic(PollLsmThreadWA,
        sizeof(PollLsmThreadWA),
        I2C_THREADS_PRIO,
        PollLsmThread,
        NULL);

//  init_bmp085(&bmp085_sem);


  chDbgPanic("this argument must not be NULL");
  ImuInit(NULL);
  GPSInit();
}

