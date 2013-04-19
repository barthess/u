#include "uav.h"
#include "sensors.hpp"
#include "global_flags.h"
#include "adc_local.hpp"
#include "exti_local.hpp"
#include "gps.hpp"
#include "imu.hpp"
#include "tmp75.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
RawData raw_data;
CompensatedData comp_data;
extern GlobalFlags_t GlobalFlags;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/* semaphores to sync with external interrupts from sensors */
static chibios_rt::BinarySemaphore mag3110_sem(true);
static chibios_rt::BinarySemaphore mma8451_sem(true);
static chibios_rt::BinarySemaphore bmp085_sem(true);
static chibios_rt::BinarySemaphore itg3200_sem(true);
static chibios_rt::BinarySemaphore lsm303_sem(true);

/* sem for sync IMU with gyro */
static chibios_rt::BinarySemaphore imu_sem(true);





static Tmp75 tmp75(&I2CD2, tmp75addr);

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

  while (!chThdShouldTerminate()) {
    chThdSleepMilliseconds(2000);
    tmp75.update();
  }
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
  ExtiInitLocal(&mag3110_sem, &mma8451_sem, &bmp085_sem, &itg3200_sem, &lsm303_sem);
  ADCInit_local();

  /* start different I2C sensors */
//  init_mma8451(&mma8451_sem);

  chThdCreateStatic(PollTmp75ThreadWA,
          sizeof(PollTmp75ThreadWA),
          I2C_THREADS_PRIO,
          PollTmp75Thread,
          NULL);


//  init_max1236();
//  init_lsm303(&lsm303_sem);
//  init_bmp085(&bmp085_sem);
//  init_itg3200(&itg3200_sem, &imu_sem);
//
  ImuInit(&imu_sem);
  GPSInit();
}

