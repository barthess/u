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
#define SDC_POLLING_INTERVAL            20
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

/* Generic large buffer.*/
static uint8_t fbuff[2048];

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
static WORKING_AREA(CardMonitorThreadWA, 1024);
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

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

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

/**
 * Get file tree.
 */
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
 * Create file.
 */
void cmd_touch(BaseChannel *chp, int argc, char *argv[]) {
  FRESULT err;
  FIL FileObject;
  uint32_t bytes_written;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: touch\r\n");
    return;
  }
  if (!fs_ready) {
    chprintf(chp, "File System not mounted\r\n");
    return;
  }
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
 * Copy file.
 */
void cmd_cp(BaseChannel *chp, int argc, char *argv[]) {
  FRESULT err;
  FIL fsrc, fdst;
  UINT br, bw;         /* File read/write count */

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: cp\r\n");
    return;
  }
  if (!fs_ready) {
    chprintf(chp, "File System not mounted\r\n");
    return;
  }

  /* Open source file on the drive 1 */
  err = f_open(&fsrc, "0:ink.7z", FA_OPEN_EXISTING | FA_READ);
  if (err != FR_OK) {
    chprintf(chp, "FS: f_open() of ink.7z failed\r\n");
    chThdSleepMilliseconds(50);
    return;
  }

  /* Create destination file on the drive 0 */
  err = f_open(&fdst, "0:dstfile.dat", FA_CREATE_ALWAYS | FA_WRITE);
  if (err != FR_OK) {
    chprintf(chp, "FS: f_open() of dstfile.dat failed\r\n");
    chThdSleepMilliseconds(50);
    return;
  }

  /* Copy source to destination */
  for (;;) {
    err = f_read(&fsrc, fbuff, sizeof(fbuff), &br);    /* Read a chunk of src file */
    if (err || br == 0) break; /* error or eof */
    err = f_write(&fdst, fbuff, br, &bw);               /* Write it to the dst file */
    if (err || bw < br) break; /* error or disk full */
  }

  /* Close open files */
  f_close(&fsrc);
  f_close(&fdst);

  chprintf(chp, "Done.\r\n");
}

/**
 * Init.
 */
void StorageInit(void){
  chThdCreateStatic(CardMonitorThreadWA,
          sizeof(CardMonitorThreadWA),
          NORMALPRIO,
          CardMonitorThread,
          NULL);
}


