#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "ch.h"
#include "hal.h"
#include "sensors.h"
#include "message.h"
#include "gps.h"
#include "bkp.h"
#include "main.h"
#include "link.h"
#include "exti_local.h"

/**
 * Широта  — это угол между отвесной линией в данной точке и плоскостью экватора,
отсчитываемый от 0 до 90° в обе стороны от экватора. Географическую широту
точек, лежащих в северном полушарии, (северная широта) принято считать
положительной, широту точек в южном полушарии — отрицательной.
 * Долгота — угол между плоскостью меридиана, проходящего через данную точку,
и плоскостью начального нулевого меридиана, от которого ведётся отсчёт долготы.
Долготы от 0° до 180° к востоку от нулевого меридиана называют восточными,
к западу — западными. Восточные долготы принято считать положительными,
западные — отрицательными.
*/

/**
A sentence may contain up to 80 characters plus "$" and CR/LF.
If data for a field is not available, the
field is omitted, but the delimiting commas are still sent,
with no space between them. The checksum
field consists of a "*" and two hex digits representing the exclusive
OR of all characters between, but not
including, the "$" and "*".
*/

/**
 * Integral values
 * Values returned by the core TinyGPS methods are integral. Angular
 * latitude and longitude measurements, for example, are provided in units
 * of 10^(-5) degrees, so instead of 90°30'00", get_position() returns a
 * longitude value of 9050000, or 90.5 degrees.
 *
 * Высота по алгоритму получается в сантиметрах
 */

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
extern RawData raw_data;
extern Mailbox tolink_mb;
extern mavlink_global_position_int_t mavlink_global_position_int_struct;
extern struct tm gps_timp;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static SerialConfig gps_ser_cfg = {
    GPS_DEFAULT_BAUDRATE,
    0,
    0,
    0,
};

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */
static void parse_rmc(uint8_t *rmcbuf, mavlink_global_position_int_t *global_pos_struct);
static void parse_gga(uint8_t *ggabuf, mavlink_global_position_int_t *global_pos_struct);
static void get_time(struct tm *timp, uint8_t *buft, uint8_t *bufd);
static int32_t parse_decimal(uint8_t *p);
static int32_t parse_degrees(uint8_t *p);
static uint32_t gpsatol(const uint8_t *str);
static bool_t gpsisdigit(char c);
static uint8_t get_gps_sentence(uint8_t *buf, uint8_t checksum);
static uint8_t from_hex(uint8_t a);

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
static WORKING_AREA(gpsRxThreadWA, 512);
static msg_t gpsRxThread(void *arg){
  chRegSetThreadName("gpsRx");
  (void)arg;
  uint32_t tmp = 0;
  uint32_t n = 0;

  // буфера под принятые сообщения
  static uint8_t ggabuf[GPS_MSG_LEN];
  static uint8_t rmcbuf[GPS_MSG_LEN];
  // заготовки контрольных сумм
  static uint8_t ggachecksum = 'G' ^ 'P' ^ 'G' ^ 'G' ^ 'A';
  static uint8_t rmcchecksum = 'G' ^ 'P' ^ 'R' ^ 'M' ^ 'C';
  /* сообщение для менеджера связи */
  Mail gps_mail;
  gps_mail.payload = NULL;
  gps_mail.invoice = MAVLINK_MSG_ID_GLOBAL_POSITION_INT;
  gps_mail.confirmbox = NULL;

  mavlink_global_position_int_struct.time_boot_ms = 0;
  mavlink_global_position_int_struct.lat = 0;
  mavlink_global_position_int_struct.lon = 0;
  mavlink_global_position_int_struct.alt = 0;
  mavlink_global_position_int_struct.relative_alt = 0;
  mavlink_global_position_int_struct.vx = 0;
  mavlink_global_position_int_struct.vy = 0;
  mavlink_global_position_int_struct.vz = 0;
  mavlink_global_position_int_struct.hdg = 65535;

  /* отправим последние достоверные кординаты */
  mavlink_global_position_int_struct.lat = bkpLoadGpsLatitude();
  mavlink_global_position_int_struct.lon = bkpLoadGpsLongitude();
  mavlink_global_position_int_struct.alt = bkpLoadGpsAltitude();

  while (TRUE) {

EMPTY:

    if ((n >= 2) && (gps_mail.payload == NULL)){
      mavlink_global_position_int_struct.time_boot_ms = TIME_BOOT_MS;
      gps_mail.payload = &mavlink_global_position_int_struct;
      chMBPost(&tolink_mb, (msg_t)&gps_mail, TIME_IMMEDIATE);
      n = 0;
    }

		tmp = 0;
		while(sdGet(&GPSSD) != '$')
			; // читаем из буфера до тех пор, пока не найдем знак бакса

		tmp = sdGet(&GPSSD) << 8;
		tmp = tmp + sdGet(&GPSSD);
		if (tmp != GP_TALKER)
			goto EMPTY;

		// определим тип сообщения
		tmp = sdGet(&GPSSD) << 16;
		tmp = tmp + (sdGet(&GPSSD) << 8);
		tmp = tmp + sdGet(&GPSSD);
		if (tmp == GGA_SENTENCE){
	    if (get_gps_sentence(ggabuf, ggachecksum) == 0){
	      parse_gga(ggabuf, &mavlink_global_position_int_struct);
	      n++;
	    }
	    goto EMPTY;
		}
		if (tmp == RMC_SENTENCE){
	    if (get_gps_sentence(rmcbuf, rmcchecksum) == 0){
	      parse_rmc(rmcbuf, &mavlink_global_position_int_struct);
	      n++;
	    }
	    goto EMPTY;
		}
		else
			goto EMPTY;
  }
  return 0;
}

