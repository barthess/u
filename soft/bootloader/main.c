#include "ch.h"
#include "hal.h"

#define APPLICATION_OFFSET 0xC0000
typedef  void (*pFunction)(void);

int main(void) {
  u32 ApplicationAddress = FLASH_BASE+APPLICATION_OFFSET;
  /* Jump to user application */
  pFunction Jump_To_Application = (pFunction) (*(__IO uint32_t*) (ApplicationAddress + 4));
  /* Initialize user application's Stack Pointer */
  u32 stack = *(__IO uint32_t*) ApplicationAddress;
  __set_MSP(stack);
  Jump_To_Application();
}
