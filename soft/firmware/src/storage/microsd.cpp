#include <string.h>

#include "main.h"

#include "chprintf.h"
#include "chrtclib.h"
#include "ff.h"
#include "global_flags.h"
#include "message.hpp"
#include "param_registry.hpp"
#include "logger.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SDC_POLLING_INTERVAL            100
#define SDC_POLLING_DELAY               5
#define SYNC_PERIOD                     5000
/* размер буфера под имя файла */
#define MAX_FILENAME_SIZE               32

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern chibios_rt::Mailbox logwriter_mb;
extern ParamRegistry param_registry;

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

/* флаг необходимости синхронизации по таймауту */
static bool_t sync_tmo = FALSE;

/* флаг обозначающий наличие свежих данных, чтобы зря не дергать sync */
static bool_t fresh_data = FALSE;

/* по этому таймеру будет синхронизироваться файл лога */
static VirtualTimer sync_vt;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

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

  if ((&SDCD1)->state == BLK_ACTIVE){
    sdcDisconnect(&SDCD1);
    sdcStop(&SDCD1);
  }
  fs_ready = FALSE;
}

/**
 * Create human readable name for file.
 */
static size_t name_from_time(char *buf){

  time_t t = 0;

  int32_t const *timezone = (const int32_t*)param_registry.valueSearch("TIME_zone");

  t = rtcGetTimeUnixSec(&RTCD1);
  if (timezone != NULL)
    t += *timezone * 60 * 60;

#if MAVLINK_LOG_FORMAT
  return strftime(buf, MAX_FILENAME_SIZE, "%F_%H.%M.%S.mavlink", localtime(&t));
#else
  return strftime(buf, MAX_FILENAME_SIZE, "%F_%H.%M.%S.raw", localtime(&t));
#endif
}

/**
 *
 */
static void sync_cb(void *par){
  (void)par;
  chSysLockFromIsr();
  chVTSetI(&sync_vt, MS2ST(SYNC_PERIOD), &sync_cb, NULL);
  sync_tmo = TRUE;
  chSysUnlockFromIsr();
}

/**
 * По нескольким критериям определяет, надо ли сбрасывать буфер и при
 * необходимости сбрасывает.
 */
static FRESULT fs_sync(FIL *Log){
  FRESULT err = FR_OK;

  if (sync_tmo && fresh_data){
    err = f_sync(Log);
    sync_tmo = FALSE;
    fresh_data = FALSE;
  }
  return err;
}

/**
 * Проверяет вёрнутый статус.
 */
#define err_check()   if(err != FR_OK){return RDY_RESET;}


/**
 * Если произошла ошибка - просто тушится
 * поток логгера, потому что исправить всё равно ничего нельзя.
 */
static WORKING_AREA(SdThreadWA, 2048);
static msg_t SdThread(void *arg){
  chRegSetThreadName("MicroSD");
  (void)arg;

  FRESULT err;
  uint32_t clusters;
  FATFS *fsp;
  FIL Log;

  msg_t id;

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
  err_check();
  if ((clusters * (uint32_t)SDC_FS.csize * (uint32_t)MMCSD_BLOCK_SIZE) < (16*1024*1024))
    return RDY_RESET;

  /* open file for writing log */
  char namebuf[MAX_FILENAME_SIZE];
  name_from_time(namebuf);
  err = f_open(&Log, namebuf, FA_WRITE | FA_CREATE_ALWAYS);
  err_check();

  /* main write cycle
   * This writer waits msg_t with mavlink message ID. Based on that ID it
   * will pack extern mavlink struct with proper packing function. */
  setGlobalFlag(GlobalFlags.logger_ready);
  while (TRUE){
    /* wait ID */
    if (logwriter_mb.fetch(&id, TIME_INFINITE) == RDY_OK){
      if (!sdcIsCardInserted(&SDCD1)){
        clearGlobalFlag(GlobalFlags.logger_ready);
        remove_handler();
        goto NOT_READY;
      }
      err = WriteLog(&Log, id, &fresh_data);
      err_check();
    }

    err = fs_sync(&Log);
    err_check();
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
void cmd_touch(BaseSequentialStream *chp, int argc, char *argv[]) {
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
  err = f_write(&FileObject, "This is test file", 17, (UINT *)&bytes_written);
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
  chThdCreateStatic(SdThreadWA,
          sizeof(SdThreadWA),
          NORMALPRIO - 5,
          SdThread,
          NULL);

  chSysLock();
  chVTSetI(&sync_vt, MS2ST(SYNC_PERIOD), &sync_cb, NULL);
  chSysUnlock();
}
