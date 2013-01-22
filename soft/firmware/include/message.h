#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <mavlink.h>
#include <common.h>

/* output messages events */
#define EVMSK_MAVLINK_OUT_HEARTBEAT                         (1UL << 0)
#define EVMSK_MAVLINK_OUT_GPS_RAW_INT                       (1UL << 1)
#define EVMSK_MAVLINK_OUT_GLOBAL_POSITION_INT               (1UL << 2)
#define EVMSK_MAVLINK_OUT_SYSTEM_TIME                       (1UL << 4)
#define EVMSK_MAVLINK_OUT_SYS_STATUS                        (1UL << 5)
#define EVMSK_MAVLINK_OUT_STATUSTEXT                        (1UL << 6)
#define EVMSK_MAVLINK_OUT_PARAM_VALUE                       (1UL << 7)
#define EVMSK_MAVLINK_OUT_COMMAND_ACK                       (1UL << 8)
#define EVMSK_MAVLINK_OUT_RC_CHANNELS_RAW                   (1UL << 9)
#define EVMSK_MAVLINK_OUT_MISSION_ACK                       (1UL << 10)
#define EVMSK_MAVLINK_OUT_MISSION_CURRENT                   (1UL << 11)
#define EVMSK_MAVLINK_OUT_MISSION_ITEM_REACHED              (1UL << 12)

/* input messages events */
#define EVMSK_MAVLINK_IN_PARAM_SET                          (1UL << 20)
#define EVMSK_MAVLINK_IN_PARAM_REQUEST_LIST                 (1UL << 21)
#define EVMSK_MAVLINK_IN_PARAM_REQUEST_READ                 (1UL << 22)
#define EVMSK_MAVLINK_IN_COMMAND_LONG                       (1UL << 23)
#define EVMSK_MAVLINK_IN_MANUAL_CONTROL                     (1UL << 24)
#define EVMSK_MAVLINK_IN_SET_MODE                           (1UL << 25)
#define EVMSK_MAVLINK_IN_MISSION_SET_CURRENT                (1UL << 26)
#define EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST               (1UL << 27)
#define EVMSK_MAVLINK_IN_MISSION_COUNT                      (1UL << 28)
#define EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL                  (1UL << 29)

/* other events */
#define EVMSK_GPS_TIME_GOT                                  (1UL << 0)

/* function prototypes */
void MsgInit(void);
void MavInit(void);

#endif /* MESSAGE_H_ */

