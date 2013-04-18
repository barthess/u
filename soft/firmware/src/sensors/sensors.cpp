#include "uav.h"
#include "sensors.hpp"
#include "global_flags.h"

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
static chibios_rt::BinarySemaphore mag3110_sem;
static chibios_rt::BinarySemaphore mma8451_sem;
static chibios_rt::BinarySemaphore bmp085_sem;
static chibios_rt::BinarySemaphore itg3200_sem;
static chibios_rt::BinarySemaphore lsm303_sem;

/* sem for sync IMU with gyro */
static chibios_rt::BinarySemaphore imu_sem;
chibios_rt::BinarySemaphore imu_sem__;

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

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void SensorsInit(void){

  chDbgCheck(GlobalFlags.i2c_ready == 1, "bus not ready");


  chDbgPanic("uncomment next lines");

  /* EXTI start. REMEMBER! I2C slaves and RTC need EXTI.*/
//  ExtiInitLocal(&mag3110_sem, &mma8451_sem, &bmp085_sem, &itg3200_sem, &lsm303_sem);
  ADCInit_local();

  /* start different I2C sensors */
//  init_mma8451(&mma8451_sem);
//  init_tmp75();
//  init_max1236();
//  init_lsm303(&lsm303_sem);
//  init_bmp085(&bmp085_sem);
//  init_itg3200(&itg3200_sem, &imu_sem);
//
//  ImuInit(&imu_sem);
  GPSInit();
}

