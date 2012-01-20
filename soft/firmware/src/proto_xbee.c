/*
 * proto_xbee.c
 *
 *  Created on: 09.05.2011
 *      Author: barthess
 */

#include "proto_xbee.h"
#include "checksum.h"


//-----------------------------------------------------------------------------
// константы и флаги
//-----------------------------------------------------------------------------
#define USE_ACK FALSE // использовать подтверждения средствами модемов?


/* адрес назначения в виде массива байтов. Одно значение на 64 бита компилятор
 * переваривает плохо*/
static const uint8_t dest64[8] = {0x00,0x13,0xA2,0x00,0x40,0x5D,0xF9,0xEA}; //GND
static const uint8_t self64[8] = {0x00,0x13,0xA2,0x00,0x40,0x5D,0xF9,0xE9}; //PNS


//-----------------------------------------------------------------------------
// функции
//-----------------------------------------------------------------------------

/**
 *  заворачивает данные в пакет для отправки через радиоканал
 * [in] *opacket указатель на буфер, в который надо сложить готовый пакет
 * [in] *buf указатель на структуру, которую надо отправить
 * [in] len размер структуры, которую надо послать
 * [in] id идентификатор пакета
 * [in] ack (xbee specific) идентификатор, на который принимающая сторона
 *      присылает подтверждение, если равен нулю - подтверждение не присылается
 * [out] количество байт, которые надо пропихнуть в UART за один сеанс
 */

size_t xbee_wrap(uint8_t *opacket, uint8_t *buf, size_t len, uint8_t id, uint8_t ack){
	// временный буфер под исходящий НЕзаэскейпанный пакет
	uint8_t raw_opacket[API_PACKET_LEN];
	uint8_t checksum_pos = 0;

	chDbgCheck((buf != NULL) && (opacket != NULL) && (len <= RF_DATA_LEN),
             "xbee_wrap");

  // заполняем служебные поля
	fill_header(raw_opacket, len, ack);

  // служебные данные записаны, пишем информацию
  cpbuf(&raw_opacket[TX_RF_DATA_OFFSET + 1], buf, len);
  raw_opacket[TX_RF_DATA_OFFSET] = id;

  // новая длина для нужд расчета котрольной суммы
  len = raw_opacket[LEN_OFFSET + 1] + (raw_opacket[LEN_OFFSET] << 8);
  // позиция контрольной суммы в пакете
  checksum_pos = LEN_OFFSET + LEN_LEN + len;
  // запишем контрольную сумму
  raw_opacket[checksum_pos] = checksum_xbee(&raw_opacket[LEN_OFFSET + LEN_LEN], len);

  // проводоим эскейпизацию
  return(escape_packet(raw_opacket, opacket));
}



/**
 * Выковыривает данные из пакета, вылезшего из модема
 * [in] *clean_ipacket указатель на буфер, в который надо сложить обработанный пакет
 * [in] *ipacket указатель на буфер, в который сложены байты из модема
 * [in] len количество данных
 * [out] указатель на начало полезной нагрузке в clean_ipacket
 */
uint8_t* xbee_extract(uint8_t *clean_ipacket, uint8_t *ipacket, size_t len){
  len = unescape_packet(clean_ipacket, ipacket, len);                         // уберем эскейпы и обновим длинну
  /* а теперь будем долго и нудно проверять */

  if (ipacket[0] != 0x7E){                                                    // проверка заголовка
  	return NULL;
  }

  len = len - DELIM_LEN - LEN_LEN - XBEE_CHECKSUM_LEN;                        // проверка длины
  size_t api_len = 0;
  api_len = clean_ipacket[LEN_OFFSET + 1] + (clean_ipacket[LEN_OFFSET] << 8);
  if (len != api_len){
  	return NULL;
  }

  if (checksum_xbee(                                                          // проверка контрольной суммы
      &clean_ipacket[LEN_OFFSET + LEN_LEN], api_len + XBEE_CHECKSUM_LEN) != 0){
  	return NULL;
  }

  // косяков не выявлено
	switch(clean_ipacket[API_ID_OFFSET]){
	case API_RX_PACK:
		return &(clean_ipacket[RX_RF_DATA_OFFSET]);
	case API_TX_STATUS:
		return NULL;
	default:
		return NULL;
		// TODO: более грамотный обработчик
	}
}


