#include <string.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "logger.h"
#include "link_sortout.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

#define BUFF_SIZE 8192

/* ������� ��������� ���� �������� � ������ */
#define FREE (BUFF_SIZE - offset)

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern mavlink_system_t              mavlink_system_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/* ��� ������, ������� ����� ������������� �� ���� ���������� */
static uint8_t b0[BUFF_SIZE];
static uint8_t b1[BUFF_SIZE];

/* ��������� �� ������� ������� ����� */
static uint8_t* currbuf = b0;

/* �������� � ������� ������� ������ */
static uint32_t offset = 0;

/* some buffers for mavlink handling */
static mavlink_message_t mavlink_msgbuf_log;
static uint8_t logbuf[MAVLINK_MAX_PACKET_LEN];

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * ����������� ��������� �� ��������� �����
 */
void swap_buf(void){
  if (currbuf == b0)
    currbuf = b1;
  else
    currbuf = b0;
}


/**
 * ������������� ������ � �����
 */
uint8_t* bufferize(uint8_t *payload, uint32_t count){

  uint8_t *ret; /* ��������� �� ����������� ������� ����� */

  if (FREE > count){
    memcpy(currbuf + offset, payload, count);
    offset += count;
    return NULL;
  }
  else{
    /* ���������� � ������� ����� ������� ���������� */
    memcpy(currbuf + offset, payload, FREE);
    /* ���� ��������� �� ������, ��� ��������� ������ */
    ret = currbuf;
    /* ������������� �� ��������� ����� */
    swap_buf();
    /* ������� ������ ���������� � ��������� */
    memcpy(currbuf, payload + FREE, count - FREE);
    offset = count - FREE;
    return ret;
  }
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * Get id of data
 * Pack it
 * Store to FS buffer
 * Raise bool flag if fresh data available
 */
FRESULT WriteLog(FIL *Log, msg_t id, bool_t *fresh_data){
  uint32_t bytes_written;
  uint8_t *fs_buf;
  FRESULT err = FR_OK;
  uint16_t len = 0;

  mavencoder(id, mavlink_system_struct.sysid, &mavlink_msgbuf_log);
  len = mavlink_msg_to_send_buffer(logbuf, &mavlink_msgbuf_log);

  fs_buf = bufferize(logbuf, len);

  if (fs_buf != NULL){
    err = f_write(Log, fs_buf, BUFF_SIZE, (void *)&bytes_written);
    if (err == FR_OK)
      *fresh_data = TRUE;
  }
  return err;
}





