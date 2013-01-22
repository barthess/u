#include "uav.h"

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
extern MemoryHeap ThdHeap;
extern GlobalFlags_t GlobalFlags;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* pointers to spawned threads */
static Thread *linkout_tp = NULL;
static Thread *linkin_tp  = NULL;

/* need only during parsing */
static mavlink_status_t                mavlink_status_struct;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 *
 */
static WORKING_AREA(LinkOutThreadWA, 1024);
static msg_t LinkOutThread(void *sdp){
  chRegSetThreadName("MAVLinkOut");

  while (!chThdShouldTerminate()) {
    chThdSleepMilliseconds(200);
    // process_in_here
  }

  /* try correctly stop thread */
  chThdSleepMilliseconds(200);
  chThdExit(0);
  return 0;
}


/**
 * Parse input data.
 */
static WORKING_AREA(LinkInThreadWA, 512);
static msg_t LinkInThread(void *sdp){
  chRegSetThreadName("MAVLinkIn");

  mavlink_message_t msg;
  msg_t c = 0;

  while (!chThdShouldTerminate()) {
    // Try to get a new message
    c = sdGetTimeout((SerialDriver *)sdp, MS2ST(200));
    if (c != Q_TIMEOUT){
      if (mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)c, &msg, &mavlink_status_struct)) {
        if (msg.sysid == GROUND_STATION_ID){ /* message from our ground station */
          sort_input_messages(&msg);
        }
      }
    }
  }

  chThdExit(0);
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * Kills previously spawned threads
 */
void KillMavlinkThreads(void){
  clearGlobalFlag(GlobalFlags.tlm_link_ready);

  chThdTerminate(linkout_tp);
  chThdTerminate(linkin_tp);

  chThdWait(linkout_tp);
  chThdWait(linkin_tp);
}

/**
 * Create telemetry link threads
 */
void SpawnMavlinkThreads(SerialDriver *sdp){

  linkout_tp = chThdCreateFromHeap(&ThdHeap,
                            sizeof(LinkOutThreadWA),
                            LINK_THREADS_PRIO,
                            LinkOutThread,
                            sdp);
  if (linkout_tp == NULL)
    chDbgPanic("Can not allocate memory");

  linkin_tp = chThdCreateFromHeap(&ThdHeap,
                            sizeof(LinkInThreadWA),
                            LINK_THREADS_PRIO,
                            LinkInThread,
                            sdp);
  if (linkin_tp == NULL)
    chDbgPanic("Can not allocate memory");

  setGlobalFlag(GlobalFlags.tlm_link_ready);
}

