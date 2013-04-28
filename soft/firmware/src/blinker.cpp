#include <stdlib.h>

#include "uav.h"
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
extern GlobalFlags_t GlobalFlags;
extern chibios_rt::Mailbox red_blink_mb;
extern chibios_rt::Mailbox blue_blink_mb;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

/**
 *
 */
void blink_cycle(int16_t *seq, uint32_t led){
  uint32_t i = 0;
  while (0 != seq[i]){
    /* check for probable oferflow */
    chDbgCheck((abs(seq[i]) <= 500), "Are you forgot terminating zero?");

    if (seq[i] > 0)
      palClearPad(GPIOB, led); // on
    else
      palSetPad(GPIOB, led); // off
    chThdSleepMilliseconds(abs(seq[i]));
    i++;
  }
  palSetPad(GPIOB, GPIOB_LED_R); // off
}

/**
 * Blinker thread for red LED.
 */
static WORKING_AREA(RedBlinkThreadWA, 192);
static msg_t RedBlinkThread(void *arg) {
  chRegSetThreadName("RedBlink");
  (void)arg;
  msg_t rx = 0;
  msg_t status = RDY_RESET;

  while(!chThdShouldTerminate()){
    status = red_blink_mb.fetch(&rx, MS2ST(100));

    if (RDY_OK == status){
      blink_cycle((int16_t *)rx, GPIOB_LED_R);
    }
  }
  return 0;
}

/**
 * Blinker thread for red LED.
 */
static WORKING_AREA(BlueBlinkThreadWA, 192);
static msg_t BlueBlinkThread(void *arg) {
  chRegSetThreadName("BlueBlink");
  (void)arg;
  msg_t rx = 0;
  msg_t status = RDY_RESET;

  while(!chThdShouldTerminate()){
    status = red_blink_mb.fetch(&rx, MS2ST(100));

    if (RDY_OK == status){
      blink_cycle((int16_t *)rx, GPIOB_LED_B);
    }
  }
  return 0;
}
/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */
void BlinkerInit(void){
  chThdCreateStatic(RedBlinkThreadWA,
          sizeof(RedBlinkThreadWA),
          NORMALPRIO - 10,
          RedBlinkThread,
          NULL);

  chThdCreateStatic(BlueBlinkThreadWA,
          sizeof(BlueBlinkThreadWA),
          NORMALPRIO - 10,
          BlueBlinkThread,
          NULL);

  setGlobalFlag(GlobalFlags.blinker_ready);
}