/* Заполняет служебные поля */
void fill_header(uint8_t *buf, size_t len, uint8_t ack){
  uint8_t i = 0;

  chDbgCheck((len + 1 < RF_DATA_LEN), "Too much data");
  if (len + 1 > RF_DATA_LEN)
    len = RF_DATA_LEN - 1;

  // TODO: заполнение заголовка кэшировать где-нибудь
  // разделитель
  buf[DELIM_OFFSET] = DELIM;
  // длина
  buf[LEN_OFFSET] = 0; // старший байт всегда получается равен 0
  /* служебные байты + (длина + ID) - заголовок - длина длины - длина контрольной суммы*/
  buf[LEN_OFFSET + 1] = CONTROL_LEN + (len + 1) - DELIM_LEN - LEN_LEN - XBEE_CHECKSUM_LEN;
  // это запрос передачи
  buf[API_ID_OFFSET] = API_TX_REQ;
  // нужно ли подтверждение о доставке
  buf[API_ACK_OFFSET] = ack;
  // записываем адреса
  i = 8;
  while (i--){
    buf[DEST64_ADDR_OFFSET + i] = dest64[i];
  }
  buf[DEST16_ADDR_OFFSET] = 0xFF;
  buf[DEST16_ADDR_OFFSET + 1] = 0xFE;
  buf[BCAST_RADIUS_OFFSET] = 1;
  buf[OPTIONS_OFFSET] = 0;
}

/*
 * Копирует переданную структуру во временный буфер
 */
inline void cpbuf(uint8_t *out, uint8_t *in, size_t len){
  // кастанём указатель на переданную структуру в uint8_t*
  uint8_t *casted_in = in;
  while(len--){
    out[len] = casted_in[len];
  }
}


/*
 * заменяет все контрольные символы esc-последовательностями
 * эскейпать положено всё, кроме заголовка
 * [in] *raw_buf указатель на исходный пакет с контрольной суммой
 * [in] *packet указатель на буфер под заэскейпанный пакет
 * [out] количество байт на весь пакет
 */
size_t escape_packet(uint8_t *raw_buf, uint8_t *packet){
  uint8_t len = 0;
  uint8_t i = 0; // индекс для обработанного массива
  uint8_t j = 0; // индекс для входного массива
  // длинна без учета заголовка
  len = DELIM_LEN + raw_buf[LEN_OFFSET + 1] + (raw_buf[LEN_OFFSET] << 8) + LEN_LEN + XBEE_CHECKSUM_LEN;

  // начинаем заполнять выходной массив
  packet[0] = raw_buf[0]; // заголовок без изменений
  j = 1;
  i = 1;

  for (j=1; j<len; j++){
    switch(raw_buf[j]){
    case 0x11:
      packet[i] = 0x7D;
      packet[i+1] = 0x11 ^ 0x20;
      i += 2;
      break;
    case 0x13:
      packet[i] = 0x7D;
      packet[i+1] = 0x13 ^ 0x20;
      i += 2;
      break;
    case 0x7D:
      packet[i] = 0x7D;
      packet[i+1] = 0x7D ^ 0x20;
      i += 2;
      break;
    case 0x7E:
      packet[i] = 0x7D;
      packet[i+1] = 0x7E ^ 0x20;
      i += 2;
      break;
    default:
      packet[i] = raw_buf[j];
      i++;
      break;
    }
  }
  return i; // новая длинна, с учетом заголовка
}


/*
 * заменяет все esc-последовательности символами
 * эскейпать положено всё, кроме заголовка
 * [in] *raw_buf указатель на исходный пакет с контрольной суммой
 * [in] *ipacket указатель на буфер под заэскейпанный пакет
 * [out] количество байт на весь пакет
 */
size_t unescape_packet(uint8_t *raw_buf, uint8_t *ipacket, size_t len){
  uint8_t i = 1; // индекс для обработанного массива
  uint8_t j = 1; // индекс для входного массива

  raw_buf[0] = ipacket[0]; // заголовок без изменений

  for (j=1; j<len; j++){
    if (ipacket[j] == 0x7D){
      raw_buf[i] = ipacket[j + 1] ^ 0x20;
      i++;
      j++; // увеличим, т.к. приняты 2 байта
    }
    else{
      raw_buf[i] = ipacket[j];
      i++;
    }
  }
  // вернем количество байт после удаления эскейпов
  return(i);
}




