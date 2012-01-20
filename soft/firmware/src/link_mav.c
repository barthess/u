#include "ch.h"
#include "hal.h"

#include "link_mav.h"
#include "rtc.h"
#include "message.h"
#include "proto_xbee.h"
#include "proto_pns.h"

#if !LINK_USE_XBEE_API

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define SDLINK SD2

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern LogItem log_item;
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

// почтовые ящики
static Mailbox fromxbee_mb;
static msg_t   fromxbee_mb_buf[1];

static Mailbox toxbee_mb;
static msg_t   tooxbee_mb_buf[8];

static XbeeMsg tlm_xbeemsg = {NULL, NULL, 0, TEST}; // сообщение с телеметрией
static VirtualTimer tlm_vt;                         // таймер для отправки телеметрии

static XbeeMsg toxbee_msg = {NULL, NULL, 0, 0};     // сообщение, приготовленное для отправки через модем



/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */


/* пытается вставить сообщение с телеметрией в очередь xbee кодера */
static void tlm_vt_cb(void *par){
  #define TLM_TRY_PERIOD 2
  (void)par;
  chVTSetI(&tlm_vt, MS2ST(TLM_TRY_PERIOD), &tlm_vt_cb, NULL);
  uint16_t msec = 0;

  // сначала проверяем наличе места и успешность обработки сообщения на предыдущем заходе
  if(tlm_xbeemsg.bufp != NULL || chMBGetUsedCountI(&tolink_mb) > 0)
    return;
  else{
    log_item.rtc_sec = rtcGetTime(&msec);
    log_item.rtc_msec = msec;

    tlm_xbeemsg.bufp = (uint8_t*)&log_item;
    tlm_xbeemsg.len = sizeof(log_item);
    tlm_xbeemsg.id  = LOGITEM;

    chMBPostI(&tolink_mb, (msg_t)&tlm_xbeemsg);
  }
  //chDbgCheck((eepromlog_len <= 64), "eepromlog_vt_cb");
  #undef TLM_TRY_PERIOD
}




static WORKING_AREA(MavLinkThreadWA, 1024);
__attribute__((noreturn))
static msg_t MavLinkThread(void *arg){
  chRegSetThreadName("MAVLink");
  (void)arg;

  // Define the system type, in this case an airplane
  int system_type = MAV_FIXED_WING;
  int autopilot_type = MAV_AUTOPILOT_GENERIC;

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len = 0;

  uint64_t pnstime = 0;
  uint16_t msec;
  uint32_t cnt = 0;

  while (TRUE) {
    cnt++;
    chThdSleepMilliseconds(50);
    if((cnt & 0xF) == 0xF){
      // Pack the message
      // mavlink_message_heartbeat_pack(system id, component id, message container, system type, MAV_AUTOPILOT_GENERIC)
      mavlink_msg_heartbeat_pack(100, 200, &msg, system_type, autopilot_type);
      // Copy the message to the send buffer
      len = mavlink_msg_to_send_buffer(buf, &msg);
      sdWrite(&SD1, buf, len);
    }

    pnstime = (uint64_t)1000000 * rtcGetTime(&msec) + (uint64_t)1000 * msec;

    float Ix = log_item.imu_x / 10000.0;
    float Iy = log_item.imu_y / 10000.0;
    float Iz = log_item.imu_z / 10000.0;

    float roll  = -atan2(-Iy, -Iz);
    float pitch = atan2(Ix, -Iz);

    mavlink_msg_attitude_pack(100, 200, &msg, pnstime, roll, pitch, 0, 0,0,0);
    len = mavlink_msg_to_send_buffer(buf, &msg);
    sdWrite(&SD1, buf, len);

    mavlink_msg_global_position_pack(100, 200, &msg, pnstime, 35, 35, log_item.baro_altitude / 10.0, 0,0,0);
    len = mavlink_msg_to_send_buffer(buf, &msg);
    sdWrite(&SD1, buf, len);
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
  0,//USART_CR2_STOP_1,
  0
};




static SerialConfig xbee_ser_cfg = {
    BAUDRATE_XBEE,
    0,
    0,
    0,
};

inline void GPSInit(void){
  /* настройка лапок на UEXT */
  palSetPadMode(IOPORT1, 9, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
  palSetPadMode(IOPORT1, 10, PAL_MODE_INPUT);

  /* запуск на дефолтной частоте */

  sdStart(&SDGPS, &xbee_ser_cfg);


}















/**
 * Инициализация связи через SD-драйвер
 */
inline void LinkInitXbeeMav(void){
  chBSemInit(&xbeesimplex_sem, TRUE);

  // настройка лапок
  palSetPadMode(IOPORT1, 9, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
  palSetPadMode(IOPORT1, 10, PAL_MODE_INPUT);
  uartStart(&UARTDlink, &uartlink_cfg);

  chMBInit(&fromxbee_mb, fromxbee_mb_buf, (sizeof(fromxbee_mb_buf)/sizeof(msg_t)));
  chMBInit(&toxbee_mb, tooxbee_mb_buf, (sizeof(tooxbee_mb_buf)/sizeof(msg_t)));
  chSysLock();
  chVTSetI(&tlm_vt, MS2ST(2000), &tlm_vt_cb, NULL);
  chSysUnlock();

  chThdSleepMilliseconds(3000);   /* ждем, пока модемы встанут в ружьё */

  chThdCreateStatic(LinkThreadWA,
          sizeof(LinkThreadWA),
          NORMALPRIO + 2,
          LinkThread,
          NULL);


  chThdCreateStatic(MavLinkThreadWA,
          sizeof(MavLinkThreadWA),
          NORMALPRIO,
          MavLinkThread,
          NULL);
}


#endif  /* LINK_USE_XBEE_API */
