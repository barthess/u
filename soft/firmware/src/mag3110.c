#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "dsp.h"
#include "mag3110.h"
#include "message.h"
#include "main.h"

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
extern RawData raw_data;
extern BinarySemaphore mag3110_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// ������ ��� ������ ������������
static uint8_t rxbuf[MAG_RX_DEPTH];
static uint8_t txbuf[MAG_TX_DEPTH];

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/* ����� ��� ������� ������������� */
static WORKING_AREA(PollMagThreadWA, 256);
static msg_t PollMagThread(void *arg){

  chRegSetThreadName("PollMag");
  (void)arg;
  msg_t sem_status = RDY_OK;

  while (TRUE) {
    /* ������ ��� ���� ������� ������ ����� ��������� �� ��������, ���������
     * ����������� �������� �� ����� ������, ��� ����������� EXTI. ��� ����,
     * ����� ���������� ��������� ��������, ���� ����������� ������ ������
     * �� ��� ������� ������� ��������. */
    sem_status = chBSemWaitTimeout(&mag3110_sem, MS2ST(200));

    /* ���������, �� ��� ���������� */
    txbuf[0] = MAG_OUT_DATA;
    if (i2c_transmit(mag3110addr, txbuf, 1, rxbuf, 6) == RDY_OK &&
                                           sem_status == RDY_OK){
      raw_data.magnetic_x = complement2signed(rxbuf[0], rxbuf[1]);
      raw_data.magnetic_y = complement2signed(rxbuf[2], rxbuf[3]);
      raw_data.magnetic_z = complement2signed(rxbuf[4], rxbuf[5]);
    }
    else{
      /* ���������� ���� ��� �������� ������ */
      raw_data.magnetic_x = 0;
      raw_data.magnetic_y = 0;
      raw_data.magnetic_z = 0;
    }

    /* ���� ������ ������������ - ���� ���������� �����. � ��������,
    ����� � ������� ��������� ��������� �� ������ ���������, �� ���
    ���-�� �� ���������. */
    if (abs(raw_data.magnetic_x) > OVERDOSE ||
        abs(raw_data.magnetic_y) > OVERDOSE ||
        abs(raw_data.magnetic_z) > OVERDOSE){
      txbuf[0] = MAG_CTRL_REG2;
      txbuf[1] = MAG_RST;
      i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0);
    }
  }

  return 0;
}


void init_mag3110(void){
  // TODO: ������� ������ ���������, ��� ������ �������� ����� ������� ��� WHOAMI
  // TODO: ��������� � ��� ���������������

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint8_t i = 0;
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
  txbuf[0] = MAG_CTRL_REG2;
  txbuf[1] = MAG_RST;
  while(i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdCreateStatic(PollMagThreadWA,
          sizeof(PollMagThreadWA),
          NORMALPRIO,
          PollMagThread,
          NULL);
}


