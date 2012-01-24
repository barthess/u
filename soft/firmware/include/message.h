/*
 * message.h
 *
 *  Created on: 24.03.2011
 *      Author: barthess
 *
 *  Файл описывает всякие глобальные структуры данных
 */
#ifndef MESSAGE_H_
#define MESSAGE_H_

#define HEADER_LENGTH 2
#define LENGTH_LENGTH 1
#define CRC_LENGTH 1 // 1 байт
// масимальная длинна данных
#define FRAME_LENGTH (64 - LENGTH_LENGTH - HEADER_LENGTH - CRC_LENGTH)

// смещения служебных данных
#define HEADER_OFFSET 0
#define LENGTH_OFFSET (HEADER_OFFSET + HEADER_LENGTH)

#define FRAME_OFFSET (LENGTH_OFFSET + LENGTH_LENGTH)

// буфер под входящие данные
#define UART_BUF_DEPTH (FRAME_LENGTH + CRC_LENGTH + LENGTH_LENGTH + HEADER_LENGTH)


/*
 * Допустимые идентификаторы пакетов
 */
typedef enum {
  TEST           = 0, /* Тестовый пакет, может быть что угодно */
  MANUALDRIVING  = 1, /* Пакет с данными ручного управления */
  TELEMETRY      = 2, /* Телеметрия */
  RAWDATA        = 3, /* Структура данных для отладки */
  LOGITEM        = 4, /* Структура данных из тех, что пишется в EEPROM */
  ROUTEPOINT     = 5, /* Точка маршрута */
  CONTROL        = 6, /* Переключение режимов на лету */
  SETTINGS_SERVO = 7, /* Настройки серв */
  SETTINGS_OTHER = 8, /* Настройки остальной хрени */
  DATE           = 9, /* Установка времени */
} packet_id;


/**
 * Направление данных.
 * Применяется только в пакетах, входящих в кунээску.
 */
typedef enum {
  READ  = 0,
  WRITE = 1,
} packet_direction;


/*
 * Наверх.
 * Данные ручного управления с земли.
 */
typedef struct ManualDriving ManualDriving;
struct ManualDriving {
  uint8_t aileron;
  uint8_t elevator;
  uint8_t throttle;
  uint8_t rudder;

  // переключатели. Пока что просто пустышка.
//  bool_t self_annihilation;
};



/*
 * Вниз. 
 * Сырые данные прямо с сенсоров (для дебага).
 */
typedef struct RawData RawData;
struct RawData{
  /* Углы поворота с момента включения устройства. Фиксированная точка -- полный поворот == 2^32 */
  uint32_t gyro_xI;
  uint32_t gyro_yI;
  uint32_t gyro_zI;
  // шаги поворота, посчитанные через интеграл
  int32_t gyro_x_delta;
  int32_t gyro_y_delta;
  int32_t gyro_z_delta;
  /* смещения нулей, посчитанные во время выставки.*/
  uint32_t gyro_xAvg;
  uint32_t gyro_yAvg;
  uint32_t gyro_zAvg;
  // данные с гироскопа
  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;
  int16_t gyro_temp;
  // значения с внешнего АЦП
  uint16_t pressure_dynamic;
  uint16_t altitude_sonar;
  //магнитомерт
  int16_t magnetic_x;
  int16_t magnetic_y;
  int16_t magnetic_z;
  // акселерометр
  int16_t acceleration_x;
  int16_t acceleration_y;
  int16_t acceleration_z;
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
 * Двунаправленный. 
 * Точка маршрута. Одна точка на сообщение.  При запросе точки необходимо
 * прислать ее номер. Остальные поля тоже должны быть, но их содержимое будет
 * проигнорировано. Рекомендуется установить их содержимое в ноль.
 */
typedef struct RoutePoint RoutePoint;
struct RoutePoint{
  // широта, долгота, высота (TODO: над уровнем хуй знает чего, надо уточнять)
  int32_t latitude; // in units of 10^(-5) degrees
  int32_t longitude;// in units of 10^(-5) degrees
  int16_t altitude; // метры

  // скорость.
  uint8_t speed; //TODO: относительно воздуха или земли. Уточнить
  // номер точки.
  uint8_t number;
  // контрольная сумма точки
  uint8_t crc;
};


/*
 * Наверх. 
 * Пакеты для переключения режимов ПОНИЭС (автопилот\ручное, автоматическая
 * выдача данных\по запросу и т.д. и т.п.)
 */
typedef struct Control Control;
struct Control{
  // переключатель на ручное управление
  bool_t manual_driving;
  // автоматическое присылание телеметрии
  bool_t telemetry_auto_send;
  // автоматический подбор скорости для минимального энергопотребления
  // при этом скорости, заданные в RoutePoint игнорируются
  bool_t power_saving;
};

/**
 * структура определяет формат сообщений для менеджера xbee.
 */
typedef struct XbeeMsg XbeeMsg;
struct XbeeMsg{
  /**
   * Указатель на почтовый ящик, в который надо прислать подтверждение
   * успешного выполнения. Аналогия обратного адреса на конверте письма.
   * Может быть NULL
   */
  Mailbox *mailbox;
  /**
   * @brief указатель на внешний буфер.
   * @details После того, как данные забраны берущей
   * стороной, указатель устанавливается в NULL. Это будет сигналом для
   * дающей стороны.
   */
  uint8_t *bufp;
  /**
   * сколько байт транзакция
   * @details старший байт является признаком R/W
   *          0 - write
   *          1 - read
   *          точно так же, как и для I2C
   */
  uint16_t  len;
  /**
   * Идентификатор пакета.
   */
  packet_id id;
};



/**
 * структура определяет формат сообщений для менеджера еепром.
 * Может быть как запросом записи, так и чтения
 */
typedef struct EepromReq EepromReq;
struct EepromReq{
  /**
   * Указатель на почтовый ящик, в который надо прислать подтверждение
   * успешного выполнения. Аналогия обратного адреса на конверте письма.
   * Может быть NULL
   */
  Mailbox *mailbox;
  /**
   * @brief указатель на внешний буфер.
   * @details После того, как данные забраны берущей
   * стороной, указатель устанавливается в NULL. Это будет сигналом для
   * дающей стороны.
   */
  uint8_t *bufp;
  /**
   * сколько байт транзакция
   * @details старший байт является признаком R/W
   *          0 - write
   *          1 - read
   *          точно так же, как и для I2C
   */
  uint16_t  len;
  /**
   * Адрес в еепром. По нему будет произведена запись
   */
  uint16_t addr;
};



#endif /* MESSAGE_H_ */

