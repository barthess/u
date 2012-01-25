#include "ch.h"
#include "hal.h"

#include "link_xbee_api.h"
#include "rtc.h"
#include "message.h"
#include "proto_xbee.h"
#include "proto_pns.h"

#if LINK_USE_XBEE_API
/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define UARTDlink UARTD2

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern LogItem log_item;
//extern RTCTime timespec;
extern BinarySemaphore link_thd_sem;
extern Mailbox tolink_mb;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/* семафор для предотвращения попыток дуплексной связи через модемы
 * Будет сбрасываться с помощью коллбэка USART */
static BinarySemaphore xbeesimplex_sem;
/* семафор для заворачивалки данных в пакеты. Предназначен для того чтобы
 * не испортить данные, которые не успели забрать из буфера */
static BinarySemaphore xbeewrapper_sem;

// почтовые ящики
static Mailbox fromxbee_mb;
static msg_t   fromxbee_mb_buf[1];

static Mailbox toxbee_mb;
static msg_t   tooxbee_mb_buf[8];

static XbeeMsg tlm_xbeemsg = {NULL, NULL, 0, TEST}; // сообщение с телеметрией
static VirtualTimer tlm_vt;                         // таймер для отправки телеметрии

static XbeeMsg toxbee_msg = {NULL, NULL, 0, 0};     // сообщение, приготовленное для отправки через модем

/* буфер под пакет передаваемых эскейпнутых данных. */
static uint8_t opacket[O_PACKET_LEN];
/* буфер под пакет принимаемых эскейпнутых данных. */
static uint8_t ipacket[I_PACKET_LEN];
/* буфер под разъэскейпанный входящий пакет */
static uint8_t clean_ipacket[I_PACKET_LEN];


/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/* пытается вставить сообщение с телеметрией в очередь xbee кодера */
static void tlm_vt_cb(void *par){
  #define TLM_TRY_PERIOD 5
  (void)par;
  chVTSetI(&tlm_vt, MS2ST(TLM_TRY_PERIOD), &tlm_vt_cb, NULL);

  // сначала проверяем наличе места и успешность обработки сообщения на предыдущем заходе
  if(tlm_xbeemsg.bufp != NULL || chMBGetUsedCountI(&tolink_mb) > 0)
    return;
  else{
    //rtcGetTime(&RTCD1, &timespec);
    //log_item.rtc_sec = timespec.tv_sec;
    //log_item.rtc_msec = (uint16_t)timespec.tv_msec;

    tlm_xbeemsg.bufp = (uint8_t*)&log_item;
    tlm_xbeemsg.len = sizeof(log_item);
    tlm_xbeemsg.id  = LOGITEM;

    chMBPostI(&tolink_mb, (msg_t)&tlm_xbeemsg);
  }
  //chDbgCheck((eepromlog_len <= 64), "eepromlog_vt_cb");
  #undef TLM_TRY_PERIOD
}


/**
 * @brief
 * Поток заворачивания данных в пакет xbee.
 * @details
 * Берет сообщение из входящего ящика.
 * Выковыривает оттуда массив данных.
 * Прогоняет данные через функции xbee.
 * Обработанные данные заворачивает в сообщение.
 * Кладет получившееся сообщение в исходящий почтовый ящик.
 *
 * По приблизительным оценкам, заготовка пакета для xbee занимает около 140 мкс.
 */
static WORKING_AREA(XbeeWrapThreadWA, 256);
__attribute__((noreturn))
static msg_t XbeeWrapThread(void *arg){
  chRegSetThreadName("XbeeWrap");
  (void)arg;

  msg_t msg;
  uint8_t *buf;
  uint16_t inlen;  // длинна входящего в функцию сообщения
  uint16_t outlen; // длинна выходящего из функции сообещия
  packet_id id;    // ID пакета для заворачивалки
  msg_t status = 0;

  while(TRUE){
    status = chMBFetch(&tolink_mb, &msg, TIME_INFINITE);
    chDbgCheck((&msg != NULL), "");
    inlen = ((XbeeMsg *)msg)->len;
    id    = ((XbeeMsg *)msg)->id;
    buf   = ((XbeeMsg *)msg)->bufp;
    outlen = xbee_wrap(opacket, buf, inlen, id, 0);
    ((XbeeMsg *)msg)->bufp = NULL;

    toxbee_msg.bufp = opacket;
    toxbee_msg.len = outlen;
    status = chMBPost(&toxbee_mb, (msg_t)&toxbee_msg, TIME_INFINITE);

    /* ждем, пока будет забрана модемным потоком предыдущая порция данных */
    chBSemWait(&xbeewrapper_sem);
  }
}

/**
 * Поток выковыривания данных из пакета xbee.
 */
static WORKING_AREA(XbeeExtractThreadWA, 256);
__attribute__((noreturn))
static msg_t XbeeExtractThread(void *arg){
  chRegSetThreadName("XbeeExtract");
  (void)arg;

  uint8_t *received_data = NULL; // указатель на начало полезной нагрузки в глобальном буфере "clean_ipacket"
  msg_t   msg; // сообщение из модема, которое надо пропарсить

  while (TRUE) {
    chMBFetch(&fromxbee_mb, &msg, TIME_INFINITE);
    received_data = xbee_extract(clean_ipacket, ((XbeeMsg *)msg)->bufp, ((XbeeMsg *)msg)->len);
    if (received_data != NULL){
//      palTogglePad(IOPORT3, GPIOC_LED);
      ProtoPnsParser(received_data);                     /* дернем внешнюю функцию обработки данных */
    }
    ((XbeeMsg *)msg)->bufp = NULL;                       /* готов к приему новых данных */
  }
}


