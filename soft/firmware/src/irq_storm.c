#include <stdio.h>

#include "uav.h"

#include "../microrl/src/microrl.h"

#define IRQSTROM_GPTD1 GPTD3
#define IRQSTROM_GPTD2 GPTD2
//#define IRQSTORM_SD    SD2

/*===========================================================================*/
/* Extern vars.                                                              */
/*===========================================================================*/
extern MemoryHeap ThdHeap;

/*===========================================================================*/
/* Configurable settings.                                                    */
/*===========================================================================*/

#ifndef RANDOMIZE
#define RANDOMIZE       TRUE
#endif

#ifndef ITERATIONS
#define ITERATIONS      1
#endif

#ifndef NUM_THREADS
#define NUM_THREADS     4
#endif

#ifndef MAILBOX_SIZE
#define MAILBOX_SIZE    4
#endif

/*===========================================================================*/
/* Test related code.                                                        */
/*===========================================================================*/

#define MSG_SEND_LEFT   0
#define MSG_SEND_RIGHT  1

static bool_t saturated;

/*
 * Mailboxes. Them buffers will be allocated at thread context.
 */
static Mailbox *mb = NULL;
//static Mailbox mb[NUM_THREADS];

/*
 * Test worker threads.
 */
static WORKING_AREA(waWorkerThread[NUM_THREADS], 144);
static msg_t WorkerThread(void *arg) {
  chRegSetThreadName("IRQ_Worker");
  static volatile unsigned x = 0;
  static unsigned cnt = 0;
  unsigned me = (unsigned)arg;
  unsigned target;
  unsigned r;
  msg_t msg;

  /* Work loop.*/
  while (TRUE) {
    /* Waiting for a message.*/
   chMBFetch(&mb[me], &msg, TIME_INFINITE);

#if RANDOMIZE
   /* Pseudo-random delay.*/
   {
     chSysLock();
     r = rand() & 15;
     chSysUnlock();
     while (r--)
       x++;
   }
#else
   /* Fixed delay.*/
   {
     r = me >> 4;
     while (r--)
       x++;
   }
#endif

    /* Deciding in which direction to re-send the message.*/
    if (msg == MSG_SEND_LEFT)
      target = me - 1;
    else
      target = me + 1;

    if (target < NUM_THREADS) {
      /* If this thread is not at the end of a chain re-sending the message,
         note this check works because the variable target is unsigned.*/
      msg = chMBPost(&mb[target], msg, TIME_IMMEDIATE);
      if (msg != RDY_OK)
        saturated = TRUE;
    }
    else {
      /* Provides a visual feedback about the system.*/
      if (++cnt >= 500) {
        cnt = 0;
        palToggleIrqStormLed();
      }
    }
    /* exit correctly */
    if (chThdShouldTerminate())
      chThdExit(0);
  }
  return 0;
}

/*
 * GPT1 callback.
 */
static void gpt1cb(GPTDriver *gptp) {
  msg_t msg;

  (void)gptp;
  chSysLockFromIsr();
  msg = chMBPostI(&mb[0], MSG_SEND_RIGHT);
  if (msg != RDY_OK)
    saturated = TRUE;
  chSysUnlockFromIsr();
}

/*
 * GPT2 callback.
 */
static void gpt2cb(GPTDriver *gptp) {
  msg_t msg;

  (void)gptp;
  chSysLockFromIsr();
  msg = chMBPostI(&mb[NUM_THREADS - 1], MSG_SEND_LEFT);
  if (msg != RDY_OK)
    saturated = TRUE;
  chSysUnlockFromIsr();
}

/*
 * GPT1 configuration.
 */
static const GPTConfig gpt1cfg = {
  1000000,  /* 1MHz timer clock.*/
  gpt1cb    /* Timer callback.*/
};

/*
 * GPT2 configuration.
 */
static const GPTConfig gpt2cfg = {
  1000000,  /* 1MHz timer clock.*/
  gpt2cb    /* Timer callback.*/
};


/*===========================================================================*/
/* Generic demo code.                                                        */
/*===========================================================================*/

static void print(char *p) {
  cli_print(p);
}

static void println(char *p) {
  cli_println(p);
}

static void printn(uint32_t n) {
  char buf[16], *p;

  if (n == 0)
    cli_put('0');
  else {
    p = buf;
    while (n)
      *p++ = (n % 10) + '0', n /= 10;
    while (p > buf)
      cli_put(*--p);
  }
}

/* terminates correctly */
void _storm_abort(Thread* th_pull[]){
  unsigned i;
  chThdSleepMilliseconds(20);
  for (i = 0; i < NUM_THREADS; i++) {
    chThdTerminate(th_pull[i]);
    chMBPost(&mb[i], 0, TIME_INFINITE); /* gives worker thread a chace to run to chThdShouldTerminate()*/
    chThdWait(th_pull[i]);
  }
  palOffIrqStormLed();
}

