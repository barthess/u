#include <math.h>

#define ARM_MATH_CM3
#include "arm_math.h" // отсюда возьмем константу PI

#include "ch.h"
#include "hal.h"

#include "message.h"
#include "main.h"
#include "imu.h"
#include "adc_pns.h"
#include "dsp.h"

// TODO: сделать компенсацию нелинейности гироскопов, хранить в EEPROM
// TODO: сделать компенсацию нелинейности акселерометров, хранить в EEPROM

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern uint32_t GlobalFlags;

extern RawData raw_data;
extern LogItem log_item;

extern BinarySemaphore imu_sem;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
/* "опорный" весовой коэффициент для гироскопов. */
static float wGyroRef = 200;

static float Racc[]  = {0.01, 0.01, 0.99};  // проекция вектора тяжести на оси
static float Rest[]  = {0.01, 0.01, 0.99};  // проекция вектора тяжести на оси с учетом гироскопов

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

void imu_update(int16_t ax, int16_t ay, int16_t az){
  /* поправочные коэффициенты для не совсем прямого акселерометра */
  int32_t offsetx = 0;
  int32_t offsety = 0;
  int32_t offsetz = 0;

  /* Коэффициенты усиления. На это число нужно поделить полученное значение
   * с датчика чтобы получить ускорение в (g).
   * где:
   *    32768 -- шкала АЦП
   *    6 -- шкала акселерометра */
  float a_scalex = 32768 / 6.0;
  float a_scaley = 32768 / 6.0;
  float a_scalez = 32768 / 6.0;

  /* матрица для переворота осей акселерометра */
  int a_placematrix[] = {1, 1, 1};

  /* матрица для переворота осей гироскопов */
  int g_placematrix[] = {-1, -1, 1};

  /* чувствительности гироскопов
   * Тут по всем канонам должно быть 180 вместо 360, но я где-то проебал 2. */
  float g_sens_x = 0.003752 * (360.0 / PI); // v/(rag/s)
  float g_sens_y = 0.003752 * (360.0 / PI); // v/(rag/s)
  float g_sens_z = 0.003752 * (360.0 / PI); // v/(rag/s)

  /* время одного периода интегрирования */
  float T = GYRO_ADC_PERIOD;

  /* начальное значение для веса гироспов. Далее оно будет подкручиваться динамически */
  float wGyro = wGyroRef;
  /* длинна радиуса для нужд нормализации */
  float R = 1.0;

  /* коэффициенты пересчета из у.е. в углы поворота */
  #define Vref (3.3)        // опорник АЦП
  #define ADCSize (4096.0)  // разрядность АЦП
  #define Tcoef (1000000.0) // делитель для перевода времени из мкс в с
  const float gk_x = (Vref * T) / (ADCSize * g_sens_x * Tcoef * GYRO_AVG_SAMPLES_CNT);
  const float gk_y = (Vref * T) / (ADCSize * g_sens_y * Tcoef * GYRO_AVG_SAMPLES_CNT);
  const float gk_z = (Vref * T) / (ADCSize * g_sens_z * Tcoef * GYRO_AVG_SAMPLES_CNT);
  #undef Vref
  #undef ADCSize
  #undef Tcoef

  /* вспомогательные переменные */
  float Axz = 0.0;
  float Ayz = 0.0;
  float tmp1 = 0.0;
  float tmp2 = 0.0;

  /************************ обработка акселей *********************************/
  Racc[0] = (((float)(ax + offsetx)) / a_scalex) * a_placematrix[0];
  Racc[1] = (((float)(ay + offsety)) / a_scaley) * a_placematrix[1];
  Racc[2] = (((float)(az + offsetz)) / a_scalez) * a_placematrix[2];

  log_item.acceleration_x = (int16_t)(Racc[0] * 1000.0);
  log_item.acceleration_y = (int16_t)(Racc[1] * 1000.0);
  log_item.acceleration_z = (int16_t)(Racc[2] * 1000.0);

  R = sqrtf(Racc[0]*Racc[0] + Racc[1]*Racc[1] + Racc[2]*Racc[2]);
  Racc[0] = Racc[0] / R;
  Racc[1] = Racc[1] / R;
  Racc[2] = Racc[2] / R;


  /************************ обработка гироскопов*******************************/

  /* получим из условных единиц АЦП угол поворота в радианах */
  float fi_gyro_x_delta = (float)(raw_data.xgyro_delta * g_placematrix[0]) * gk_x;
  float fi_gyro_y_delta = (float)(raw_data.ygyro_delta * g_placematrix[1]) * gk_y;
  float fi_gyro_z_delta = (float)(raw_data.zgyro_delta * g_placematrix[2]) * gk_z;

  /* прибавим к оценочной матрице углы поворота с гироскопов */
  Ayz = atan2f(Rest[1], Rest[2]) + fi_gyro_x_delta;
  Axz = atan2f(Rest[0], Rest[2]) + fi_gyro_y_delta;

  /* возведение в степень заменим умножениями */
  tmp1 = cosf(Axz);
  tmp2 = tanf(Ayz);
  float RxGyro = sinf(Axz) / sqrtf(1 + (tmp1 * tmp1) * (tmp2 * tmp2));
  tmp1 = cosf(Ayz);
  tmp2 = tanf(Axz);
  float RyGyro = sinf(Ayz) / sqrtf(1 + (tmp1 * tmp1) * (tmp2 * tmp2));
  //float RxGyro = sinf(Axz) / sqrtf(1 + powf(cosf(Axz), 2) * powf(tanf(Ayz), 2));
  //float RyGyro = sinf(Ayz) / sqrtf(1 + powf(cosf(Ayz), 2) * powf(tanf(Axz), 2));

  /* FIXME: copysign плохо работает в граничных случаях, их надо обрабатывать отдельно
   * Тут вообще наглухо срывает крышу и значения превращаются в NaN */
  float RzGyro = copysignf(1, Rest[2]) * sqrtf(1 - RxGyro*RxGyro - RyGyro*RyGyro);

  /* получим новую оценочную матрицу с учетом весовых коэффициетов гироскопов */
  Rest[0] = (Racc[0] + RxGyro * wGyro) / (1 + wGyro);
  Rest[1] = (Racc[1] + RyGyro * wGyro) / (1 + wGyro);
  Rest[2] = (Racc[2] + RzGyro * wGyro) / (1 + wGyro);

  /* еще раз отнормируем */
  R = sqrtf(Rest[0]*Rest[0] + Rest[1]*Rest[1] + Rest[2]*Rest[2]);
  Rest[0] = Rest[0] / R;
  Rest[1] = Rest[1] / R;
  Rest[2] = Rest[2] / R;

  float k = 0x100000000 / (2.0 * PI);

  raw_data.xgyro_I += (int32_t)(fi_gyro_x_delta * k);
  raw_data.ygyro_I += (int32_t)(fi_gyro_y_delta * k);
  raw_data.zgyro_I += (int32_t)(fi_gyro_z_delta * k);

  log_item.imu_x = (int16_t)(Rest[0] * 10000);
  log_item.imu_y = (int16_t)(Rest[1] * 10000);
  log_item.imu_z = (int16_t)(Rest[2] * 10000);

  log_item.gyro_xI = (uint16_t)(raw_data.xgyro_I >> 16);
  log_item.gyro_yI = (uint16_t)(raw_data.ygyro_I >> 16);
  log_item.gyro_zI = (uint16_t)(raw_data.zgyro_I >> 16);
}




/**
 * Поток обработки инерациальных данных
 */
static WORKING_AREA(waImu, 512);
static msg_t Imu(void *arg) {
  (void)arg;

  chRegSetThreadName("IMU");

  while (TRUE) {
    chBSemWait(&imu_sem);
    imu_update(raw_data.acceleration_x,
               raw_data.acceleration_y,
               raw_data.acceleration_z);
  }
  return 0;
}


void ImuInit(void){
  /* зададим начальные значения, по изменению которые будем определять, что гироскопы выставились */
  log_item.imu_x = 16000;
  log_item.imu_y = 16000;
  log_item.imu_z = 16000;

  chThdCreateStatic(waImu, sizeof(waImu), NORMALPRIO - 5, Imu, NULL);
}

/**
 * Сбрасывает всё рассчитанное инерциалкой в начальное состояние
 */
void ImuReset(void){

}




