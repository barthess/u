#include "ch.h"
#include "hal.h"

#include "sensors.h"
#include "message.h"

#include "mavsender.h"
#include "imu.h"
#include "gps.h"
#include "adc_pns.h"
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
RawData raw_data;                     /* структура с сырыми данными с датчиков */
CompensatedData comp_data;            /* обработанные данные */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/* примитивы для синхронизации потока с прерываниеми от датчиков */
static BinarySemaphore mag3110_sem;
static BinarySemaphore mma8451_sem;
static BinarySemaphore bmp085_sem;
static BinarySemaphore itg3200_sem;

/* семафор для синхронизации инерциалки и датчиков */
static BinarySemaphore imu_sem;

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

  /* инициализация семафоров */
  chBSemInit(&mag3110_sem,  TRUE);
  chBSemInit(&mma8451_sem,  TRUE);
  chBSemInit(&bmp085_sem,   TRUE);
  chBSemInit(&itg3200_sem,  TRUE);
  chBSemInit(&imu_sem,      TRUE);

  /* Запуск контроллера внешних прерываний.
   * ПОМНИ! I2C-датчики и RTC используют его */
  ExtiInitLocal(&mag3110_sem, &mma8451_sem, &bmp085_sem, &itg3200_sem);
  ADCInit_pns();

  /* start I2C sensors */
  init_itg3200(&itg3200_sem, &imu_sem);
  init_mma8451(&mma8451_sem);
  init_tmp75();
  init_max1236();
  init_mag3110(&mag3110_sem);
  init_bmp085(&bmp085_sem);

  ImuInit(&imu_sem);
  GPSInit();

  MavSenderInit();
}

