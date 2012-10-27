#include "ch.h"
#include "hal.h"

#include "sensors.h"
#include "message.h"

#include "imu.h"
#include "gps.h"
#include "adc_local.h"
#include "exti_local.h"
#include "itg3200.h"
#include "mma8451.h"
#include "tmp75.h"
#include "max1236.h"
#include "bmp085.h"
#include "mag3110.h"

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

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/* semaphores to sync with external interrupts from sensors */
static BinarySemaphore mag3110_sem;
static BinarySemaphore mma8451_sem;
static BinarySemaphore bmp085_sem;
static BinarySemaphore itg3200_sem;

/* sem for sync IMU with gyro */
static BinarySemaphore imu_sem;
BinarySemaphore imu_sem__;
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

  chBSemInit(&mag3110_sem,  TRUE);
  chBSemInit(&mma8451_sem,  TRUE);
  chBSemInit(&bmp085_sem,   TRUE);
  chBSemInit(&itg3200_sem,  TRUE);
  chBSemInit(&imu_sem,      TRUE);

  /* EXTI start. REMEMBER! I2C slaves and RTC need EXTI.*/
  ExtiInitLocal(&mag3110_sem, &mma8451_sem, &bmp085_sem, &itg3200_sem);
  ADCInit_local();

  /* start different I2C sensors */
  init_mma8451(&mma8451_sem);
  init_tmp75();
  init_max1236();
  init_mag3110(&mag3110_sem);
  init_bmp085(&bmp085_sem);
  init_itg3200(&itg3200_sem, &imu_sem);

  ImuInit(&imu_sem);
  GPSInit();
}

