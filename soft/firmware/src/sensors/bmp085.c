#include "ch.h"
#include "hal.h"

#include "arm_math.h"

#include "i2c_local.h"
#include "bmp085.h"
#include "bmp085_table.h"
#include "sensors.h"
#include "message.h"
#include "main.h"
#include "link.h"


/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define bmp085addr          0b1110111
#define TEMPERATURE_ERROR   0
#define PRESSURE_ERROR      0

// sensor precision (see datasheet)
#define OSS 3 // 3 -- max

// filtering constants
#define N_AWG      32 // Averaging values count
#define FIX_FORMAT 5  // 32 == 2^5 to replace division by shift

#define BLOCK_SIZE 1 /* FIR filtering block size */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern CompensatedData comp_data;
extern EventSource init_event;

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

/* filtered value */
static uint32_t pres_awg = 10UL << FIX_FORMAT;
static int32_t  pres_fir = 100000;

/* filtering coefficients */
static q31_t firCoeffs[33] = {0, 561969, 2337062, 5572473, 10615881, 17830251, 27495135, 39711165, 54324315, 70883798, 88642511, 106602604, 123601838, 138430111, 149960741, 157278541, 159786860, 157278541, 149960741, 138430111, 123601838, 106602604, 88642511, 70883798, 54324315, 39711165, 27495135, 17830251, 10615881, 5572473, 2337062, 561969, 0};
//static q31_t firCoeffs[33] = {0, 452653, 1945095, 4779443, 9358996, 16117507, 25422603, 37470203, 52190041, 69181933, 87698263, 106680852, 124851191, 140843608, 153362998, 161343745, 164085387, 161343745, 153362998, 140843608, 124851191, 106680852, 87698263, 69181933, 52190041, 37470203, 25422603, 16117507, 9358996, 4779443, 1945095, 452653, 0};
//static q31_t firCoeffs[33] = {0, 560306, 2331154, 5560622, 10597250, 17805058, 27464875, 39678685, 54293625, 70859575, 88629370, 106604255, 123620311, 138465225, 150009943, 157337169, 159848802, 157337169, 150009943, 138465225, 123620311, 106604255, 88629370, 70859575, 54293625, 39678685, 27464875, 17805058, 10597250, 5560622, 2331154, 560306, 0};
//static q31_t firCoeffs[129] = {0, 8190, 32912, 74520, 133532, 210629, 306645, 422560, 559483, 718647, 901383, 1109110, 1343309, 1605507, 1897250, 2220081, 2575518, 2965025, 3389987, 3851690, 4351287, 4889783, 5468003, 6086577, 6745912, 7446177, 8187286, 8968877, 9790304, 10650625, 11548593, 12482650, 13450925, 14451238, 15481095, 16537703, 17617976, 18718544, 19835774, 20965784, 22104465, 23247504, 24390410, 25528540, 26657129, 27771322, 28866205, 29936840, 30978296, 31985690, 32954215, 33879178, 34756036, 35580426, 36348200, 37055456, 37698565, 38274203, 38779373, 39211428, 39568093, 39847484, 40048117, 40168926, 40209268, 40168926, 40048117, 39847484, 39568093, 39211428, 38779373, 38274203, 37698565, 37055456, 36348200, 35580426, 34756036, 33879178, 32954215, 31985690, 30978296, 29936840, 28866205, 27771322, 26657129, 25528540, 24390410, 23247504, 22104465, 20965784, 19835774, 18718544, 17617976, 16537703, 15481095, 14451238, 13450925, 12482650, 11548593, 10650625, 9790304, 8968877, 8187286, 7446177, 6745912, 6086577, 5468003, 4889783, 4351287, 3851690, 3389987, 2965025, 2575518, 2220081, 1897250, 1605507, 1343309, 1109110, 901383, 718647, 559483, 422560, 306645, 210629, 133532, 74520, 32912, 8190, 0};
//static q31_t firCoeffs[129] = {0, -2479, -10262, -23788, -43386, -69247, -101411, -139731, -183849, -233156, -286756, -343425, -401573, -459201, -513866, -562648, -602124, -628344, -636827, -622558, -580003, -503135, -385478, -220163, 0, 282432, 634683, 1064315, 1578772, 2185238, 2890491, 3700747, 4621501, 5657371, 6811944, 8087627, 9485509, 11005245, 12644941, 14401078, 16268442, 18240095, 20307362, 22459853, 24685517, 26970721, 29300363, 31658015, 34026091, 36386045, 38718587, 41003923, 43222009, 45352815, 47376603, 49274197, 51027260, 52618557, 54032211, 55253936, 56271256, 57073691, 57652916, 58002893, 58119960, 58002893, 57652916, 57073691, 56271256, 55253936, 54032211, 52618557, 51027260, 49274197, 47376603, 45352815, 43222009, 41003923, 38718587, 36386045, 34026091, 31658015, 29300363, 26970721, 24685517, 22459853, 20307362, 18240095, 16268442, 14401078, 12644941, 11005245, 9485509, 8087627, 6811944, 5657371, 4621501, 3700747, 2890491, 2185238, 1578772, 1064315, 634683, 282432, 0, -220163, -385478, -503135, -580003, -622558, -636827, -628344, -602124, -562648, -513866, -459201, -401573, -343425, -286756, -233156, -183849, -139731, -101411, -69247, -43386, -23788, -10262, -2479, 0};
//static q31_t firCoeffs[65] = {0, 68603, 277511, 635451, 1156186, 1857759, 2761465, 3890589, 5268982, 6919503, 8862426, 11113858, 13684247, 16577047, 19787595, 23302257, 27097891, 31141652, 35391151, 39795000, 44293695, 48820848, 53304708, 57669932, 61839553, 65737061, 69288547, 72424808, 75083374, 77210349, 78762022, 79706189, 80023125, 79706189, 78762022, 77210349, 75083374, 72424808, 69288547, 65737061, 61839553, 57669932, 53304708, 48820848, 44293695, 39795000, 35391151, 31141652, 27097891, 23302257, 19787595, 16577047, 13684247, 11113858, 8862426, 6919503, 5268982, 3890589, 2761465, 1857759, 1156186, 635451, 277511, 68603, 0};

