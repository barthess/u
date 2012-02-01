#include "ch.h"
#include "hal.h"

#include "i2c_pns.h"
#include "bmp085.h"
#include "bmp085_table.h"
#include "message.h"
#include "main.h"

#include "mavlink.h"
#include "common.h"
#include "bart.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define bmp085addr          0b1110111
#define TEMPERATURE_ERROR   0// флаг того, что при измерении температуры произошла ошибка
#define PRESSURE_ERROR      0// флаг того, что при измерении довления произошла ошибка

// sensor precision (see datasheet)
#define OSS 3 // 3 -- max

// filtering constants
#define N_AWG      32 // Averaging values count
#define FIX_FORMAT 5  // 32 == 2^5 to replace division by shift

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern LogItem log_item;
extern BinarySemaphore bmp085_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
// input and output buffers
static uint8_t rxbuf[BMP085_RX_DEPTH];
static uint8_t txbuf[BMP085_TX_DEPTH] = {0x55,0x55};

// bmp085 calibration coefficients
static int16_t  ac1=0, ac2=0, ac3=0, b1=0, b2=0, mb=0, mc=0, md=0;
static uint16_t ac4=0, ac5=0, ac6=0;

// uncompensated temperature and pressure values
static uint32_t up = 0, ut = 0;

// aweraged value
static uint32_t pres_awg = 10UL << FIX_FORMAT;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 * calculation height from pressure using precalculated table and linear interpolation
 */
static int16_t pres_to_height(uint32_t pres){
  uint16_t i = 0;
  int32_t dp = 0;

  if(pres > BMP085_MAX_PRES)
    return ptable[0];
  if(pres < (BMP085_MIN_PRES - BMP085_STEP))
    return ptable[(sizeof(ptable) / sizeof(int16_t)) - 1];

  i  = (BMP085_MAX_PRES - pres) >> 8;         // pseudo divide by 256
  dp = (BMP085_MAX_PRES - pres) & 0b11111111; // pseudo modulo by 256

  return(ptable[i] + (((ptable[i+1] - ptable[i]) * dp) >> 8));
}

/**
 * calculation of compensated pressure value
 */
static void bmp085_calc(void){

  // compensated temperature and pressure values
  uint32_t pval = 0;
  int32_t  tval = 0;

  if (ut == TEMPERATURE_ERROR)
    goto ERROR;

  if (up == PRESSURE_ERROR)
    goto ERROR;

  /* Calculate pressure using black magic from datasheet */
  int32_t  x1, x2, x3, b3, b5, b6, p;
  uint32_t  b4, b7;

  x1 = (ut - ac6) * ac5 >> 15;
  x2 = ((int32_t) mc << 11) / (x1 + md);
  b5 = x1 + x2;
  tval = (b5 + 8) >> 4;
  raw_data.temp_bmp085 = (int16_t)tval;

  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11;
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
  b3 = ((((int32_t)ac1 * 4 + x3) << OSS) + 2) >> 2;

  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (uint32_t)(x3 + 32768)) >> 15;
  b7 = ((uint32_t)up - b3) * (50000 >> OSS);
  if(b7 < 0x80000000)
    p = (b7 * 2) / b4;
  else
    p = (b7 / b4) * 2;

  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357L * p) >> 16;
  pval = p + ((x1 + x2 + 3791) >> 4);
  // end of black magic

  raw_data.pressure_static = pval;

  // refresh aweraged pressure value
  pres_awg = pres_awg - (pres_awg >> FIX_FORMAT) + pval;
  // calculate height
  log_item.baro_altitude = pres_to_height(pres_awg >> FIX_FORMAT);
  return;

ERROR:
  raw_data.pressure_static = 0;
  log_item.baro_altitude = -32768;
  return;
}

/**
 * Функция для вычитывания температуры из датчика
 */
static uint32_t get_temperature(void){
  txbuf[0] = BOSCH_CTL;
  txbuf[1] = BOSCH_TEMP;
  if (i2c_transmit(bmp085addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    return TEMPERATURE_ERROR;

  /* wait temperature results (datasheet says 4.5 ms) */
  if (chBSemWaitTimeout(&bmp085_sem, MS2ST(5)) != RDY_OK)
    return TEMPERATURE_ERROR;

  /* read measured value */
  txbuf[0] = BOSCH_ADC_MSB;
  if (i2c_transmit(bmp085addr, txbuf, 1, rxbuf, 2) != RDY_OK)
    return TEMPERATURE_ERROR;

  return (rxbuf[0] << 8) + rxbuf[1];
}

/**
 * Функция для вычитывания довления из датчика
 */
static uint32_t get_pressure(void){
  // command to measure pressure
  txbuf[0] = BOSCH_CTL;
  txbuf[1] = (0x34 + (OSS<<6));
  if (i2c_transmit(bmp085addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    return PRESSURE_ERROR;

  /* wait temperature results (datasheet says 25.5 ms) */
  if (chBSemWaitTimeout(&bmp085_sem, MS2ST(26)) != RDY_OK)
    return PRESSURE_ERROR;

  /* acqure pressure */
  txbuf[0] = BOSCH_ADC_MSB;
  if (i2c_transmit(bmp085addr, txbuf, 1, rxbuf, 3) != RDY_OK)
    return PRESSURE_ERROR;

  return ((rxbuf[0] << 16) + (rxbuf[1] << 8) + rxbuf[2]) >> (8 - OSS);
}

/**
 * Polling thread
 */
static WORKING_AREA(PollBaroThreadWA, 256);
static msg_t PollBaroThread(void *arg){
  chRegSetThreadName("PollBaro");
  (void)arg;
  uint32_t t = 0;

  while (TRUE) {
    /* we get temperature every 0x1F cycle */
    if ((t & 0x1F) == 0x1F)
      ut = get_temperature();

    up = get_pressure();
    bmp085_calc();

    t++;
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void init_bmp085(void){

  txbuf[0] = 0xAA;
  while(i2c_transmit(bmp085addr, txbuf, 1, rxbuf, 22) != RDY_OK)
    ;
  ac1 = (rxbuf[0]  << 8) + rxbuf[1];
  ac2 = (rxbuf[2]  << 8) + rxbuf[3];
  ac3 = (rxbuf[4]  << 8) + rxbuf[5];
  ac4 = (rxbuf[6]  << 8) + rxbuf[7];
  ac5 = (rxbuf[8]  << 8) + rxbuf[9];
  ac6 = (rxbuf[10] << 8) + rxbuf[11];
  b1  = (rxbuf[12] << 8) + rxbuf[13];
  b2  = (rxbuf[14] << 8) + rxbuf[15];
  mb  = (rxbuf[16] << 8) + rxbuf[17];
  mc  = (rxbuf[18] << 8) + rxbuf[19];
  md  = (rxbuf[20] << 8) + rxbuf[21];

  chThdCreateStatic(PollBaroThreadWA,
          sizeof(PollBaroThreadWA),
          I2C_THREADS_PRIO,
          PollBaroThread,
          NULL);
}

