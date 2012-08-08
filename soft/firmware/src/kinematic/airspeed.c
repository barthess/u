#include <math.h>
/*
 * Pressure measurement unit
 * Рассчитывает воздушную скорость по сырым данным с MPX5100
 */

#include "uav.h"
#include "airspeed_table.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern CompensatedData comp_data;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/** термокомпенсация нуля
 * Принимает сырое значение с датчика и температуру в градусах цельсия*/
static uint16_t zerocomp(uint16_t raw, int16_t t){

  putinrange(t, MIN_TEMP, MAX_TEMP);

  uint16_t zero = zerocomp_table[t - MIN_TEMP];

  if (zero >= raw)
    return 0;
  else
    return raw - zero;
}

/* принимает сырое значение с датчика
 * возвращает воздушную скорость в м/с
 *
 * при комнатной температуре смещение нуля 0.201 V, вычитаемое значение 0.183 V,
 * на выходе усилителя 0.167 V
 * КУ получается - 9.277777
 */
#define KU    928     //КУ*100
#define Radc  122070  //uV*100 (чувствительность АЦП 5.0/4096 вольт на деление)
#define Smpx  450     //(Чувствительность датчика 450uV/Pa)

float calc_air_speed(uint16_t press_diff_raw){
  uint16_t p;
  p = zerocomp(press_diff_raw, comp_data.temp_onboard / 10);
  p = ((p * Radc) / Smpx) / KU; /* давление в паскалях */
  return sqrtf((float)(2*p) / 1.2);
}




