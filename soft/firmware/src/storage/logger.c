#include <string.h>

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "logger.h"
/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

#define BUFF_SIZE 4096

/* ������� ��������� ���� �������� � ������ */
#define FREE (BUFF_SIZE - offset)

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

/* ��� ������, ������� ����� ������������� �� ���� ���������� */
static uint8_t b0[BUFF_SIZE];
static uint8_t b1[BUFF_SIZE];

/* ��������� �� ������� ������� ����� */
static uint8_t* currbuf = b0;

/* �������� � ������� ������� ������ */
static uint32_t offset = 0;

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
 * @note Field 'invoice' in mail MUST contains number of bytes to be written.
 */
FRESULT WriteLog(FIL *Log, Mail *mailp, bool_t *fresh_data){
  uint32_t bytes_written;
  uint8_t *fs_buf;
  FRESULT err = FR_OK;

  fs_buf = bufferize(mailp->payload, mailp->invoice);
  mailp->payload = NULL;

  if (fs_buf != NULL){
    err = f_write(Log, fs_buf, BUFF_SIZE, (void *)&bytes_written);
    if (err == FR_OK)
      *fresh_data = TRUE;
  }
  return err;
}