/*
$GPGGA,115436.000,5354.713670,N,02725.690517,E,1,5,2.01,266.711,M,26.294,M,,*5D
$GPGGA,000103.037,,,,,0,0,,,M,,M,,*4E

$GPRMC,115436.000,A,5354.713670,N,02725.690517,E,0.20,210.43,010611,,,A*66
$GPRMC,115436.000,,,,,,0.20,210.43,010611,,,A*66
$GPRMC,115436.000,,,,,,,,,,,A*66
*/
void parse_gga(uint8_t *ggabuf, mavlink_global_position_int_t *global_pos_struct){
  // для широты и долготы выбран знаковый формат чтобы не таскать N, S, W, E
  int32_t  gps_latitude = 0;
  int32_t  gps_longitude = 0;
  int32_t  gps_altitude = 0;

  uint8_t i = 1; /* начинается с 1, потому что нулевым символом является рудиментарная запятая */
  uint8_t fix = 0, satellites_visible = 0;

  while(ggabuf[i] != ','){i++;}                 /* time */
  i++;

  gps_latitude = parse_degrees(&ggabuf[i]);     /* latitude */
  while(ggabuf[i] != ','){i++;}
    i++;

  if (ggabuf[i] == 'S')                         /* latitude letter */
    gps_latitude = -abs(gps_latitude);
  while(ggabuf[i] != ','){i++;}
    i++;

  gps_longitude = parse_degrees(&ggabuf[i]);    /* longitude */
  while(ggabuf[i] != ','){i++;}
    i++;

	if (ggabuf[i] == 'W')
	  gps_longitude = -abs(gps_longitude);        /* longitude letter parse */
  while(ggabuf[i] != ','){i++;}
    i++;

  fix = ggabuf[i] - '0';                        /* gps quallity */
  while(ggabuf[i] != ','){i++;}
    i++;

  satellites_visible = gpsatol(&ggabuf[i]);     /* number of satellites */
  while(ggabuf[i] != ','){i++;}
    i++;

  while(ggabuf[i] != ','){i++;}                 /* diltusion */
    i++;

  gps_altitude = parse_decimal(&ggabuf[i]);     /* altitude */
  while(ggabuf[i] != ','){i++;}
    i++;

  while(ggabuf[i] != ','){i++;}                 /* units of altitude */
    i++;

  while(ggabuf[i] != ','){i++;}                 /* geoidal separation */
    i++;

	if (fix > 0){  /* если есть достоверные координаты */
      raw_data.gps_latitude  = gps_latitude;
      raw_data.gps_longitude = gps_longitude;
      raw_data.gps_altitude  = gps_altitude;
      raw_data.gps_satellites = satellites_visible;

      global_pos_struct->lat = gps_latitude * 100;
      global_pos_struct->lon = gps_longitude * 100;
      global_pos_struct->alt = gps_altitude * 10;

      /* сохраним координаты на будущее */
      bkpSaveGpsLatitude(global_pos_struct->lat);
      bkpSaveGpsLongitude(global_pos_struct->lon);
      bkpSaveGpsAltitude(global_pos_struct->alt);
	}
	else{
		raw_data.gps_latitude = 0;
		raw_data.gps_longitude = 0;
		raw_data.gps_altitude = 0;
		raw_data.gps_satellites = 0;

		/* отправим последние достоверные кординаты */
    global_pos_struct->lat = bkpLoadGpsLatitude();
    global_pos_struct->lon = bkpLoadGpsLongitude();
    global_pos_struct->alt = bkpLoadGpsAltitude();
	}
}

