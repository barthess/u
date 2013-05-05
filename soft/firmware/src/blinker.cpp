#include <stdlib.h>

#include "main.h"
#include "global_flags.h"

/*
 * Blinker.
 * To use blinker you have to push pointer to int16_t array to the apropriate
 * mailbox.
 *
 * Array example:
 * static const int16_t myblink[5] = {100, -100, 100, -100, 0}
 * - numbers denotes duration of pulses in milliseconds
 * - negative values switching LED off, positive - on
 * - sequence must be terminated by zero
 * - total duration of sequence must be less or equal to 1 second
 */

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
  uint32_t sum = 0;

  /* check for probable oferflow */
  i = 0;
  while (0 != seq[i]){
    sum += abs(seq[i]);
    i++;
  }
  chDbgCheck((sum <= 1000), "Blinker sequence too long");

  /* main blinker */
  i = 0;
  while (0 != seq[i]){
    if (seq[i] > 0)
      palClearPad(GPIOB, led); // on
    else
      palSetPad(GPIOB, led); // off
    chThdSleepMilliseconds(abs(seq[i]));
    i++;
  }
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

  while(true){
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

  while(true){
    status = blue_blink_mb.fetch(&rx, MS2ST(100));

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
