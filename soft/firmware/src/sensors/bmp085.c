#include "uav.h"

#include "bmp085_table.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define bmp085addr          0b1110111

// sensor precision (see datasheet)
#define OSS 3 // 3 -- max

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern CompensatedData comp_data;

extern mavlink_vfr_hud_t          mavlink_vfr_hud_struct;
extern mavlink_scaled_pressure_t  mavlink_scaled_pressure_struct;

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

/**/
static alphabeta_instance_float bmp085_filter_f32;
static alphabeta_instance_float bmp085_climb_filter_f32;

/* length of filter */
static uint32_t const *flen_pres_stat;
static uint32_t const *flen_climb;

/* value to calculate time between measurements and climb rate */
static systime_t measurement_time_prev;
static systime_t measurement_time;

static float altitude = 0;
static float altitude_prev = 0;
static float climb = 0;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 * calculation height from pressure using precalculated table and linear interpolation
 * return height in decimeters.
 */
//static int16_t pres_to_height(uint32_t pres){
//  uint16_t i = 0;
//  int32_t dp = 0;
//
//  if(pres > BMP085_MAX_PRES)
//    return ptable[0];
//  if(pres < (BMP085_MIN_PRES - BMP085_STEP))
//    return ptable[(sizeof(ptable) / sizeof(int16_t)) - 1];
//
//  i  = (BMP085_MAX_PRES - pres) >> 8;         // pseudo divide by 256
//  dp = (BMP085_MAX_PRES - pres) & 0b11111111; // pseudo modulo by 256
//
//  return(ptable[i] + (((ptable[i+1] - ptable[i]) * dp) >> 8));
//}

/**
 *
 */
static float press_to_height_f32(uint32_t press){
  const float p0 = 101325.0;
  return 44330.0 * (1.0 - powf((float)press/p0, 1.0/5.255));
}

/**
 * calculation of compensated pressure value
 */
static void bmp085_calc(void){
  // compensated temperature and pressure values
  uint32_t pval = 0;
  int32_t  tval = 0;

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

  altitude = press_to_height_f32(pval);

  measurement_time = chTimeNow();
  climb = (CH_FREQUENCY * (altitude - altitude_prev)) / (measurement_time - measurement_time_prev);
  measurement_time_prev = measurement_time;
  altitude_prev = altitude;

  comp_data.baro_climb = alphabeta_float(&bmp085_climb_filter_f32, climb, *flen_climb);
  comp_data.baro_altitude = alphabeta_float(&bmp085_filter_f32, altitude, *flen_pres_stat);

  mavlink_vfr_hud_struct.alt = comp_data.baro_altitude;
  mavlink_vfr_hud_struct.climb = comp_data.baro_climb;
  mavlink_vfr_hud_struct.alt = comp_data.baro_altitude;
  mavlink_scaled_pressure_struct.press_abs = (float)pval / 100.0;
}

/**
 *
 */
static uint32_t get_temperature(BinarySemaphore *semp, int32_t *retry){

  txbuf[0] = BOSCH_CTL;
  txbuf[1] = BOSCH_TEMP;
  i2c_transmit(bmp085addr, txbuf, 2, rxbuf, 0);

  /* wait temperature results (datasheet says 4.5 ms) */
  if (chBSemWaitTimeout(semp, MS2ST(10)) != RDY_OK)
    (*retry)--;

  /* read measured value */
  txbuf[0] = BOSCH_ADC_MSB;
  i2c_transmit(bmp085addr, txbuf, 1, rxbuf, 2);
  return (rxbuf[0] << 8) + rxbuf[1];
}

/**
 *
 */
static uint32_t get_pressure(BinarySemaphore *semp, int32_t *retry){

  // command to measure pressure
  txbuf[0] = BOSCH_CTL;
  txbuf[1] = (0x34 + (OSS<<6));
  i2c_transmit(bmp085addr, txbuf, 2, rxbuf, 0);


  /* wait pressure results (datasheet says 25.5 ms) */
  if (chBSemWaitTimeout(semp, MS2ST(50)) != RDY_OK)
    (*retry)--;

  /* acqure pressure */
  txbuf[0] = BOSCH_ADC_MSB;
  i2c_transmit(bmp085addr, txbuf, 1, rxbuf, 3);
  return ((rxbuf[0] << 16) + (rxbuf[1] << 8) + rxbuf[2]) >> (8 - OSS);
}

/**
 * Polling thread
 */
static WORKING_AREA(PollBaroThreadWA, 256);
static msg_t PollBaroThread(void *semp){
  chRegSetThreadName("PollBaro");
  uint32_t t = 0;
  int32_t retry = 20;

  while (TRUE) {
    chDbgAssert(retry > 0, "PollAccelThread(), #1",
          "probably no interrupts from pressure sensor");

    /* we get temperature every 0x1F cycle */
    if ((t & 0x1F) == 0x1F)
      ut = get_temperature((BinarySemaphore*)semp, &retry);

    up = get_pressure((BinarySemaphore*)semp, &retry);
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
void init_bmp085(BinarySemaphore *bmp085_semp){

  flen_pres_stat = ValueSearch("FLEN_pres_stat");
  flen_climb     = ValueSearch("FLEN_climb");

  /* get calibration coefficients from sensor */
  txbuf[0] = 0xAA;
  i2c_transmit(bmp085addr, txbuf, 1, rxbuf, 22);

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

  /**/
  chThdSleepMilliseconds(2);
  chThdCreateStatic(PollBaroThreadWA,
          sizeof(PollBaroThreadWA),
          I2C_THREADS_PRIO,
          PollBaroThread,
          bmp085_semp);
  chThdSleepMilliseconds(2);
}