/**
 * Поток отправки/приема данных через модем.
 *
 * Синхронизирован с ШИМ с помощью семафора.
 * По нечетному периоду отправляет пакет, по четному - принимает
 *
 * TODO: счетчик для контроля потерь
 */
static WORKING_AREA(LinkThreadWA, 256);
__attribute__((noreturn))
static msg_t LinkThread(void *arg){
  chRegSetThreadName("Link");
  (void)arg;

  uint32_t oddcheck = 1; // для проверки на четность периода
  msg_t result;
  msg_t msg;   // для сообщения из почтового ящика
  uint8_t *buf;// временный буфер
  uint16_t len;
  XbeeMsg fromxbee_msg = {NULL, NULL, 0, 0}; // сообщение из модема, которое надо пропарсить

  while(TRUE){
    chBSemWait(&link_thd_sem);                              /* Waiting for the signal in semaphore. Signaled from servo ISR. */
    switch(oddcheck & 1){
    /*********** нечетный период *************/
    case 1:
      result = chMBFetch(&toxbee_mb, &msg, TIME_IMMEDIATE);
      if (result == RDY_OK){
        buf = ((XbeeMsg *)msg)->bufp;
        len = ((XbeeMsg *)msg)->len;
        uartStartSend(&UARTDlink, len, buf);
        chBSemWait(&xbeesimplex_sem);                       /* ждем, пока коллбэк не отпустит семафор */
        ((XbeeMsg *)msg)->bufp = NULL;
        chBSemSignal(&xbeewrapper_sem);                     /* извещаем поток заворачивания данных */
      }
      // все данные в модем вдули. Теперь принимаем из него данные.
      uartStartReceive(&UARTDlink, I_PACKET_LEN, ipacket);
      break;

    /*************** четный период *************/
    case 0:
      chThdSleepMilliseconds(19);                           /* ждем, пока буфер заполнится. Учитываем, что период у нас 20 мс. */
      if (fromxbee_msg.bufp != NULL){                       /* данные по какой-то причине до сих пор не обработаны */
        uartStopReceive(&UARTDlink);
        break;
      }
      len = uartStopReceive(&UARTDlink);                    /* что успели принять, то и будем парсить */
      len = I_PACKET_LEN - len;
      if (len >= CONTROL_LEN){
        fromxbee_msg.bufp = ipacket;
        fromxbee_msg.len = len;
        chMBPost(&fromxbee_mb, (msg_t)&fromxbee_msg, TIME_IMMEDIATE);
      }
      break;

    default:
      break;
    } /* switch() */

    oddcheck++;
  }
}





/*
 * This callback is invoked when a transmission buffer has been completely
 * read by the driver.
 */
static void txend1(UARTDriver *uartp) {
  (void)uartp;
}

/*
 * This callback is invoked when a transmission has phisically completed.
 */
static void txend2(UARTDriver *uartp) {
  (void)uartp;
  /* отпускаем семафор, чтобы поток связи переключился на приём данных */
  chSysLockFromIsr();
  chBSemSignalI(&xbeesimplex_sem);
  chSysUnlockFromIsr();
}

/*
 * This callback is invoked on a receive error, the errors mask is passed
 * as parameter.
 */
static void rxerr(UARTDriver *uartp, uartflags_t e) {
  (void)uartp;
  (void)e;
}

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 */
static void rxchar(UARTDriver *uartp, uint16_t c) {
  (void)uartp;
  (void)c;
}

/*
 * This callback is invoked when a receive buffer has been completely written.
 */
static void rxend(UARTDriver *uartp) {
  (void)uartp;
}

/*
 * UART driver configuration structure.
 */
static UARTConfig uartlink_cfg = {
  txend1,
  txend2,
  rxend,
  rxchar,
  rxerr,
  BAUDRATE_XBEE,
  0,
  USART_CR2_STOP_1,
  0
};

/**
 * Инициализация связи через SD-драйвер
 */
inline void LinkInitXbeeApi(void){
  int i = 0;
  for (i = 0; i < O_PACKET_LEN; i++)
    opacket[i] = 0x55;
  for (i = 0; i < I_PACKET_LEN; i++)
    ipacket[i] = 0x55;
  for (i = 0; i < I_PACKET_LEN; i++)
    clean_ipacket[i] = 0x55;

  chBSemInit(&xbeesimplex_sem, TRUE);
  chBSemInit(&xbeewrapper_sem, TRUE);

  chMBInit(&fromxbee_mb, fromxbee_mb_buf, (sizeof(fromxbee_mb_buf)/sizeof(msg_t)));
  chMBInit(&toxbee_mb, tooxbee_mb_buf, (sizeof(tooxbee_mb_buf)/sizeof(msg_t)));
  chSysLock();
  chVTSetI(&tlm_vt, MS2ST(2000), &tlm_vt_cb, NULL);
  chSysUnlock();

  uartStart(&UARTDlink, &uartlink_cfg);

  chThdSleepMilliseconds(3000);   /* ждем, пока модемы встанут в ружьё */

  chThdCreateStatic(LinkThreadWA,
          sizeof(LinkThreadWA),
          NORMALPRIO + 2,
          LinkThread,
          NULL);

  chThdCreateStatic(XbeeExtractThreadWA,
          sizeof(XbeeExtractThreadWA),
          NORMALPRIO,
          XbeeExtractThread,
          NULL);

  chThdCreateStatic(XbeeWrapThreadWA,
          sizeof(XbeeWrapThreadWA),
          NORMALPRIO,
          XbeeWrapThread,
          NULL);
}

#endif /* LINK_USE_XBEE_API */
