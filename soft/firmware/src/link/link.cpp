#include "main.h"
#include "global_flags.h"

#include "link_packer.hpp"
#include "link_unpacker.hpp"

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

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* pointers to spawned threads */
static Thread *linkout_tp = NULL;
static Thread *linkin_tp  = NULL;

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
static WORKING_AREA(LinkOutThreadWA, 1536);
static msg_t LinkOutThread(void *arg){
  chRegSetThreadName("MAVLinkOut");
  SerialDriver *sdp = (SerialDriver *)arg;
  PackCycle(sdp);
  chThdExit(0);
  return 0;
}

/**
 * Parse input data.
 */
static WORKING_AREA(LinkInThreadWA, 1024);
static msg_t LinkInThread(void *arg){
  chRegSetThreadName("MAVLinkIn");
  SerialDriver *sdp = (SerialDriver *)arg;
  UnpackCycle(sdp);
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
void SpawnMavlinkThreads(void *sdp){

  linkout_tp = chThdCreateStatic(LinkOutThreadWA,
                            sizeof(LinkOutThreadWA),
                            LINK_THREADS_PRIO,
                            LinkOutThread,
                            sdp);

  if (linkout_tp == NULL)
    chDbgPanic("Can not allocate memory");

  linkin_tp = chThdCreateStatic(LinkInThreadWA,
                            sizeof(LinkInThreadWA),
                            LINK_THREADS_PRIO,
                            LinkInThread,
                            sdp);
  if (linkin_tp == NULL)
    chDbgPanic("Can not allocate memory");

  setGlobalFlag(GlobalFlags.tlm_link_ready);
}

