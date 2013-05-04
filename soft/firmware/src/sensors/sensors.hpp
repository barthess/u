#ifndef SENSORS_H_
#define SENSORS_H_

/* immobility masks detected by different sensors */
#define STILL_GYRO_MSK    1
#define STILL_MAG_MSK     2
#define STILL_ACC_MSK     4

/*
 *
 */
typedef struct CompensatedData CompensatedData;
struct CompensatedData{
  /* Integrated angles for debug. Degrease */
  float     gyro_angle[3];
  float     gyrotemp;
  /* acceleration in mG (for sending in mavlink messages) */
  int16_t   acc_i16[3];
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
  int16_t main_voltage;
  int16_t main_current;
  int16_t secondary_voltage; // напряга с вторичного источника питания для серв и приемника
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


/**
 * @brief   System attitude calculated by IMU and GPS
 */
typedef struct {
  float     gamma;    // roll (rad)
  float     theta;    // pitch (rad)
  float     psi;      // heading (rad)
  float     lat;      // lattitude from GNSS (WGS-84, rad)
  float     lon;      // longitude from GNSS (WGS-84, rad)
  float     hmsl;     // altitude from GNSS (WGS-84, m)
  float     xn;       // X coordinate, North (m)
  float     hup;      // H coordinate, Up (m)
  float     ye;       // Y coordinate, East (m)
  float     vgps;     // speed from GPS (m/s)
  float     vodo;     // speed from odometer (m/s)
}StateVector;


/**
 * @brief   Output data from ACS
 */
typedef struct {
  float     angle0;   // (rad)
  float     angle1;   // (rad)
  float     angle2;   // (rad)
  uint8_t   thrust;   // (percents)
}Impact;


void SensorsInit(void);

#endif /* SENSORS_H_ */