void parse_rmc(uint8_t *rmcbuf, mavlink_global_position_int_t *global_pos_struct){
  int32_t  gps_speed_knots = 0;
  int32_t  gps_course = 0;

  uint8_t *buft, *bufd;
  uint8_t i = 1;  /* начинается с 1, потому что нулевым символом является рудиментарная запятая */
  uint8_t valid = 'V';

  buft = &(rmcbuf[i]);
  while(rmcbuf[i] != ','){i++;}                   /* Time (UTC) */
    i++;

  valid = rmcbuf[i];                              /* Status, V = Navigation receiver warning */
  while(rmcbuf[i] != ','){i++;}
    i++;

  while(rmcbuf[i] != ','){i++;}                   /* Latitude */
    i++;

  while(rmcbuf[i] != ','){i++;}                   /* N or S */
    i++;

  while(rmcbuf[i] != ','){i++;}                   /* Longitude */
    i++;

  while(rmcbuf[i] != ','){i++;}                   /* E or W */
    i++;

  gps_speed_knots = parse_decimal(&rmcbuf[i]);    /*Speed over ground, knots */
  while(rmcbuf[i] != ','){i++;}
    i++;

  gps_course = parse_decimal(&rmcbuf[i]);         /*Course Over Ground */
  while(rmcbuf[i] != ','){i++;}
    i++;

  bufd = &(rmcbuf[i]);
  while(rmcbuf[i] != ','){i++;}                   /* Date (UTC) */
    i++;

  if (valid == 'A'){                              /* если координаты достоверны */
  	raw_data.gps_course      = gps_course;
  	raw_data.gps_speed_knots = gps_speed_knots;

    global_pos_struct->hdg = 65535;
    //global_pos_struct->vel = gps_speed_knots * 51; /* GPS ground speed (m/s * 100) */
    get_time(&gps_timp, buft, bufd);
  }
  else{
  	raw_data.gps_course = 0;
  	raw_data.gps_speed_knots = 0;

    global_pos_struct->hdg = 65535;
  }
}

/**
 * Выковыривает дату и время из RMC
 *
 * timp - указатель на структуру с временем
 * buft - указатель на строку с временем
 * bufd - указатель на строку с датой
 *
int tm_sec       seconds after minute [0-61] (61 allows for 2 leap-seconds)
int tm_min       minutes after hour [0-59]
int tm_hour      hours after midnight [0-23]
int tm_mday      day of the month [1-31]
int tm_mon       month of year [0-11]
int tm_year      current year-1900
int tm_wday      days since Sunday [0-6]
int tm_yday      days since January 1st [0-365]
int tm_isdst     daylight savings indicator (1 = yes, 0 = no, -1 = unknown)
 */

void get_time(struct tm *timp, uint8_t *buft, uint8_t *bufd){
  timp->tm_hour = 10 * (buft[0] - '0') + (buft[1] - '0');
  timp->tm_min  = 10 * (buft[2] - '0') + (buft[3] - '0');
  timp->tm_sec  = 10 * (buft[4] - '0') + (buft[5] - '0');

  timp->tm_mday = 10 * (bufd[0] - '0') + (bufd[1] - '0');
  timp->tm_mon  = 10 * (bufd[2] - '0') + (bufd[3] - '0') - 1;
  timp->tm_year = 10 * (bufd[4] - '0') + (bufd[5] - '0') + 2000 - 1900;
}

uint8_t get_gps_sentence(uint8_t *buf, uint8_t checksum){
  uint8_t byte = 0, i = 0;

  while TRUE{
    i++;
    if (i >= GPS_MSG_LEN)   /* если данных больше, чем поместится в буфер длинной len */
      return 1;
    byte = sdGet(&GPSSD);
    if (byte == '*')        /* как только натыкаемся на * - выходим из цикла */
      break;
    checksum ^= byte;
    *buf++ = byte;
  }
  checksum ^= from_hex(sdGet(&GPSSD)) * 16; /* читаем 2 байта контрольной суммы */
  checksum ^= from_hex(sdGet(&GPSSD));

  if(checksum == 0)    /* сошлась */
    return 0;
  else
    return 2;
}

