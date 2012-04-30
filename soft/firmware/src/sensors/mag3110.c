#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "utils.h"
#include "mag3110.h"
#include "message.h"
#include "param.h"
#include "main.h"
#include "link.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define mag3110addr 0b0001110
#define OVERDOSE    ((uint16_t)25000) // ������, ����� �������� ���� �������� ������

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern BinarySemaphore mag3110_sem;
//extern GlobalParam_t global_data[];
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern RawData raw_data;
extern EventSource pwrmgmt_event;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// ������ ��� ������ ������������
static uint8_t rxbuf[MAG_RX_DEPTH];
static uint8_t txbuf[MAG_TX_DEPTH];

/* ������� � ��������� � ����������� */
static uint32_t xoffset_index, yoffset_index, zoffset_index;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/* ����� ��� ������� ������������� */
static WORKING_AREA(PollMagThreadWA, 512);
static msg_t PollMagThread(void *arg){
  chRegSetThreadName("PollMag");
  (void)arg;
  msg_t sem_status = RDY_OK;

  struct EventListener self_el;
  chEvtRegister(&pwrmgmt_event, &self_el, PWRMGMT_SIGHALT_EVID);

  while (TRUE) {
    /* ������ ��� ���� ������� ������ ����� ��������� �� ��������, ���������
     * ����������� �������� �� ����� ������, ��� ����������� EXTI. ��� ����,
     * ����� ���������� ��������� ��������, ���� ����������� ������ ������
     * �� ��� ������� ������� ��������. */
    sem_status = chBSemWaitTimeout(&mag3110_sem, MS2ST(200));

    /* ���������, �� ��� ���������� */
    txbuf[0] = MAG_OUT_DATA;
    if ((sem_status == RDY_OK) && (i2c_transmit(mag3110addr, txbuf, 1, rxbuf, 6) == RDY_OK)){
      raw_data.xmag = complement2signed(rxbuf[0], rxbuf[1]);
      raw_data.ymag = complement2signed(rxbuf[2], rxbuf[3]);
      raw_data.zmag = complement2signed(rxbuf[4], rxbuf[5]);

      mavlink_raw_imu_struct.xmag = raw_data.xmag;
      mavlink_raw_imu_struct.ymag = raw_data.xmag;
      mavlink_raw_imu_struct.zmag = raw_data.xmag;
    }
    else{
      /* ���������� �������� ������ */
      raw_data.xmag = -32768;
      raw_data.ymag = -32768;
      raw_data.zmag = -32768;
      mavlink_raw_imu_struct.xmag = raw_data.xmag;
      mavlink_raw_imu_struct.ymag = raw_data.xmag;
      mavlink_raw_imu_struct.zmag = raw_data.xmag;
    }

    /* ���� ������ ������������ - ���� ���������� �����. � ��������,
          ����� � ������� ��������� ��������� �� ������ ���������, �� ���
          ���-�� �� ���������. */
    if (abs(raw_data.xmag) > OVERDOSE ||
        abs(raw_data.ymag) > OVERDOSE ||
        abs(raw_data.zmag) > OVERDOSE){
      txbuf[0] = MAG_CTRL_REG2;
      txbuf[1] = MAG_RST;
      i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0);
    }

    if (chThdSelf()->p_epending & EVENT_MASK(PWRMGMT_SIGHALT_EVID))
      chThdExit(RDY_OK);
  }

  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void init_mag3110(void){
  int32_t i = -1;

  i = KeyValueSearch("MAG_xoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    xoffset_index = i;

  i = KeyValueSearch("MAG_yoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    yoffset_index = i;

  i = KeyValueSearch("MAG_zoffset");
  if (i == -1)
    chDbgPanic("key not found");
  else
    zoffset_index = i;

  // TODO: ������� ������ ���������, ��� ������ �������� ����� ������� ��� WHOAMI
  // TODO: ��������� � ��� ���������������

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    i = 0;
    for (i = 0; i < MAG_TX_DEPTH; i++){txbuf[i] = 0x55;}
    for (i = 0; i < MAG_RX_DEPTH; i++){rxbuf[i] = 0x55;}
  #endif

  /* Except for STANDBY mode selection, the device must be in STANDBY mode
   to change any of the fields within CTRL_REG1 (0x10). */
  txbuf[0] = MAG_CTRL_REG1; // register address
  txbuf[1] = 0b11001;       // ������� �� ������� ������, ����������� ����������������
  while(i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  /* ��������� ��������� ����� ������� */
  chThdSleepMilliseconds(2);
  txbuf[0] = MAG_CTRL_REG2;
  txbuf[1] = MAG_RST;
  while(i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdSleepMilliseconds(2);
  chThdCreateStatic(PollMagThreadWA,
          sizeof(PollMagThreadWA),
          I2C_THREADS_PRIO,
          PollMagThread,
          NULL);
  chThdSleepMilliseconds(1);
}


