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
  int16_t   baro_altitude;  /* высота по барометру bmp085. Целое (dm)*/
  uint16_t  air_speed;      /* воздушная скорость. Фиксированная точка. (mm/s)*/
  int8_t    temp_onboard;   /* температура c tmp75. Целые градусы. */
  // напряжение и ток бортовой сети
  uint16_t  main_voltage;      // mV
  uint32_t  main_current;      // mA
  uint16_t  secondary_voltage; // mV напряга с вторичного источника питания для серв и приемника

  float     groundspeed;        ///< Current ground speed in m/s
};


/*
 * Сырые данные прямо с сенсоров.
 */
typedef struct RawData RawData;
struct RawData{
  /* смещения нулей гироскопа, посчитанные во время выставки.*/
  int32_t xgyro_zero;
  int32_t ygyro_zero;
  int32_t zgyro_zero;
  /* данные с гироскопа. Эти оси не обязаны совпадать с осями платы автопилота,
   * они содержат показания из регистров датчика в том порядке, в котором
   * вычитываются */
  int16_t xgyro;
  int16_t ygyro;
  int16_t zgyro;
  int16_t gyro_temp;
  // значения с внешнего АЦП
  uint16_t pressure_dynamic;
  uint16_t altitude_sonar;
  /* данные с магнитометра. Эти оси не обязаны совпадать с осями платы автопилота,
   * они содержат показания из регистров датчика в том порядке, в котором
   * вычитываются */
  int16_t xmag;
  int16_t ymag;
  int16_t zmag;
  /* данные с акселерометра. Эти оси не обязаны совпадать с осями платы автопилота,
   * они содержат показания из регистров датчика в том порядке, в котором
   * вычитываются */
  int16_t xacc;
  int16_t yacc;
  int16_t zacc;
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
  // температура c tmp75 (сотые доли градуса)
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
  uint8_t  gps_satellites;

  uint32_t odometer;          /* количество импульсов с одометра */
  uint32_t groundspeed;       /* земляная скорость (количество миллисекунд между импульсами)*/
  uint16_t engine_rpm;        /* Тахометр (rpm)*/
};


void SensorsInit(void);

#endif /* SENSORS_H_ */
