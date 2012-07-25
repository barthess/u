#include "ch.h"
#include "hal.h"

#include "sensors.h"
#include "message.h"
#include "utils.h"
#include "airspeed.h"
#include "main.h"
#include "i2c_local.h"
#include "max1236.h"
#include "link.h"
#include "logger.h"
#include "timekeeping.h"
#include "dsp.h"

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
extern CompensatedData comp_data;
extern EventSource init_event;
extern Mailbox logwriter_mb;

extern mavlink_raw_pressure_t     mavlink_raw_pressure_struct;
extern mavlink_scaled_pressure_t  mavlink_scaled_pressure_struct;
extern mavlink_vfr_hud_t          mavlink_vfr_hud_struct;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static uint8_t rxbuf[MAX1236_RX_DEPTH];
static uint8_t txbuf[MAX1236_TX_DEPTH];

/**/
static alphabeta_instance_q31 press_diff_filter;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/** Опрос max1236
 * после настройки достаточно просто читать из него данные, по 2 байта на канал
 * после отправки запроса АЦП занимает линию примерно на 8.3uS, после чего
 * отдает результат. Как только мастер вычитал нужное количество байт - дает
 * в шину STOP.
 * При частоте 100кГц на вычитывание 4 значений уйдет примерно:
 * 10 * (4 * 2 * 8) + 8.3 * 4 = 673.2 uS
 */
static WORKING_AREA(PollMax1236ThreadWA, 256);
static msg_t PollMax1236Thread(void *arg) {
  chRegSetThreadName("PollMax1236");
  (void)arg;

  q31_t press;
  uint16_t sonar;
  const uint16_t filter_comp = 10000; // constant for compesate filter flyback delay

  struct EventListener self_el;
  chEvtRegister(&init_event, &self_el, INIT_FAKE_EVID);

  while (TRUE) {
    chThdSleepMilliseconds(20);

    if (i2c_receive(max1236addr, rxbuf, MAX1236_RX_DEPTH) == RDY_OK){

      press = ((rxbuf[0] & 0xF) << 8) + rxbuf[1];
      sonar = ((rxbuf[2] & 0xF) << 8) + rxbuf[3];

      press = alphabeta_q31(&press_diff_filter, press + filter_comp);
      press -= filter_comp;

      raw_data.pressure_dynamic = press;
      raw_data.altitude_sonar = sonar;

      mavlink_vfr_hud_struct.airspeed = calc_air_speed(raw_data.pressure_dynamic);

      mavlink_raw_pressure_struct.press_diff1 = raw_data.pressure_dynamic;
      mavlink_raw_pressure_struct.temperature = raw_data.temp_tmp75;
      mavlink_raw_pressure_struct.time_usec = pnsGetTimeUnixUsec();

      mavlink_scaled_pressure_struct.time_boot_ms = TIME_BOOT_MS;

      comp_data.air_speed = (uint16_t)(1000 * mavlink_vfr_hud_struct.airspeed);

      if (chThdSelf()->p_epending & EVENT_MASK(LOGGER_READY_EVID)){
        log_write_schedule(MAVLINK_MSG_ID_VFR_HUD);
        log_write_schedule(MAVLINK_MSG_ID_RAW_PRESSURE);
        log_write_schedule(MAVLINK_MSG_ID_SCALED_PRESSURE);
      }
    }
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

/**
 * see datasheet on page 13 how to initialize ADC
 */
void init_max1236(void){

  if (alphabeta_init_q31(&press_diff_filter, 3, 0) != CH_SUCCESS)
    chDbgPanic("Wrong len");

#if CH_DBG_ENABLE_ASSERTS
  // clear bufers. Just to be safe.
  uint32_t i = 0;
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
  chThdSleepMilliseconds(1);
}

