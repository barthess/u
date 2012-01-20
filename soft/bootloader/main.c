/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "ch.h"
#include "hal.h"



#define APPLICATION_OFFSET 0xE0000
typedef  void (*pFunction)(void);

void startApp(void) {
  u32 ApplicationAddress = FLASH_BASE+APPLICATION_OFFSET;
  /* Jump to user application */
  pFunction Jump_To_Application = (pFunction) (*(__IO uint32_t*) (ApplicationAddress + 4));
  /* Initialize user application's Stack Pointer */
  u32 stack = *(__IO uint32_t*) ApplicationAddress;
  __set_MSP(stack);
  Jump_To_Application();
}


/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  startApp();
}
