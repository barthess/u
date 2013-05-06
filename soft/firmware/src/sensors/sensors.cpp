#include "main.h"
#include "sensors.hpp"
#include "global_flags.h"
#include "adc_local.hpp"
#include "exti_local.hpp"
#include "gps.hpp"
#include "imu.hpp"
#include "speedometer.hpp"

#include "tmp75.hpp"
#include "bmp085.hpp"
#include "max1236.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
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
extern chibios_rt::BinarySemaphore bmp085_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static TMP75    tmp75(&I2CD2,   tmp75addr);
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
  ADCInitLocal();

  /* start different I2C sensors */
  chThdCreateStatic(PollTmp75ThreadWA,
          sizeof(PollTmp75ThreadWA),
          I2C_THREADS_PRIO,
          PollTmp75Thread,
          NULL);

  chThdCreateStatic(PollMax1236ThreadWA,
          sizeof(PollMax1236ThreadWA),
          I2C_THREADS_PRIO,
          PollMax1236Thread,
          NULL);

  chThdCreateStatic(PollBaroThreadWA,
          sizeof(PollBaroThreadWA),
          I2C_THREADS_PRIO,
          PollBaroThread,
          NULL);

  SpeedometerInit();
  GPSInit();
}

