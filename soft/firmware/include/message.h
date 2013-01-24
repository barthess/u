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
#define EVMSK_MAVLINK_OUT_RAW_IMU                           (1UL << 13)
#define EVMSK_MAVLINK_OUT_SCALED_IMU                        (1UL << 14)
#define EVMSK_MAVLINK_OUT_RAW_PRESSURE                      (1UL << 15)
#define EVMSK_MAVLINK_OUT_SCALED_PRESSURE                   (1UL << 16)
#define EVMSK_MAVLINK_OUT_VFR_HUD                           (1UL << 17)
#define EVMSK_MAVLINK_OUT_ATTITUDE                          (1UL << 18)
#define EVMSK_MAVLINK_OUT_MISSION_COUNT                     (1UL << 19)
#define EVMSK_MAVLINK_OUT_MISSION_ITEM                      (1UL << 20)
#define EVMSK_MAVLINK_OUT_MISSION_REQUEST                   (1UL << 21)

/* input messages events */
#define EVMSK_MAVLINK_IN_PARAM_SET                          (1UL << 0)
#define EVMSK_MAVLINK_IN_PARAM_REQUEST_LIST                 (1UL << 1)
#define EVMSK_MAVLINK_IN_PARAM_REQUEST_READ                 (1UL << 2)
#define EVMSK_MAVLINK_IN_COMMAND_LONG                       (1UL << 3)
#define EVMSK_MAVLINK_IN_MANUAL_CONTROL                     (1UL << 4)
#define EVMSK_MAVLINK_IN_SET_MODE                           (1UL << 5)
#define EVMSK_MAVLINK_IN_MISSION_SET_CURRENT                (1UL << 6)
#define EVMSK_MAVLINK_IN_MISSION_REQUEST_LIST               (1UL << 7)
#define EVMSK_MAVLINK_IN_MISSION_COUNT                      (1UL << 8)
#define EVMSK_MAVLINK_IN_MISSION_CLEAR_ALL                  (1UL << 9)
#define EVMSK_MAVLINK_IN_MISSION_ITEM                       (1UL << 10)
#define EVMSK_MAVLINK_IN_MISSION_REQUEST                    (1UL << 11)
#define EVMSK_MAVLINK_IN_MISSION_ACK                        (1UL << 12)

/* other events */
#define EVMSK_GPS_TIME_GOT                                  (1UL << 0)

/* function prototypes */
void MsgInit(void);
void MavInit(void);

#endif /* MESSAGE_H_ */

