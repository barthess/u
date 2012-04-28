#ifndef MESSAGE_H_
#define MESSAGE_H_


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
  float     xgyrorate;
  float     ygyrorate;
  float     zgyrorate;
  /* ускорения по осям в mG */
  int16_t   xacc;
  int16_t   yacc;
  int16_t   zacc;

  /**/
  uint16_t  air_speed;      /* воздушная скорость. Фиксированная точка. (mm/s)*/
  int8_t    temp_onboard;   /* температура c tmp75. Целые градусы. */
  // напряжение и ток бортовой сети
  uint16_t main_voltage;      // mV
  uint32_t main_current;      // mA
  uint16_t secondary_voltage; // mV напряга с вторичного источника питания для серв и приемника
};


/*
 * Сырые данные прямо с сенсоров.
 */
typedef struct RawData RawData;
struct RawData{
  /* смещения нулей, посчитанные во время выставки.*/
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
  //магнитометр
  //  int16_t magnetic_x;
  //  int16_t magnetic_y;
  //  int16_t magnetic_z;
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
  uint32_t gps_time;
  uint8_t  gps_satellites;

  uint32_t rtc_sec;           /* время по внутренним часам. Секунды с начала эпохи */
  uint16_t rtc_msec;          /* дробная часть */

  uint16_t engine_rpm;        /* Тахометр (rpm)*/
};


/**
 * Структура для записи в бортовой самописец. Должна быть такого размера, чтобы
 * удобно влезала в сектор размером 128 байт.
 */
typedef struct LogItem LogItem;
struct LogItem{
  int32_t  gps_latitude;      /* широта, долгота */
  int32_t  gps_longitude;

  uint32_t gps_time;          /* время по GPS. В формате 115436 -- 11 часов, 54 минуты, 36 секунд */

  uint32_t rtc_sec;           /* время по внутренним часам. Секунды с начала эпохи */
  uint16_t rtc_msec;          /* дробная часть */

  uint16_t aileron;           /* положения сервоприводов и дросселя (данные из регистров счетчика) */
  uint16_t elevator;
  uint16_t throttle;
  uint16_t rudder;

  uint16_t altitude_sonar;    /* высота по сонару. Целое (cm)*/
  uint16_t main_current;      /* ток. милиамперы */

  uint16_t gyro_xI;           /* Углы поворота. Фиксированная точка -- полный поворот == 2^16*/
  uint16_t gyro_yI;
  uint16_t gyro_zI;

  int16_t acceleration_x;     /* Ускорения (mg)*/
  int16_t acceleration_y;
  int16_t acceleration_z;

  int16_t imu_x;              /* Рассчитанные проекции единичного вектора на оси * 10000 */
  int16_t imu_y;
  int16_t imu_z;

  int16_t baro_altitude;      /* высота по барометру bmp085. Целое (dm)*/
  int16_t gps_altitude;       /* высота по GPS. Целое (m)*/

  uint8_t main_voltage;       /* напряжение бортовой сети -- десятые доли вольта */
  uint8_t air_speed;          /* воздушная скорость. Фиксированная точка 5:3. (m/s)*/
  uint8_t engine_rpm;         /* частота вращения коленвала двигателя (Hz) */

  uint8_t gps_speed;          /* скорость по GPS. Целое (m/s)*/
  uint8_t gps_course;         /* Полный оборот -- 256 условных единиц. */
  uint8_t cpu_load;           /* загрузка CPU (%) */

  int8_t  temp_onboard;       /* температура c tmp75. Целые градусы. */
};


/**
 * структура определяет формат сообщений типа "письмо" для обмена данными.
 */
typedef struct Mail Mail;
struct Mail{
  /**
   * @brief указатель на внешний буфер.
   * @details После того, как данные забраны берущей
   * стороной, указатель устанавливается в NULL. Это будет сигналом для
   * дающей стороны.
   */
  void *payload;
  /**
   * Поле заполняется по усмотрению приложения, может содержать что угодно.
   */
  msg_t invoice;
  /**
   * Указатель на почтовый ящик, в который надо прислать подтверждение
   * успешного выполнения. Может использоваться для синхронизации отправляющего
   * потока. Аналогия обратного адреса на конверте письма.
   * Может быть NULL.
   */
  Mailbox *confirmbox;
};

#endif /* MESSAGE_H_ */

