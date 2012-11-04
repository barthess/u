#ifndef SENSORS_H_
#define SENSORS_H_


/*
 * Обработанные данные.
 */
typedef struct CompensatedData CompensatedData;
struct CompensatedData{
  /* Накопленные углы поворота с момента включения устройства (для отладки). Градусы */
  float     xgyro_angle;
  float     ygyro_angle;
  float     zgyro_angle;
  /* моментальные угловые скорости в рад/с */
  float     xgyro;
  float     ygyro;
  float     zgyro;
  /* моментальные угловые скорости в uRad/s */
  int32_t   xgyroi;
  int32_t   ygyroi;
  int32_t   zgyroi;
  /* ускорения по осям в mG */
  int16_t   xacc;
  int16_t   yacc;
  int16_t   zacc;
  /* магнитное поле в T */
  float     xmag;
  float     ymag;
  float     zmag;

  /**/
  float     baro_altitude;      /* высота по барометру bmp085 (m)*/
  float     baro_climb;         /* вертикальная скорость (m/s) */
  uint16_t  air_speed;          /* воздушная скорость. Фиксированная точка. (mm/s)*/
  int16_t   temp_onboard;       /* температура c tmp75. (цельсий / 100). */
  // напряжение и ток бортовой сети
  uint16_t  main_voltage;      // mV
  uint32_t  main_current;      // mA
  uint16_t  secondary_voltage; // mV напряга с вторичного источника питания для серв и приемника

  float     groundspeed_odo;   // Current ground speed by odometer (m/s)
  float     groundspeed_gps;   // Current ground speed by gps (m/s)
  float     heading;           // Current heading in radians
};


/*
 * Сырые данные прямо с сенсоров.
 */
typedef struct RawData RawData;
struct RawData{
  // значения с внешнего АЦП
  uint16_t pressure_dynamic;
  uint16_t altitude_sonar;
  /* данные с магнитометра. Эти оси не обязаны совпадать с осями платы автопилота,
   * они содержат показания из регистров датчика в том порядке, в котором
   * вычитываются */
//  int16_t xmag;
//  int16_t ymag;
//  int16_t zmag;
  // положения сервоприводов (данные из регистров счетчика)
  uint16_t servo1;
  uint16_t servo2;
  uint16_t servo3;
  uint16_t servo4;
  uint16_t servo5;
  uint16_t servo6;
  uint16_t servo7;
  uint16_t servo8;
  // напряжение и ток бортовой сети
  uint16_t main_voltage;
  uint16_t main_current;
  uint16_t secondary_voltage; // напряга с вторичного источника питания для серв и приемника
  // температура c tmp75
  int16_t temp_tmp75;
  // температура с барометра bmp085 (десятые доли градуса)
  int16_t temp_bmp085;
  // давление c bmp085 (Па)
  uint32_t pressure_static;
  // GPS
  int32_t  gps_latitude;
  int32_t  gps_longitude;
  int32_t  gps_altitude;
  int32_t  gps_speed_knots;
  int32_t  gps_course;
  bool_t   gps_valid;
  uint8_t  gps_satellites;

  uint32_t odometer;
  uint32_t groundspeed;       /* земляная скорость (количество миллисекунд между импульсами)*/
  uint16_t engine_rpm;        /* Тахометр (rpm)*/

  uint32_t battery_consumed;  /* mAc sourced from battery since startup */
};


void SensorsInit(void);

#endif /* SENSORS_H_ */
