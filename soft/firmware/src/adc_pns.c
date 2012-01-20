#include "ch.h"
#include "hal.h"

#include "adc_pns.h"
#include "message.h"
#include "main.h"
#include "i2c.h"
#include "imu.h"
#include "dsp.h"

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;

extern RawData raw_data;
extern LogItem log_item;

extern volatile uint16_t cal_CurrentCoeff;
extern volatile uint8_t  cal_CurrentOffset;
extern volatile uint16_t cal_VoltageCoeff;

extern BinarySemaphore gyroadc_sem;
extern EventSource es_adc;
extern eventmask_t em_adcgyroready;
extern eventmask_t em_adcpowerready;

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define DEFAULT_CURRENT_COEFF  1912   // коэффициент пересчета из условных единиц в амперы для саломёта -- 37, для машинки -- 1912
#define DEFAULT_CURRENT_OFFSET 16   // смещение нуля датчика тока в единицах АЦП
#define DEFAULT_VOLTAGE_COEFF  1022 // коэффициент пересчета из условных единиц в децывольты

/*
 ******************************************************************************
 * FUNCTIONS PROTOTIPES
 ******************************************************************************
 */
void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n);
void adccb_gyrozeroing(ADCDriver *adcp, adcsample_t *buffer, size_t n);

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static ADCConfig adccfg; // для STM32 -- должна быть пустышка

/* Частота тактирования АЦП:
 *
 * SYSCLK/STM32_HPRE_DIV1/STM32_PPRE2_DIV2/STM32_ADCPRE_DIV8 = 72/1/2/4 = 9MHz
 *
 * The total conversion time is calculated as follows:
 * Tconv = Sampling time + 12.5 cycles
 * Example:
 * With an ADCCLK = 9 MHz and a sampling time of 239.5 cycles:
 * Tconv = 239.5 + 12.5 = 252 cycles
 * При частоте в 9МГц получается ровно 28 us.
 *
 * 1. Встроенный ИОН лучше вообще не трогать - его АЦП показывает полное фуфло.
 *
 * 2. Частота среза внутреннего RC-фильтра гироскопов = 140 Гц.
 * По теореме Котельникова часто дискретизации должна быть как минимум
 * в 2 раза выше. В реальных условиях надо дергать по 8-10 точек на период.
 * Отсюда - 140 * 8 = 1000 Гц.
*/
static ADCConversionGroup adccg = {
    TRUE,                     // буфер кольцевой?
    (uint16_t)(ADC_CH_NUM),   // количество каналов
    adccb_gyrozeroing,        // Изначально надо посчитать нули гироскопов
    NULL,                     // error cb
    0,                        // CR1 register
    ADC_CR2_TSVREFE,          // CR2 register. Vref on
    (0x1000000 - 1),          // SMPR1 (все на максимальное время)
    (0x40000000 - 1),         // SMPR2 (все на максимальное время)
    (ADC_CH_NUM - 1) << 20,   // SQR1
    0,                        // SQR2.
    // z, y, x, current, voltage, joy
    ((10 << 25) | (11 << 20) | (12 << 15) | (13 << 10) | (14 << 5) | 15), // SQR3
};

// результаты АЦП.
static adcsample_t samples_buf[ADC_BUF_DEPTH * ADC_CH_NUM];

// счетчик для выборки нужных сэмплов
static uint32_t adccnt = (0UL - 1UL);

// массив собранных значений для рассчета интеграла
static uint32_t gxv[4] = {0,0,0,0};
static uint32_t gyv[4] = {0,0,0,0};
static uint32_t gzv[4] = {0,0,0,0};

// счетчик для выставки нулей
static uint32_t zero_cnt = GYRO_AVG_SAMPLES_CNT;

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/* Коллбэк для выставки нулей.
 * Запускается после ресета контроллера и живёт до тех пор, пока не высчитает
 * нули. После этого переключает группу конверсии на другой коллбэк и сюда
 * мы больше никогда не попадаем. */
void adccb_gyrozeroing(ADCDriver *adcp, adcsample_t *buffer, size_t n){
  (void)adcp;
  (void)n;
  adccnt++;
  if ((adccnt & 0x7) == 0x7){// каждое 8-е прерывание
    if (zero_cnt > 0){
      raw_data.gyro_xAvg += buffer[GYRO_ADC_X_OFFSET];
      raw_data.gyro_yAvg += buffer[GYRO_ADC_Y_OFFSET];
      raw_data.gyro_zAvg += buffer[GYRO_ADC_Z_OFFSET];
    }
    else{
      GlobalFlags &= ~GYRO_CAL;
      /* не забываем сделать счетчик как было */
      adccnt = 0UL - 1UL;
      /* теперь из этого коллбэка переключаемся на основной коллбэк */
      adccg.end_cb = adccb;
      return;
    }
    zero_cnt--;
  }
}

