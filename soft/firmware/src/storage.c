#include <time.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "ff.h"

#include "storage.h"
#include "message.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SDC_POLLING_INTERVAL            100
#define SDC_POLLING_DELAY               5

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/* SDIO configuration. */
static const SDCConfig sdccfg = {
  0
};

/* FS object.*/
static FATFS SDC_FS;

/* FS mounted and ready.*/
static bool_t fs_ready = FALSE;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

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
 * @note    Not supported, allways not protected.
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
static void insert_handler(void) {
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
static void remove_handler(void) {

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

/**
 * Monitors presence of SD card in slot.
 */
static WORKING_AREA(CardMonitorThreadWA, 256);
static msg_t CardMonitorThread(void *arg){
  (void)arg;
  chRegSetThreadName("CardMonitor");
  unsigned cnt = SDC_POLLING_DELAY;/* Debounce counter. */

  while TRUE{
    chThdSleepMilliseconds(SDC_POLLING_INTERVAL);

    if (cnt > 0) {
      if (sdcIsCardInserted(&SDCD1)) {
        if (--cnt == 0) {
          insert_handler();
        }
      }
      else
        cnt = SDC_POLLING_INTERVAL;
    }
    else {
      if (!sdcIsCardInserted(&SDCD1)) {
        cnt = SDC_POLLING_INTERVAL;
        remove_handler();
      }
    }
  }
  return 0;
}


/**
 * Monitors presence of SD card in slot.
 */
static WORKING_AREA(LogWriterThreadWA, 2048);
static msg_t LogWriterThread(void *arg){
  chRegSetThreadName("LogWriter");
  (void)arg;

  FRESULT err;
  uint32_t clusters;
  FATFS *fsp;
  FIL Log;
  uint32_t bytes_written;

  /* wait until card not ready */
NOT_READY:
  while (!sdcIsCardInserted(&SDCD1))
    chThdSleepMilliseconds(SDC_POLLING_INTERVAL);
  chThdSleepMilliseconds(SDC_POLLING_INTERVAL);
  if (!sdcIsCardInserted(&SDCD1))
    goto NOT_READY;
  else
    insert_handler();

  /* fs mounted? */
  if (!fs_ready)
    return RDY_RESET;

  /* are we have at least 16MB of free space? */
  err = f_getfree("/", &clusters, &fsp);
  if (err != FR_OK)
    return RDY_RESET;
  if ((clusters * (uint32_t)SDC_FS.csize * (uint32_t)SDC_BLOCK_SIZE) < (16*1024*1024))
    return RDY_RESET;

  //TODO: open file named YYYY-MM-DD_hh.mm.ss
  err = f_open(&Log, "0:test.log", FA_WRITE | FA_OPEN_ALWAYS);
  if (err != FR_OK)
    return RDY_RESET;

  /* main write cycle */
  while TRUE{
    //TODO: wait pointer to buffer
    if (!sdcIsCardInserted(&SDCD1)){
      remove_handler();
      goto NOT_READY;
    }
    else
      err = f_write(&Log, "This is test file", 17, (void *)&bytes_written);
      if (err != FR_OK)
        return RDY_RESET;
  }
  return 0;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */



/**
 * Create file.
 */
void cmd_touch(BaseChannel *chp, int argc, char *argv[]) {
  (void)argc;
  FRESULT err;
  FIL FileObject;
  uint32_t bytes_written;

  (void)argv;

  err = f_open(&FileObject, "0:test.txt", FA_WRITE | FA_OPEN_ALWAYS);
  if (err != FR_OK) {
    chprintf(chp, "FS: f_open() failed\r\n");
    return;
  }
  err = f_write(&FileObject, "This is test file", 17, (void *)&bytes_written);
  if (err != FR_OK) {
    chprintf(chp, "FS: f_write() failed\r\n");
    return;
  }
  else
    chprintf(chp, "some bytes written\r\n");

  err = f_sync(&FileObject);
  if (err != FR_OK) {
    chprintf(chp, "FS: f_sync() failed\r\n");
    return;
  }
  else
    chprintf(chp, "sync success\r\n");

  err = f_close(&FileObject);
  if (err != FR_OK) {
    chprintf(chp, "FS: f_close() failed\r\n");
    return;
  }
  else
    chprintf(chp, "file closed\r\n");
}

/**
 * Init.
 */
void StorageInit(void){
  chThdCreateStatic(CardMonitorThreadWA,
          sizeof(CardMonitorThreadWA),
          NORMALPRIO - 5,
          CardMonitorThread,
          NULL);

  chThdCreateStatic(LogWriterThreadWA,
          sizeof(LogWriterThreadWA),
          NORMALPRIO - 5,
          LogWriterThread,
          NULL);
}