uint8_t from_hex(uint8_t a){
  if (a >= 'A' && a <= 'F')
    return a - 'A' + 10;
  else if (a >= 'a' && a <= 'f')
    return a - 'a' + 10;
  else
    return a - '0';
}

/**
 * Возвращает значение с фиксированной точкой с точностью 2 знака после запятой
 */
int32_t parse_decimal(uint8_t *p){
  bool_t isneg = (*p == '-'); /* обработаем наличие знака "-" */
  if (isneg) ++p;
  uint32_t ret = gpsatol(p);  /* сделаем заготовку для возвращаемого значения */
  ret = ret * 100UL;          /* сделаем место для 2 знаков после запятой */

  while (gpsisdigit(*p)) ++p; /* пропустим все знаки до запятой - мы их уже обработали */
  if (*p == '.'){             /* запишем 2 знака после запятой */
    if (gpsisdigit(p[1])){
      ret += 10 * (p[1] - '0');
      if (gpsisdigit(p[2]))
        ret += p[2] - '0';
    }
  }
  return isneg ? -ret : ret;
}

int32_t parse_degrees(uint8_t *p){
  uint32_t left = gpsatol(p);                       /* читаем первую часть (ddmm) */
  uint32_t tenk_minutes = (left % 100UL) * 10000UL; /* отделяем целые части минут */

  while (gpsisdigit(*p)) ++p;
  if (*p == '.'){
    uint32_t mult = 1000; /* только 3 знака после запятой */
    while (gpsisdigit(*++p)){
      tenk_minutes += mult * (*p - '0');
      mult /= 10;
    }
  }
  return (left / 100) * 100000 + tenk_minutes / 6;
}

uint32_t gpsatol(const uint8_t *str){
  uint32_t ret = 0;
  while (gpsisdigit(*str))
    ret = 10 * ret + *str++ - '0';
  return ret;
}

bool_t gpsisdigit(char c){
  return c >= '0' && c <= '9';
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */
void GPSInit(void){
  /* запуск на дефолтной частоте */
  gps_ser_cfg.sc_speed = GPS_DEFAULT_BAUDRATE;
  sdStart(&GPSSD, &gps_ser_cfg);

  /* смена скорости ПРИЁМНИКА на повышенную */
  //  sdWrite(&SDGPS, GPS_HI_BAUDRATE_STR, GPS_HI_BAUDRATE_STR_LEN);
  //  chThdSleepMilliseconds(byte2msec(GPS_HI_BAUDRATE_STR_LEN, GPS_DEFAULT_BAUDRATE));

  /* перезапуск порта контроллера на повышенной частоте */
  //  sdStop(&SDGPS);
  //  gps_ser_cfg.sc_speed = GPS_HI_BAUDRATE;
  //  sdStart(&SDGPS, &gps_ser_cfg);

  /* установка выдачи только GGA и RMC */
  sdWrite(&GPSSD, GPS_MSG_STR, GPS_MSG_STR_LEN);
  chThdSleepMilliseconds(byte2msec(GPS_MSG_STR_LEN, GPS_DEFAULT_BAUDRATE));

  /* установка частоты обновления 5 Гц */
  sdWrite(&GPSSD, GPS_FIX_PERIOD_STR, GPS_FIX_PERIOD_STR_LEN);
  chThdSleepMilliseconds(byte2msec(GPS_FIX_PERIOD_STR_LEN, GPS_DEFAULT_BAUDRATE));

  /* зачистка входной очереди после всех манипуляций. На всякий случай */
  chSysLock();
  chIQResetI( &(GPSSD.iqueue));
  chSysUnlock();

  chThdCreateStatic(gpsRxThreadWA,
          sizeof(gpsRxThreadWA),
          GPS_THREAD_PRIO,
          gpsRxThread,
          NULL);

  /* clear time structure */
  gps_timp.tm_isdst = -1;
  gps_timp.tm_wday  = 0;
  gps_timp.tm_mday  = 0;
  gps_timp.tm_yday  = 0;
  gps_timp.tm_mon   = 0;
  gps_timp.tm_year  = 0;
  gps_timp.tm_sec   = 0;
  gps_timp.tm_min   = 0;
  gps_timp.tm_hour  = 0;

  /* enable interrupts from PPS pin */
  ExtiEnablePps();
}

