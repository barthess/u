#include "ch.h"
#include "hal.h"

#include "link.h"
#include "rtc.h"
#include "message.h"

#include <mavlink.h>
#include <common.h>
#include <bart.h>

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
//extern LogItem log_item;

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






static WORKING_AREA(LinkThreadWA, 1024);
static msg_t LinkThread(void *arg){
  chRegSetThreadName("MAVLink");
  (void)arg;

  mavlink_system_t mavlink_system;

  mavlink_system.sysid  = 20;                   ///< ID 20 for this airplane
  mavlink_system.compid = MAV_COMP_ID_IMU;     ///< The component sending the message is the IMU, it could be also a Linux process
  mavlink_system.type   = MAV_TYPE_FIXED_WING;   ///< This system is an airplane / fixed wing

  // Define the system type, in this case an airplane
//  uint8_t system_type     = MAV_TYPE_GROUND_ROVER;
//  uint8_t autopilot_type  = MAV_AUTOPILOT_GENERIC;
//  uint8_t system_mode     = MAV_MODE_PREFLIGHT; ///< Booting up
//  uint32_t custom_mode    = 0;                 ///< Custom mode, can be defined by user/adopter
//  uint8_t system_state    = MAV_STATE_STANDBY; ///< System ready for flight

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  mavlink_bart_servo_tuning_t raw;

  uint16_t len = 0;
  while (TRUE) {
    chThdSleepMilliseconds(40);

    mavlink_msg_uvvu_bart_servo_tuning_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &raw);
    len = mavlink_msg_to_send_buffer(buf, &msg);
    sdWrite(&LINKSD, buf, len);
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

  chThdCreateStatic(LinkThreadWA,
          sizeof(LinkThreadWA),
          NORMALPRIO,
          LinkThread,
          NULL);
}






