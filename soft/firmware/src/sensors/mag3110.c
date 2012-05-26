#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "utils.h"
#include "mag3110.h"
#include "sensors.h"
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
#define mag3110sens 0.1F /* uT/LSB */
#define OVERDOSE    ((uint16_t)25000) // ������, ����� �������� ���� �������� ������
#define ERR_VAL     -32700  /* ��� �������� �������� �������� ������ ������ */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;
extern mavlink_raw_imu_t mavlink_raw_imu_struct;
extern mavlink_scaled_imu_t mavlink_scaled_imu_struct;
extern RawData raw_data;
extern EventSource pwrmgmt_event;
extern CompensatedData comp_data;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// ������ ��� ������ ������������
static uint8_t rxbuf[MAG_RX_DEPTH];
static uint8_t txbuf[MAG_TX_DEPTH];

/* ��������� � ��������� � ����������� */
static float *xpol, *ypol, *zpol, *xoffset, *yoffset, *zoffset, *xsens, *ysens, *zsens;

/* ������ ������������ � ���������� ��������� �� ���� ��� ���������� �������� */
static int16_t extremums[6]; //minx, maxx, miny, maxy, mixz, maxz

/**
 * @brief   Magnenometer thread state machine possible states.
 */
typedef enum {
  MAG_UNINIT = 0,         /**< Not initialized.*/
  MAG_CAL = 1,            /**< Calibrating ongoing.*/
  MAG_ACTIVE = 2,         /**< Normal data acquision.*/
} magnetometerstate_t;

static magnetometerstate_t state;


/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */
static void raise_error_flags(void);
static void check_and_clean_overdose(void);
static void acquire_data(uint8_t *rxbuf);
static void collect_staticstics(RawData *raw_data, int16_t extremums[6]);
static void calc_coefficients(int16_t extremums[6]);
static void clear_statistics(RawData *raw_data, int16_t extremums[6]);

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/**
 * ����� ��� ������ ������������
 */
static WORKING_AREA(PollMagThreadWA, 512);
static msg_t PollMagThread(void *semp){
  chRegSetThreadName("PollMag");

  msg_t sem_status = RDY_OK;

  struct EventListener self_el;
  chEvtRegister(&pwrmgmt_event, &self_el, PWRMGMT_SIGHALT_EVID);

  while (TRUE) {
    /* ������ ��� ���� ������� ������ ����� ��������� �� ��������, ���������
     * ����������� �������� �� ����� ������, ��� ����������� EXTI. ��� ����,
     * ����� ���������� ��������� ��������, ���� ����������� ������ ������
     * �� ��� ������� ������� ��������. */
    sem_status = chBSemWaitTimeout((BinarySemaphore*)semp, MS2ST(200));

    /* ���������, �� ��� ���������� */
    txbuf[0] = MAG_OUT_DATA;
    if ((i2c_transmit(mag3110addr, txbuf, 1, rxbuf, 6) == RDY_OK) && (sem_status == RDY_OK))
      acquire_data(rxbuf);
    else
      raise_error_flags();

    /* �������? */
    check_and_clean_overdose();

    /* ��� �������� ������ HALT? */
    if (chThdSelf()->p_epending & EVENT_MASK(PWRMGMT_SIGHALT_EVID))
      chThdExit(RDY_OK);
  }
  return 0;
}

/**
 * ������������ ���������� ������ �� ����������, ��� ������������� ������������.
 */
void acquire_data(uint8_t *rxbuf){

  /**/
  raw_data.xmag = complement2signed(rxbuf[0], rxbuf[1]);
  raw_data.ymag = complement2signed(rxbuf[2], rxbuf[3]);
  raw_data.zmag = complement2signed(rxbuf[4], rxbuf[5]);

  /* fill debug structs */
  mavlink_raw_imu_struct.xmag = raw_data.xmag;
  mavlink_raw_imu_struct.ymag = raw_data.ymag;
  mavlink_raw_imu_struct.zmag = raw_data.zmag;
  mavlink_scaled_imu_struct.xmag = (raw_data.xmag - *xoffset) * *xpol;
  mavlink_scaled_imu_struct.ymag = (raw_data.ymag - *yoffset) * *ypol;
  mavlink_scaled_imu_struct.zmag = (raw_data.zmag - *zoffset) * *zpol;

  /* Sensitivity is 0.1uT/LSB */
  comp_data.xmag = (float)(mavlink_scaled_imu_struct.xmag) * *xsens;
  comp_data.ymag = (float)(mavlink_scaled_imu_struct.ymag) * *ysens;
  comp_data.zmag = (float)(mavlink_scaled_imu_struct.zmag) * *zsens;

  /* collect statistics for calibration purpose */
  if (GlobalFlags & MAG_CAL_FLAG){
    /* ��������� ���� ���������� */
    if (state == MAG_ACTIVE){
      clear_statistics(&raw_data, extremums);
      state = MAG_CAL;
    }
    collect_staticstics(&raw_data, extremums);
  }
  else{
    if (state == MAG_CAL){
      /* ������������� ���� ���������� */
      state = MAG_ACTIVE;
      calc_coefficients(extremums);
    }
  }
}

