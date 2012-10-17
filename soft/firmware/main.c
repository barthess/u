/*                      WARNINGS!
 *
 * cmpilation without -fomit-frame-pointer cause stack overflows.
 */

/*
Hi,
I also had the same problem interfacing to an I2C device. However I solved the issue by changing the relevant outputs to open drain by editing the board.h file. Therefore palSetPadMode(i2c_gpio->sda_gpio_port, i2c_gpio->sda_gpio, PAL_MODE_ALTERNATE(4)); is still correct if your board.h file configurse these pins as opendrain.
However, I set my pins to alternate mode in board.h, which is processed before the call to i2cStart(). This works but is there any negative effect from connecting to a alternative peripheral before activating it?
Pilt

Hi,
Setting the alternate function before activating the peripheral can create problems.
For example, the USART TX line is set to zero until the clock is activated and this creates a spurious start bit if the alternate is set in board.h (before the driver is activated).
The safest way to initialize peripherals like USART and I2C is the following (I2C case).
1) In board.h set the pins as *normal* outputs with open drain and an acceptable idle logic state (idle is one for I2C if I remember well).
2) Start the peripheral clock using i2cStart(), the pins are still normal outputs and keep their idle state.
3) Now switch to alternate(4) with open drain and the pins state will go from idle to idle, no transients.
Giovanni
*/

// TODO: add autotests for I2C sensors
// TODO: logrotate functionality and log compression

// TODO: rewrite stab code in general case using aviation formulae.
// TODO: probably migrate from float32 to double in coordinate calculations.

// TODO: correct STOP handling in waypoint algorithm (incorrect realization in QGC)

// TODO: speed autosetting
// TODO: combine barometer and accelerometer in one filter.
// TODO: Power brown out handler (using ADC comparator?) for sync/umout SDC.
// TODO: Events on differnt subsystems failures (gyro_failed, gps_failed, etc.)
// TODO: One more point in dynamic pressure thermal compensation algorithm (at 60 celsius)
// TODO: Rewrite XBee code for use DMA.
// TODO: WDT with backup domain for fuckups investigation.

#include "uav.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
/* RTC-GPS sync */
BinarySemaphore rtc_sem;

/* Servo-PID sync */
BinarySemaphore servo_updated_sem;

/* store here time from GPS */
struct tm gps_timp;

/* some global flags */
GlobalFlags_t GlobalFlags;

/* EEPROM "file" */
EepromFileStream EepromFile;

/* heap for some threads */
MemoryHeap ThdHeap;
static uint8_t link_thd_buf[THREAD_HEAP_SIZE + sizeof(stkalign_t)];

/**/
uint8_t currWpFrame = MAV_FRAME_GLOBAL;

/**/
uint16_t WpSeqNew = 0;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

int main(void) {

//  nvicEnableVector(DebugMonitor_IRQn, CORTEX_PRIORITY_MASK(STM32_I2C_I2C1_IRQ_PRIORITY - 2));
//  nvicEnableVector(PendSV_IRQn, CORTEX_PRIORITY_MASK(STM32_I2C_I2C1_IRQ_PRIORITY - 2));
//  nvicEnableVector(BusFault_IRQn, CORTEX_PRIORITY_MASK(STM32_I2C_I2C1_IRQ_PRIORITY - 2));
//  nvicEnableVector(UsageFault_IRQn, CORTEX_PRIORITY_MASK(STM32_I2C_I2C1_IRQ_PRIORITY - 2));
//  nvicEnableVector(MemoryManagement_IRQn, CORTEX_PRIORITY_MASK(STM32_I2C_I2C1_IRQ_PRIORITY - 2));

  halInit();
  chSysInit();

  chBSemInit(&rtc_sem, TRUE);
  chBSemInit(&servo_updated_sem, TRUE);

  //chThdSleepMilliseconds(200);

  /* give power to all needys */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();

  chHeapInit(&ThdHeap, (uint8_t *)MEM_ALIGN_NEXT(link_thd_buf), THREAD_HEAP_SIZE);

  EepromOpen(&EepromFile);

  MavlinkDbgPrintInit();
  MsgInit();
  SanityControlInit();
  I2CInitLocal();     /* also starts EEPROM and load global parameters from it */
  MavInit();          /* mavlink constants initialization must be called after I2C init */
  ControllerInit();   /* must be started only after loading of parameters */
  LinkMgrInit();      /* after controller to reduce memory fragmentation on thread creation */
  TimekeepingInit();
  SensorsInit();      /* sensors use I2C */
  PwrMgmtInit();
  TlmSenderInit();
  MavCmdInitLocal();
  StorageInit();

  while (TRUE){
    chThdSleepMilliseconds(666);
  }

  return 0;
}

