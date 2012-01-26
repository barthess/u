
/* Следит за состоянием здоровья органов.*/

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"

#include <mavlink.h>
#include <common.h>
#include <bart.h>

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;
//extern RawData raw_data;
extern Mailbox tolink_mb;
extern mavlink_heartbeat_t mavlink_heartbeat_struct;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

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
static WORKING_AREA(SanityControlThreadWA, 256);
static msg_t SanityControlThread(void *arg) {
  chRegSetThreadName("Sanity");
  (void)arg;

  Mail tolink_mail = {NULL, MAVLINK_MSG_ID_HEARTBEAT, NULL};

  while (TRUE) {
    palSetPad(GPIOB, GPIOB_LED_R);
    chThdSleepMilliseconds(950);

    if (tolink_mail.payload == NULL){
      clear_flag(POSTAGE_FAILED);

      tolink_mail.payload = &mavlink_heartbeat_struct;
      chMBPost(&tolink_mb, (msg_t)&tolink_mail, TIME_IMMEDIATE);

      palClearPad(GPIOB, GPIOB_LED_R); /* blink*/
      chThdSleepMilliseconds(50);
    }
    else
      set_flag(POSTAGE_FAILED);

  }
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void SanityControlInit(void){

  mavlink_heartbeat_struct.autopilot = MAV_AUTOPILOT_GENERIC;

  chThdCreateStatic(SanityControlThreadWA,
          sizeof(SanityControlThreadWA),
          NORMALPRIO,
          SanityControlThread,
          NULL);
}