/* Главный тред. */
static WORKING_AREA(StormTreadWA, 512);
static msg_t StormTread(void *arg){
  chRegSetThreadName("IRQ_Storm");
  (void)arg;
  unsigned i;
  gptcnt_t interval, threshold, worst;
  Mailbox _mb[NUM_THREADS];
  msg_t b[NUM_THREADS][MAILBOX_SIZE];

  /*
   * Initializes the mailboxes and creates the worker threads.
   */
  mb = _mb; /* init static variable */
  Thread* th_pull[NUM_THREADS];
  for (i = 0; i < NUM_THREADS; i++) {
    chMBInit(&mb[i], b[i], MAILBOX_SIZE);
    th_pull[i] = chThdCreateFromHeap(&ThdHeap,
                                     sizeof(waWorkerThread[i]),
                                     NORMALPRIO - 20,
                                     WorkerThread,
                                     (void *)i);
    if (th_pull[i] == NULL)
      chDbgPanic("can not allocate memory for thread");
  }

  /*
   * Test procedure.
   */
  println("");
  println("*** ChibiOS/RT IRQ-STORM long duration test");
  println("*** Press ^C to interrupt it");
  println("***");
  print("*** Kernel:       ");
  println(CH_KERNEL_VERSION);
#ifdef __GNUC__
  print("*** GCC Version:  ");
  println(__VERSION__);
#endif
  print("*** Architecture: ");
  println(CH_ARCHITECTURE_NAME);
#ifdef CH_CORE_VARIANT_NAME
  print("*** Core Variant: ");
  println(CH_CORE_VARIANT_NAME);
#endif
#ifdef PLATFORM_NAME
  print("*** Platform:     ");
  println(PLATFORM_NAME);
#endif
#ifdef BOARD_NAME
  print("*** Test Board:   ");
  println(BOARD_NAME);
#endif
  println("***");
  print("*** System Clock: ");
  printn(STM32_SYSCLK);
  println("");
  print("*** Iterations:   ");
  printn(ITERATIONS);
  println("");
  print("*** Randomize:    ");
  printn(RANDOMIZE);
  println("");
  print("*** Threads:      ");
  printn(NUM_THREADS);
  println("");
  print("*** Mailbox size: ");
  printn(MAILBOX_SIZE);
  println("");

  println("");
  worst = 0;

  for (i = 1; i <= ITERATIONS; i++){
    print("Iteration ");
    printn(i);
    println("");
    saturated = FALSE;
    threshold = 0;
    //defaults: max interval == 2000, min interval == 20, divider == 10
    for (interval = 1000; interval >= 20; interval -= interval / 10) {
      gptStartContinuous(&IRQSTROM_GPTD1, interval - 1); /* Slightly out of phase.*/
      gptStartContinuous(&IRQSTROM_GPTD2, interval + 1); /* Slightly out of phase.*/
      chThdSleepMilliseconds(1000);
      gptStopTimer(&IRQSTROM_GPTD1);
      gptStopTimer(&IRQSTROM_GPTD2);
      if (!saturated){
        print(".");
        printn(interval);
        println("");
      }
      else {
        print("#");
        println("");
        if (threshold == 0)
          threshold = interval;
      }
      if (chThdShouldTerminate()){
        _storm_abort(th_pull);
        chThdExit(0);
      }
    }
    /* Gives the worker threads a chance to empty the mailboxes before next
       cycle.*/
    chThdSleepMilliseconds(20);
    println("");
    print("Saturated at ");
    printn(threshold);
    println(" uS");
    println("");
    if (threshold > worst)
      worst = threshold;
  }
  gptStopTimer(&IRQSTROM_GPTD1);
  gptStopTimer(&IRQSTROM_GPTD2);

  print("Worst case at ");
  printn(worst);
  println(" uS");
  println("");
  println("Test Complete");

  gptStop(&IRQSTROM_GPTD1);
  gptStop(&IRQSTROM_GPTD2);
  _storm_abort(th_pull);
  chThdExit(0);

  return 0;
}


Thread* IRQStormStart(void){
  gptStart(&IRQSTROM_GPTD1, &gpt1cfg);
  gptStart(&IRQSTROM_GPTD2, &gpt2cfg);

  return chThdCreateFromHeap(&ThdHeap,
                             sizeof(StormTreadWA),
                             NORMALPRIO,
                             StormTread,
                             NULL);
}

Thread* irqstorm_clicmd(int argc, const char * const * argv, const ShellCmd_t *cmdarray){
  (void)argv;
  (void)argc;
  (void)cmdarray;

  return IRQStormStart();
}

