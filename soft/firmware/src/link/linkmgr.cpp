#include "uav.h"
#include "global_flags.h"
#include "usbcfg.hpp"
#include "cli.hpp"
#include "link.hpp"
#include "param_registry.hpp"

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
extern ParamRegistry param_registry;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static SerialUSBDriver SDU1;

static SerialConfig xbee_ser_cfg = {
    BAUDRATE_XBEE,
    0,
    0,
    USART_CR3_CTSE | USART_CR3_RTSE,
};

static uint32_t const *sh_overxbee;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * Track changes of sh_overxbee flag and fork appropriate threads
 */
static WORKING_AREA(LinkMgrThreadWA, 128);
static msg_t LinkMgrThread(void *arg){
  (void)arg;
  chRegSetThreadName("LinkManager");

  uint32_t sh = *sh_overxbee; // cached previouse value

  /*
  * Activates the USB driver and then the USB bus pull-up on D+.
  * Note, a delay is inserted in order to not have to disconnect the cable
  * after a reset.
  */
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1000);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  /* wait slowpoked modems */
  chThdSleepMilliseconds(3000);

  /* define what we need to run based on flag */
  if (sh == 1){
    SpawnShellThreads(&XBEESD);
    SpawnMavlinkThreads(&SDU1);
  }
  else{
    SpawnShellThreads(&SDU1);
    SpawnMavlinkThreads(&XBEESD);
  }

  /* say to all that modem is ready */
  setGlobalFlag(GlobalFlags.modem_ready);

  /* now track changes of flag and fork appropriate threads */
  while (TRUE) {
    chThdSleepMilliseconds(200);
    if(sh != *sh_overxbee){ // state changed
      sh = *sh_overxbee;
      KillShellThreads();
      KillMavlinkThreads();
      chThdSleepMilliseconds(1);

//      sdStop(&XBEESD);
//      sdStart(&XBEESD, &xbee_ser_cfg);
//
//      sduStop(&SDU1);
//      sduStart(&SDU1, &serusbcfg);

      // purge queues to be safer
//      chSysLock();
//      chIQResetI(&(SDU1.iqueue));
//      chIQResetI(&(SDU1.oqueue));
//      chIQResetI(&(XBEESD.iqueue));
//      chIQResetI(&(XBEESD.oqueue));
//      chSysUnlock();

      // now spawn threads with proper serial drivers
      if (sh == 1){
        SpawnShellThreads(&XBEESD);
        SpawnMavlinkThreads(&SDU1);
      }
      else{
        SpawnShellThreads(&SDU1);
        SpawnMavlinkThreads(&XBEESD);
      }
    }
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void LinkMgrInit(void){

  sh_overxbee = (const uint32_t*)param_registry.valueSearch("SH_overxbee");

  sdStart(&XBEESD, &xbee_ser_cfg);

  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  chThdCreateStatic(LinkMgrThreadWA,
          sizeof(LinkMgrThreadWA),
          LINK_THREADS_PRIO,
          LinkMgrThread,
          NULL);
}