/* Математически упрощенная функция интегрирования Симпсоном 3/8.
 * Снижение читабельности в угоду производительности.
 * Вынесем за скобки некоторые множители в обработчике прерывания:
 * 3 - количество промежутков интегрирования
 * 8 - делитель из каноничной формулы можно внести в состав GYRO_AVG_SAMPLES_CNT */
#define s38(a, b, c, d)      ((a) + 3*((b) + (c)) + (d))

/* Функция рассчета интеграла гироскопов по времени.
 * Дергается обработчиком прерываний АЦП по завершении всех преобразований
 * и по завершении половины преобразований.
 * У нас 6 каналов преобразования. На каждый канал тратится 28мкс, итого
 * 168мкс. Если брать каждое 8-е преобразование:
 * 1344мкс. Каждый заход надо насобирать 3 новых точки,
 * 4-я точка -- это старая, она должна стать первой в следующем заходе
 * 4032мкс для получения приращения угла. */
void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n){
  (void)adcp;
  (void)n;
  (void)buffer;
  uint32_t i = 0;
  adccnt++;
  if ((adccnt & 0xF) == 0xF){// каждое 16-е прерывание
    i = (adccnt >> 4) & 3;
    gxv[i] = samples_buf[GYRO_ADC_X_OFFSET] * (GYRO_AVG_SAMPLES_CNT / 8);
    gyv[i] = samples_buf[GYRO_ADC_Y_OFFSET] * (GYRO_AVG_SAMPLES_CNT / 8);
    gzv[i] = samples_buf[GYRO_ADC_Z_OFFSET] * (GYRO_AVG_SAMPLES_CNT / 8);
    if (i == 3){
      raw_data.gyro_x_delta = 3 * (s38(gxv[0],gxv[1],gxv[2],gxv[3]) - raw_data.gyro_xAvg);
      raw_data.gyro_y_delta = 3 * (s38(gyv[0],gyv[1],gyv[2],gyv[3]) - raw_data.gyro_yAvg);
      raw_data.gyro_z_delta = 3 * (s38(gzv[0],gzv[1],gzv[2],gzv[3]) - raw_data.gyro_zAvg);
      gxv[0] = gxv[3];
      gyv[0] = gyv[3];
      gzv[0] = gzv[3];

      chSysLockFromIsr();
      // пробуждение потока обработки инерциальных данных
      chBSemSignalI(&gyroadc_sem);
      chSysUnlockFromIsr();
    }
  }
}
#undef s38


/* Поток для запроса данных АЦП по таймеру */
static WORKING_AREA(PollADCThreadWA, 256);
__attribute__((noreturn))
static msg_t PollADCThread(void *arg){
  chRegSetThreadName("PollADC");
  (void)arg;
  systime_t time = chTimeNow();       // T0

  while(TRUE){
    time += MS2ST(NORMAL_ADC_PERIOD); // Next deadline
    chThdSleepUntil(time);

    raw_data.main_current = samples_buf[CURRENT_ADC_OFFSET];
    raw_data.main_voltage = samples_buf[VOLTAGE_ADC_OFFSET];

    log_item.main_current = (uint16_t)((__USAT(raw_data.main_current - cal_CurrentOffset, 15) * 1000) / cal_CurrentCoeff);
    uint16_t voltage = (raw_data.main_voltage * 100) / cal_VoltageCoeff;
    log_item.main_voltage = (uint8_t)__USAT(voltage, 8);
    //chEvtBroadcastFlags(&es_adc, em_adcpowerready);
  }
}


inline void ADCInit_pns(void){
  /* Настройка лапок */
  palSetPadMode(IOPORT3, 0, PAL_MODE_INPUT_ANALOG); // EXT2-7 gyro_Z ADC10
  palSetPadMode(IOPORT3, 1, PAL_MODE_INPUT_ANALOG); // EXT2-8 gyro_Y ADC11
  palSetPadMode(IOPORT3, 2, PAL_MODE_INPUT_ANALOG); // EXT2-9 gyro_X ADC12
  palSetPadMode(IOPORT3, 3, PAL_MODE_INPUT_ANALOG); // ток ADC13
  palSetPadMode(IOPORT3, 4, PAL_MODE_INPUT_ANALOG); // батарейка ADC14
  palSetPadMode(IOPORT3, 5, PAL_MODE_INPUT_ANALOG); // джойстик ADC15
                                                    // внутренний ИОН ADC17

  GlobalFlags |= GYRO_CAL;

  adcStart(&ADCD1, &adccfg);
  chThdSleepMilliseconds(500); /* время на прогрев гироскопов и АЦП */
  adcStartConversion(&ADCD1, &adccg, samples_buf, ADC_BUF_DEPTH);

  //"TODO: Read settings from EEPROM here"
  cal_CurrentCoeff  = DEFAULT_CURRENT_COEFF;
  cal_CurrentOffset = DEFAULT_CURRENT_OFFSET;
  cal_VoltageCoeff  = DEFAULT_VOLTAGE_COEFF;

  chThdCreateStatic(PollADCThreadWA,
          sizeof(PollADCThreadWA),
          NORMALPRIO,
          PollADCThread,
          NULL);
}