/* buffer for filter state */
static q31_t firState[sizeof(firCoeffs)/sizeof(q31_t) + BLOCK_SIZE - 1];

/* filter */
static arm_fir_instance_q31 bmp_85_fir;

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
  comp_data.baro_filtered_awg = pres_awg;

  /* refresh filtered value */
  q31_t pres_in = pval * 128;
  arm_fir_q31(&bmp_85_fir, &pres_in, &pres_fir, BLOCK_SIZE);
  comp_data.baro_filtered_fir = pres_fir;

  // calculate height
  comp_data.baro_altitude = pres_to_height(pres_awg >> FIX_FORMAT);
  mavlink_vfr_hud_struct.alt = (float)comp_data.baro_altitude / 10.0;
  mavlink_scaled_pressure_struct.press_abs = (float)pres_awg / (N_AWG * 100.0);
  mavlink_scaled_pressure_struct.press_diff = (float)pres_fir / (128 * 100.0);
  //mavlink_scaled_pressure_struct.press_diff = (float)pval / 100.0;
  return;

ERROR:
  raw_data.pressure_static = 0;
  comp_data.baro_altitude = -32768;
  return;
}

/**
 *
 */
static uint32_t get_temperature(BinarySemaphore *semp){
  txbuf[0] = BOSCH_CTL;
  txbuf[1] = BOSCH_TEMP;
  if (i2c_transmit(bmp085addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    return TEMPERATURE_ERROR;

  /* wait temperature results (datasheet says 4.5 ms) */
  if (chBSemWaitTimeout(semp, MS2ST(5)) != RDY_OK)
    return TEMPERATURE_ERROR;

  /* read measured value */
  txbuf[0] = BOSCH_ADC_MSB;
  if (i2c_transmit(bmp085addr, txbuf, 1, rxbuf, 2) != RDY_OK)
    return TEMPERATURE_ERROR;

  return (rxbuf[0] << 8) + rxbuf[1];
}

/**
 *
 */
static uint32_t get_pressure(BinarySemaphore *semp){
  // command to measure pressure
  txbuf[0] = BOSCH_CTL;
  txbuf[1] = (0x34 + (OSS<<6));
  if (i2c_transmit(bmp085addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    return PRESSURE_ERROR;

  /* wait pressure results (datasheet says 25.5 ms) */
  if (chBSemWaitTimeout(semp, MS2ST(26)) != RDY_OK)
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
static msg_t PollBaroThread(void *semp){
  chRegSetThreadName("PollBaro");
  uint32_t t = 0;

  struct EventListener self_el;
  chEvtRegister(&init_event, &self_el, INIT_FAKE_EVID);

  while (TRUE) {
    /* we get temperature every 0x1F cycle */
    if ((t & 0x1F) == 0x1F)
      ut = get_temperature((BinarySemaphore*)semp);

    up = get_pressure((BinarySemaphore*)semp);
    bmp085_calc();

    t++;

    if (chThdSelf()->p_epending & EVENT_MASK(SIGHALT_EVID))
      chThdExit(RDY_OK);
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void init_bmp085(BinarySemaphore *bmp085_semp){

  /* initialize filter */
  arm_fir_init_q31(&bmp_85_fir, sizeof(firCoeffs)/sizeof(q31_t),
                    firCoeffs, firState, BLOCK_SIZE);

  /* get calibration coefficients from sensor */
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

  /**/
  chThdSleepMilliseconds(2);
  chThdCreateStatic(PollBaroThreadWA,
          sizeof(PollBaroThreadWA),
          I2C_THREADS_PRIO,
          PollBaroThread,
          bmp085_semp);
  chThdSleepMilliseconds(2);
}

