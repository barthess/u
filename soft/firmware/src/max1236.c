#include "ch.h"
#include "hal.h"

#define ARM_MATH_CM4

#include "arm_math.h"

#include "message.h"
#include "dsp.h"
#include "main.h"
#include "i2c_pns.h"

#include "max1236.h"

#include <mavlink.h>
#include <bart.h>
#include <common.h>

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define max1236addr 0b0110100

/**сонар выдает Vcc/1024 вольт на см
 * разрешающая способность АЦП Vcc/4096
 * Итого: для получения высоты в см надо полученный результат поделить на 4 */
#define SONAR_COEF 4

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern RawData raw_data;
extern LogItem log_item;
extern Mailbox tolink_mb;
extern uint64_t TimeUsec;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[MAX1236_RX_DEPTH];
static uint8_t txbuf[MAX1236_TX_DEPTH];

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/* воздушная скорость */
// TODO: заменить термокомпенсацию if'ми какой-нибудь квадратичной функцией
static void calc_air_speed(uint16_t press_diff_raw){

  int32_t pres_diff_scale;
  uint32_t pres_dyn_offset; // смещение шкалы, зависящее от температуры

  if(raw_data.temp_tmp75 > 2600)
    pres_dyn_offset = 1540 + (115 * raw_data.temp_tmp75) / 1000;
  else
    pres_dyn_offset = 1540 + (110 * raw_data.temp_tmp75) / 1000;

  pres_diff_scale = (press_diff_raw - pres_dyn_offset) * 245;
  pres_diff_scale = __USAT(pres_diff_scale, 31);
  raw_data.pressure_dynamic = (uint16_t)(pres_diff_scale / 1000); // (Па)

  /* допустим, что входное значение не превышает 4096, тогда сдвигами
   * на 3 позиции влево переведем входное значение в "виртульную" область
   * а сдвигом на 3^2 позиции после вычисления корня переведем обратно в "реальную"
   * это получается после упрощения выражения:
   * (arm_sqrt_q15((х * 2^18)/32768)) / 2^9      */
  q15_t in = (2L * pres_diff_scale / 1225L) << 3;
  q15_t out = 0;
  arm_sqrt_q15(in, &out);
  //log_item.air_speed = (uint8_t)__USAT((out >> 9), 8); // для получения целых
  log_item.air_speed = (uint8_t)__USAT((out >> 6), 8); // для получения фиксированной точки 5:3
}







/** Опрос max1236
 * после настройки достаточно просто читать из него данные, по 2 байта на канал
 * после отправки запроса АЦП занимает линию примерно на 8.3uS, после чего
 * отдает результат. Как только мастер вычитал нужное количество байт - дает
 * в шину STOP.
 * При частоте 100кГц на вычитывание 4 значений уйдет примерно:
 * 10 * (4 * 2 * 8) + 8.3 * 4 = 673.2 uS
 *
 *---------------- Ход рассчета: --------------------------------------
 * Смещение шкалы в единицах АЦП. Зависит от температуры
 * if (t_tmp75 > 26):
 *     pressure_offset = 1530 + 11.5 * t_tmp75
 * else:
 *     pressure_offset = 1530 + 11.0 * t_tmp75
 * k = 11.08 # коэффициент усиления операционника
 * r = 5.0/4096 # вольт на деление АЦП
 * s = 0.00045 # вольт на паскаль
 * dyn = (((raw_pressure - pressure_offset) * r) / k) / s # в паскалях
 * после упрощения выражения получаем:
 * (raw_pressure - pressure_offset) * 0,2448 (Па)
 * или
 * (raw_pressure - pressure_offset) * 245 (мПа)
 *
 *
 * новые данные по рассчету:
 * при комнатной температуре смещение нуля 0.201 V, вычитаемое значение 0.183 V,
 * на выходе усилителя 0.167 V
 */
static WORKING_AREA(PollMax1236ThreadWA, 512);
static msg_t PollMax1236Thread(void *arg) {
  chRegSetThreadName("PollMax1236");
  (void)arg;
  int16_t press_diff_raw;
  int16_t sonar_raw;
  mavlink_raw_pressure_t pres_data;

  Mail air_data_mail;
  air_data_mail.payload = NULL;
  air_data_mail.invoice = MAVLINK_MSG_ID_RAW_PRESSURE;
  air_data_mail.confirmbox = NULL;

  uint32_t n = 0;

  while (TRUE) {
    chThdSleepMilliseconds(20);

    if (i2c_receive(max1236addr, rxbuf, MAX1236_RX_DEPTH) == RDY_OK){
      press_diff_raw = ((rxbuf[0] & 0xF) << 8) + rxbuf[1];
      sonar_raw = ((rxbuf[2] & 0xF) << 8) + rxbuf[3];

      /* высота по сонару */
      raw_data.altitude_sonar = sonar_raw;
      log_item.altitude_sonar = raw_data.altitude_sonar; // save to log
    }

    pres_data.time_usec = TimeUsec;
    pres_data.press_diff1 = press_diff_raw;
    if (((n & 7) == 7) && (air_data_mail.payload == NULL)){
      air_data_mail.payload = &pres_data;
      chMBPost(&tolink_mb, (msg_t)&air_data_mail, TIME_IMMEDIATE);
    }

    n++;
  }
  return 0;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 * see datasheet on page 13 how to initialize ADC
 */
void init_max1236(void){

#if CH_DBG_ENABLE_ASSERTS
  // clear bufers. Just to be safe.
  uint8_t i = 0;
  for (i = 0; i < MAX1236_TX_DEPTH; i++){txbuf[i] = 0x55;}
  for (i = 0; i < MAX1236_RX_DEPTH; i++){rxbuf[i] = 0x55;}
#endif

  txbuf[0] = 0b11110011;
  txbuf[1] = 0b00000101;

  while(i2c_transmit(max1236addr, txbuf, 2, rxbuf, 0) != RDY_OK)
    ;

  chThdCreateStatic(PollMax1236ThreadWA,
          sizeof(PollMax1236ThreadWA),
          I2C_THREADS_PRIO,
          PollMax1236Thread,
          NULL);
}

