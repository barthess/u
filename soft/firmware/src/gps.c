#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "message.h"
#include "gps.h"
#include "../main.h"

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


// указатель на последовательный драйвер, через который подключен gps
#define GPSSD SD1


extern RawData raw_data;
extern LogItem log_item;


// буфера под принятые сообщения
static uint8_t ggabuf[GPS_MSG_LEN];
static uint8_t rmcbuf[GPS_MSG_LEN];

// заготовки контрльных сумм
static uint8_t ggachecksum = 'G' ^ 'P' ^ 'G' ^ 'G' ^ 'A';
static uint8_t rmcchecksum = 'G' ^ 'P' ^ 'R' ^ 'M' ^ 'C';

// для широты и долготы выбран знаковый формат чтобы не таскать N, S, W, E
int32_t gps_latitude = 0,     gps_longitude = 0,   gps_altitude = 0;
int32_t gps_altitude_sep = 0, gps_speed_knots = 0, gps_course = 0;

uint32_t gps_time;

static WORKING_AREA(gpsRxThreadWA, 256);
//Thread *gps_rx_tp = NULL;
__attribute__((noreturn))
static msg_t gpsRxThread(void *arg){
  chRegSetThreadName("gpsRx");
  (void)arg;
  uint32_t n = 0;

  while (TRUE) {

EMPTY:
		n = 0;
		while(sdGet(&GPSSD) != '$')
			; // читаем из буфера до тех пор, пока не найдем знак бакса
		goto TALKER;

TALKER:
		n = sdGet(&GPSSD) << 8;
		n = n + sdGet(&GPSSD);
		if (n != GP_TALKER)
			goto EMPTY;
		else
			goto SENTENCE;

SENTENCE: // определим тип сообщения
		n = sdGet(&GPSSD) << 16;
		n = n + (sdGet(&GPSSD) << 8);
		n = n + sdGet(&GPSSD);
		if (n == GGA_SENTENCE)
			goto GGA;
		if (n == RMC_SENTENCE)
			goto RMC;
		else
			goto EMPTY;

GGA:
		if (get_gps_sentence(ggabuf, ggachecksum) == 0)
			parse_gga(ggabuf);
		goto EMPTY;

RMC:
		if (get_gps_sentence(rmcbuf, rmcchecksum) == 0)
			parse_rmc(rmcbuf);
		goto EMPTY;
  }
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


/*
$GPGGA,115436.000,5354.713670,N,02725.690517,E,1,5,2.01,266.711,M,26.294,M,,*5D
$GPGGA,000103.037,,,,,0,0,,,M,,M,,*4E

$GPRMC,115436.000,A,5354.713670,N,02725.690517,E,0.20,210.43,010611,,,A*66
$GPRMC,115436.000,,,,,,0.20,210.43,010611,,,A*66
$GPRMC,115436.000,,,,,,,,,,,A*66
*/
void parse_gga(uint8_t *ggabuf){
  uint8_t i = 1; /* начинается с 1, потому что нулевым символом является рудиментарная запятая */
  uint8_t fix = 0, gps_satellites = 0;

  gps_time = parse_decimal(&ggabuf[i]);         /* time */
  while(ggabuf[i] != ','){i++;}
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

  gps_satellites = parse_decimal(&ggabuf[i]);   /* number of satellites */
  while(ggabuf[i] != ','){i++;}
    i++;

  while(ggabuf[i] != ','){i++;}                 /* diltusion */
    i++;

  gps_altitude = parse_decimal(&ggabuf[i]);     /* altitude */
  while(ggabuf[i] != ','){i++;}
    i++;

  while(ggabuf[i] != ','){i++;}                 /* units of altitude */
    i++;

  gps_altitude_sep = parse_decimal(&ggabuf[i]); /* geoidal separation */
  while(ggabuf[i] != ','){i++;}
    i++;

	if (fix > 0){  /* если есть достоверные координаты */
	  raw_data.gps_time      = gps_time;
		raw_data.gps_latitude  = gps_latitude;
		raw_data.gps_longitude = gps_longitude;
	  raw_data.gps_altitude  = gps_altitude;
	  raw_data.gps_satellites = gps_satellites;

	  log_item.gps_time      = gps_time / 100; /* откинем доли секунды */
	  log_item.gps_latitude  = gps_latitude;
	  log_item.gps_longitude = gps_longitude;
	  log_item.gps_altitude  = (int16_t)gps_altitude / 100; /* откинем доли метров */
	}
	else{
	  raw_data.gps_time = 0;
		raw_data.gps_latitude = 0;
		raw_data.gps_longitude = 0;
		raw_data.gps_altitude = 0;
		raw_data.gps_satellites = 0;

    log_item.gps_time = 0;
    log_item.gps_latitude = 0;
    log_item.gps_longitude = 0;
    log_item.gps_altitude = 0;
	}
}



void parse_rmc(uint8_t *rmcbuf){
  uint8_t i = 1;  /* начинается с 1, потому что нулевым символом является рудиментарная запятая */
  uint8_t valid = 'V';

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

  if (valid == 'A'){                              /* если координаты достоверны */
  	raw_data.gps_course      = gps_course;
  	raw_data.gps_speed_knots = gps_speed_knots;

  	log_item.gps_course = (uint8_t)((gps_course * 256) / 36000);
  	log_item.gps_speed  = (uint8_t)((gps_speed_knots * 514) / 100000);
  }
  else{
  	raw_data.gps_course = 0;
  	raw_data.gps_speed_knots = 0;

    log_item.gps_course = 0;
    log_item.gps_speed = 0;
  }
}


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



uint32_t gpsatol(const uint8_t *str)
{
  uint32_t ret = 0;
  while (gpsisdigit(*str))
    ret = 10 * ret + *str++ - '0';
  return ret;
}

bool_t gpsisdigit(char c){
  return c >= '0' && c <= '9';
}



static SerialConfig gps_ser_cfg = {
    GPS_DEFAULT_BAUDRATE,
    0,
    0,
    0,
};



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
          NORMALPRIO - 2,
          gpsRxThread,
          NULL);
}

