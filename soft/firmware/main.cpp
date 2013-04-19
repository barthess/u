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

// TODO: save DCM in bkp for faster startup after panic recovery
// TODO: params in bkp
// TODO: gyro update period in bkp
// TODO: save mission data in bkp for recovery if panic occured during mission

// TODO: log compressed format
// TODO: cli for format, ls, rm

// TODO: rewrite stab code in general case using aviation formulae.
// TODO: probably migrate from float32 to double in coordinate calculations.

// TODO: correct STOP handling in waypoint algorithm (incorrect realization in QGC)

// TODO: speed autosetting
// TODO: combine barometer and accelerometer in one filter.
// TODO: Power brown out handler (using ADC comparator on power supply pin?) for sync/umout SDC.
// TODO: One more point in dynamic pressure thermal compensation algorithm (at +60 celsius)
// TODO: Rewrite XBee code for use DMA.
// TODO: WDT?

#include <time.h>

#include "uav.h"
#include "global_flags.h"
#include "fault_handlers.h"
#include "message.hpp"
#include "gps.hpp"
#include "sanity.hpp"
#include "i2c_local.hpp"
#include "eeprom_file_tree.hpp"
#include "param.hpp"
#include "timekeeping.hpp"
#include "sensors.hpp"
#include "pwr_mgmt.hpp"
#include "microsd.hpp"
//#include "controller.hpp"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
/* RTC-GPS sync */
chibios_rt::BinarySemaphore rtc_sem(true);

/* Servo-PID sync */
chibios_rt::BinarySemaphore servo_updated_sem(true);

/* store here time from GPS */
struct tm gps_timp;

/* some global flags */
GlobalFlags_t GlobalFlags = {0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0};

/* heap for some threads */
MemoryHeap ThdHeap;
static uint8_t link_thd_buf[THREAD_HEAP_SIZE + sizeof(stkalign_t)];

/**/
uint8_t currWpFrame = MAV_FRAME_GLOBAL;

/* new waypoint number for overwrite current */
uint16_t WpSeqNew = 0;

/* save here flags before clear them from MCU register */
uint32_t LastResetFlags;

/* semaphores to sync with external interrupts from sensors */
chibios_rt::BinarySemaphore mma8451_sem(true);
chibios_rt::BinarySemaphore bmp085_sem(true);
chibios_rt::BinarySemaphore itg3200_sem(true);
chibios_rt::BinarySemaphore lsm303_sem(true);

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
  halInit();
  System::init();

  /* enable softreset on panic */
  setGlobalFlag(GlobalFlags.allow_softreset);
  if (was_softreset() || was_padreset()){
    chThdSleepMilliseconds(1);
  }
  else
    chThdSleepMilliseconds(100);

  /* give power to all needys */
  pwr5v_power_on();
  gps_power_on();
  xbee_reset_clear();
  xbee_sleep_clear();

  chHeapInit(&ThdHeap, (uint8_t *)MEM_ALIGN_NEXT(link_thd_buf), THREAD_HEAP_SIZE);

  MsgInit();
  SanityControlInit();
  I2CInitLocal();
  EepromFileTreeInit();
  ParametersInit();   /* read parameters from EEPROM via I2C*/
  MavInit();          /* mavlink constants initialization must be called after parameters init */
//  ControllerInit();   /* must be started only after loading of parameters */
//  LinkMgrInit();      /* launch after controller to reduce memory fragmentation on thread creation */
  TimekeepingInit();
  SensorsInit();      /* Note. Sensors depends on I2C */
  PwrMgmtInit();
//  TlmSenderInit();
//  MavCmdInitLocal();
  StorageInit();

  /**/
  LastResetFlags = RCC->CSR;
  clear_reset_flags();

  while (TRUE){
    chThdSleepMilliseconds(666);
  }

  return 0;
}

