#include <time.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"

#include "ff.h"

#include "storage.h"
#include "message.h"

#define SDC_POLLING_INTERVAL            10
#define SDC_POLLING_DELAY               10

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/*===========================================================================*/
/* Card insertion monitor.                                                   */
/*===========================================================================*/

/**
 * @brief   Card monitor timer.
 */
static VirtualTimer tmr;

/**
 * @brief   Debounce counter.
 */
static unsigned cnt;

/**
 * @brief   Card event sources.
 */
static EventSource inserted_event, removed_event;

/**
 * @brief   Inserion monitor function.
 *
 * @param[in] sdcp      pointer to the @p SDCDriver object
 *
 * @notapi
 */
bool_t sdc_lld_is_card_inserted(SDCDriver *sdcp) {

  (void)sdcp;
  return !palReadPad(GPIOE, GPIOE_SDIO_DETECT);
}

/**
 * @brief   Protection detection.
 * @note    Not supported.
 *
 * @param[in] sdcp      pointer to the @p SDCDriver object
 *
 * @notapi
 */
bool_t sdc_lld_is_write_protected(SDCDriver *sdcp) {

  (void)sdcp;
  return FALSE;
}

/**
 * @brief   Inserion monitor timer callback function.
 *
 * @param[in] p         pointer to the @p SDCDriver object
 *
 * @notapi
 */
static void tmrfunc(void *p) {
  SDCDriver *sdcp = p;

  if (cnt > 0) {
    if (sdcIsCardInserted(sdcp)) {
      if (--cnt == 0) {
        chEvtBroadcastI(&inserted_event);
      }
    }
    else
      cnt = SDC_POLLING_INTERVAL;
  }
  else {
    if (!sdcIsCardInserted(sdcp)) {
      cnt = SDC_POLLING_INTERVAL;
      chEvtBroadcastI(&removed_event);
    }
  }
  chVTSetI(&tmr, MS2ST(SDC_POLLING_DELAY), tmrfunc, sdcp);
}

/**
 * @brief   Polling monitor start.
 *
 * @param[in] sdcp      pointer to the @p SDCDriver object
 *
 * @notapi
 */
static void tmr_init(SDCDriver *sdcp) {

  chEvtInit(&inserted_event);
  chEvtInit(&removed_event);
  chSysLock();
  cnt = SDC_POLLING_INTERVAL;
  chVTSetI(&tmr, MS2ST(SDC_POLLING_DELAY), tmrfunc, sdcp);
  chSysUnlock();
}

/*===========================================================================*/
/* FatFs related.                                                            */
/*===========================================================================*/

/**
 * @brief FS object.
 */
FATFS SDC_FS;

/* FS mounted and ready.*/
static bool_t fs_ready = FALSE;

/* Generic large buffer.*/
uint8_t fbuff[8192];

static FRESULT scan_files(BaseChannel *chp, char *path) {
  FRESULT res;
  FILINFO fno;
  DIR dir;
  int i;
  char *fn;

  res = f_opendir(&dir, path);
  if (res == FR_OK) {
    i = strlen(path);
    for (;;) {
      res = f_readdir(&dir, &fno);
      if (res != FR_OK || fno.fname[0] == 0)
        break;
      if (fno.fname[0] == '.')
        continue;
      fn = fno.fname;
      if (fno.fattrib & AM_DIR) {
        path[i++] = '/';
        strcpy(&path[i], fn);
        res = scan_files(chp, path);
        if (res != FR_OK)
          break;
        path[i] = 0;
      }
      else {
        chprintf(chp, "%s/%s\r\n", path, fn);
      }
    }
  }
  return res;
}

/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/

#define SHELL_WA_SIZE   THD_WA_SIZE(2048)
#define TEST_WA_SIZE    THD_WA_SIZE(256)

static void cmd_tree(BaseChannel *chp, int argc, char *argv[]) {
  FRESULT err;
  uint32_t clusters;
  FATFS *fsp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: tree\r\n");
    return;
  }
  if (!fs_ready) {
    chprintf(chp, "File System not mounted\r\n");
    return;
  }
  err = f_getfree("/", &clusters, &fsp);
  if (err != FR_OK) {
    chprintf(chp, "FS: f_getfree() failed\r\n");
    return;
  }
  chprintf(chp,
           "FS: %lu free clusters, %lu sectors per cluster, %lu bytes free\r\n",
           clusters, (uint32_t)SDC_FS.csize,
           clusters * (uint32_t)SDC_FS.csize * (uint32_t)SDC_BLOCK_SIZE);
  fbuff[0] = 0;
  scan_files(chp, (char *)fbuff);
}

static const ShellCommand commands[] = {
  {"tree", cmd_tree},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseChannel *)&SD1,
  commands
};

/*===========================================================================*/
/* Main and generic code.                                                    */
/*===========================================================================*/

/*
 * SD card insertion event.
 */
static void InsertHandler(eventid_t id) {
  FRESULT err;

  (void)id;
  /*
   * On insertion SDC initialization and FS mount.
   */
  if (sdcConnect(&SDCD1))
    return;

  err = f_mount(0, &SDC_FS);
  if (err != FR_OK) {
    sdcDisconnect(&SDCD1);
    return;
  }
  fs_ready = TRUE;
}

/*
 * SD card removal event.
 */
static void RemoveHandler(eventid_t id) {

  (void)id;
  if (sdcGetDriverState(&SDCD1) == SDC_ACTIVE)
    sdcDisconnect(&SDCD1);
  fs_ready = FALSE;
}


void StorageInit(void){
  static const evhandler_t evhndl[] = {
    InsertHandler,
    RemoveHandler
  };

  Thread *shelltp = NULL;
  struct EventListener el0, el1;
  /*
   * Shell manager initialization.
   */
  shellInit();

  /*
   * Activates the card insertion monitor.
   */
  tmr_init(&SDCD1);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and listen for events.
   */
  chEvtRegister(&inserted_event, &el0, 0);
  chEvtRegister(&removed_event, &el1, 1);
}




