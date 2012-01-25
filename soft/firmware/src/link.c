#include "ch.h"
#include "hal.h"

#include "link.h"
#include "rtc.h"
#include "message.h"

#include <mavlink.h>
#include <bart.h>
#include <common.h>

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define LINKSD SD2

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern Mailbox tolink_mb;

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

// Define the system type, in this case an airplane
//static uint8_t system_type     = MAV_TYPE_GROUND_ROVER;
//static uint8_t autopilot_type  = MAV_AUTOPILOT_GENERIC;
//static uint8_t system_mode     = MAV_MODE_PREFLIGHT; ///< Booting up
//static uint32_t custom_mode    = 0;                 ///< Custom mode, can be defined by user/adopter
//static uint8_t system_state    = MAV_STATE_STANDBY; ///< System ready for flight


static WORKING_AREA(LinkOutThreadWA, 1024);
static msg_t LinkOutThread(void *arg){
  chRegSetThreadName("MAVLinkOut");
  (void)arg;

  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len = 0;
  Mail* tolinkmailp = NULL;
  msg_t tmp = 0;

  while (TRUE) {
    chMBFetch(&tolink_mb, &tmp, TIME_INFINITE);
    tolinkmailp = (Mail*)tmp;
    len = mavlink_msg_to_send_buffer(buf, tolinkmailp->payload);
    sdWrite(&LINKSD, buf, len);
  }

  return 0;
}


static WORKING_AREA(LinkInThreadWA, 1024);
static msg_t LinkInThread(void *arg){
  chRegSetThreadName("MAVLinkIn");
  (void)arg;
  while (TRUE) {
    chThdSleepMilliseconds(666);
  }
  return 0;
}


static SerialConfig xbee_ser_cfg = {
    BAUDRATE_XBEE,
    0,
    0,
    USART_CR3_CTSE,
};



void LinkInit(void){

  /* запуск на дефолтной частоте */
  sdStart(&LINKSD, &xbee_ser_cfg);

  chThdSleepMilliseconds(3000);   /* ждем, пока модемы встанут в ружьё */

  chThdCreateStatic(LinkOutThreadWA,
          sizeof(LinkOutThreadWA),
          NORMALPRIO,
          LinkOutThread,
          NULL);

  chThdCreateStatic(LinkInThreadWA,
          sizeof(LinkInThreadWA),
          NORMALPRIO,
          LinkInThread,
          NULL);
}