/**
 * ��������� ������������� ������������ ������ �� ����������� ������
 */
void calc_coefficients(int16_t extremums[6]){

  int16_t xmagnitude = extremums[1] - extremums[0];
  int16_t ymagnitude = extremums[3] - extremums[2];
  int16_t zmagnitude = extremums[5] - extremums[4];

  *xoffset = extremums[1] - xmagnitude / 2;
  *yoffset = extremums[3] - ymagnitude / 2;
  *zoffset = extremums[5] - zmagnitude / 2;

  float avg = (float)(xmagnitude + ymagnitude + zmagnitude) / 3.0;

  /* slightly correct stock sens (0.1uT/LSB) */
  *xsens = mag3110sens * (avg / (float)xmagnitude);
  *ysens = mag3110sens * (avg / (float)ymagnitude);
  *zsens = mag3110sens * (avg / (float)zmagnitude);
}


/**
 * Resets collected extremums
 */
void clear_statistics(RawData *raw_data, int16_t extremums[6]){
  extremums[0] = raw_data->xmag;
  extremums[1] = raw_data->xmag;

  extremums[2] = raw_data->ymag;
  extremums[3] = raw_data->ymag;

  extremums[4] = raw_data->zmag;
  extremums[5] = raw_data->zmag;
}

/**
 * Helper function
 */
void stats_check(int16_t val, int16_t storage[2]){
  if (val == ERR_VAL)
    return;
  if (val < storage[0])
    storage[0] = val;
  else if (val > storage[1])
    storage[1] = val;
}

/**
 * @brief  �������� ���������� �� ������������ ���������� � �����������
 * ��� �������������� ����������.
 *
 * @param[in]  *raw_data    pointer to object with raw measurements
 * @param[in]  *extremums   array with maximus and minimums of raw magnetic
 *                          measurements
 */
void collect_staticstics(RawData *raw_data, int16_t extremums[6]){
  stats_check(raw_data->xmag, &(extremums[0]));
  stats_check(raw_data->ymag, &(extremums[2]));
  stats_check(raw_data->zmag, &(extremums[4]));
}

/**
 * ���� ������ ������������ - ���� ���������� �����. � ��������, �����
 * � ������� ��������� ��������� �� ������ ���������, ��
 * ��� ���-�� �� ���������.
 */
void check_and_clean_overdose(void){
  if (abs(raw_data.xmag) > OVERDOSE ||
      abs(raw_data.ymag) > OVERDOSE ||
      abs(raw_data.zmag) > OVERDOSE){
    txbuf[0] = MAG_CTRL_REG2;
    txbuf[1] = MAG_RST;
    i2c_transmit(mag3110addr, txbuf, 2, rxbuf, 0);
  }
}

/**
 * ������� ���������� ��������, ������� ����������, ��� �������� ������
 */
void raise_error_flags(void){
  raw_data.xmag = ERR_VAL;
  raw_data.ymag = ERR_VAL;
  raw_data.zmag = ERR_VAL;
  mavlink_raw_imu_struct.xmag = raw_data.xmag;
  mavlink_raw_imu_struct.ymag = raw_data.ymag;
  mavlink_raw_imu_struct.zmag = raw_data.zmag;
  mavlink_scaled_imu_struct.xmag = raw_data.xmag;
  mavlink_scaled_imu_struct.ymag = raw_data.ymag;
  mavlink_scaled_imu_struct.zmag = raw_data.zmag;
}


/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void init_mag3110(BinarySemaphore *mag3110_semp){

  state = MAG_UNINIT;

  /* ����� �������� � ������� �������� */
  xoffset = ValueSearch("MAG_xoffset");
  yoffset = ValueSearch("MAG_yoffset");
  zoffset = ValueSearch("MAG_zoffset");
  xpol    = ValueSearch("MAG_xpol");
  ypol    = ValueSearch("MAG_ypol");
  zpol    = ValueSearch("MAG_zpol");
  xsens   = ValueSearch("MAG_xsens");
  ysens   = ValueSearch("MAG_ysens");
  zsens   = ValueSearch("MAG_zsens");

  // TODO: ������� ������ ���������, ��� ������ �������� ����� ������� ��� WHOAMI
  // TODO: ��������� � ��� ���������������

  #if CH_DBG_ENABLE_ASSERTS
    // clear bufers. Just to be safe.
    uint32_t i = 0;
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
          mag3110_semp);
  state = MAG_ACTIVE;
  chThdSleepMilliseconds(1);
}


