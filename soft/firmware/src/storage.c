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

/* SDIO configuration. */
static const SDCConfig sdccfg = {
  0
};

/* FS object.*/
static FATFS SDC_FS;

/* FS mounted and ready.*/
static bool_t fs_ready = FALSE;

/* Generic large buffer.*/
static uint8_t fbuff[1024];

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

/*
 * SD card insertion event.
 */
static void InsertHandler(void) {
  FRESULT err;

  sdcStart(&SDCD1, &sdccfg);
  /*
   * On insertion SDC initialization and FS mount.
   */
  if (sdcConnect(&SDCD1))
    return;

  err = f_mount(0, &SDC_FS);
  if (err != FR_OK) {
    sdcDisconnect(&SDCD1);
    sdcStop(&SDCD1);
    return;
  }
  fs_ready = TRUE;
}

/*
 * SD card removal event.
 */
static void RemoveHandler(void) {

  if (fs_ready == TRUE){
    f_mount(0, NULL);
    fs_ready = FALSE;
  }

  if (sdcGetDriverState(&SDCD1) == SDC_ACTIVE){
    sdcDisconnect(&SDCD1);
    sdcStop(&SDCD1);
  }
  fs_ready = FALSE;
}

/*===========================================================================*/
/* FatFs related.                                                            */
/*===========================================================================*/

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

void cmd_tree(BaseChannel *chp, int argc, char *argv[]) {
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


/**
 * Monitors presence of SD card in slot.
 */
static WORKING_AREA(CardMonitorThreadWA, 8192);
static msg_t CardMonitorThread(void *arg){
  (void)arg;
  chRegSetThreadName("CardMonitor");
  unsigned cnt = SDC_POLLING_DELAY;/* Debounce counter. */

  while TRUE{
    chThdSleepMilliseconds(SDC_POLLING_INTERVAL);

    if (cnt > 0) {
      if (sdcIsCardInserted(&SDCD1)) {
        if (--cnt == 0) {
          InsertHandler();
        }
      }
      else
        cnt = SDC_POLLING_INTERVAL;
    }
    else {
      if (!sdcIsCardInserted(&SDCD1)) {
        cnt = SDC_POLLING_INTERVAL;
        RemoveHandler();
      }
    }
  }
  return 0;
}




void StorageInit(void){
  chThdCreateStatic(CardMonitorThreadWA,
          sizeof(CardMonitorThreadWA),
          NORMALPRIO,
          CardMonitorThread,
          NULL);

}




