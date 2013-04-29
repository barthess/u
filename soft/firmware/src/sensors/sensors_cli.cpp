#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "chprintf.h"
#include "sensors.hpp"

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
extern MemoryHeap ThdHeap;
extern const CompensatedData comp_data;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static Thread *sensor_tp;

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/**
 *
 */
static WORKING_AREA(SensorsCmdThreadWA, 512);
static msg_t SensorsCmdThread(void *sdp){
  chRegSetThreadName("SensorsCmd");

//  const int n = 32;
//  char str[n];

  while (!chThdShouldTerminate()){
    chprintf((BaseSequentialStream *)sdp, "%u mA\r\n", (unsigned int)comp_data.main_current);
//    snprintf(str, n, "%u mA\r\n", (unsigned int)comp_data.main_current);
//    cli_print(str);
    chThdSleepMilliseconds(100);
  }

  chThdExit(0);
  return 0;
}

/**
 *
 */
Thread* sensors_clicmd(int argc, const char * const * argv, SerialDriver *sdp){
  (void)argc;
  (void)argv;

  sensor_tp = chThdCreateFromHeap(&ThdHeap,
                                  sizeof(SensorsCmdThreadWA),
                                  CMD_THREADS_PRIO - 1,
                                  SensorsCmdThread,
                                  sdp);
  if (sensor_tp == NULL)
    chDbgPanic("Can not allocate memory");

  return sensor_tp;
}
