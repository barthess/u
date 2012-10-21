#include "uav.h"

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
volatile uint32_t fake;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
volatile uint32_t r0;
volatile uint32_t r1;
volatile uint32_t r2;
volatile uint32_t r3;
volatile uint32_t r12;
volatile uint32_t lr; /* Link register. */
volatile uint32_t pc; /* Program counter. */
volatile uint32_t psr;/* Program status register. */
volatile unsigned long _CFSR ;
volatile unsigned long _HFSR ;
volatile unsigned long _DFSR ;
volatile unsigned long _AFSR ;
volatile unsigned long _BFAR ;
volatile unsigned long _MMAR ;
volatile unsigned long _SCB_SHCSR;

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
{
/* These are volatile to try and prevent the compiler/linker optimising them
away as the variables never actually get used.  If the debugger won't show the
values of the variables, make them global my moving their declaration outside
of this function. */
  uint32_t fake;

  r0 = pulFaultStackAddress[ 0 ];
  r1 = pulFaultStackAddress[ 1 ];
  r2 = pulFaultStackAddress[ 2 ];
  r3 = pulFaultStackAddress[ 3 ];

  r12 = pulFaultStackAddress[ 4 ];
  lr = pulFaultStackAddress[ 5 ];
  pc = pulFaultStackAddress[ 6 ];
  psr = pulFaultStackAddress[ 7 ];

  // Configurable Fault Status Register
  // Consists of MMSR, BFSR and UFSR
  _CFSR = (*((volatile unsigned long *)(0xE000ED28))) ;

  // Hard Fault Status Register
  _HFSR = (*((volatile unsigned long *)(0xE000ED2C))) ;

  // Debug Fault Status Register
  _DFSR = (*((volatile unsigned long *)(0xE000ED30))) ;

  // Auxiliary Fault Status Register
  _AFSR = (*((volatile unsigned long *)(0xE000ED3C))) ;

  // Read the Fault Address Registers. These may not contain valid values.
  // Check BFARVALID/MMARVALID to see if they are valid values
  // MemManage Fault Address Register
  _MMAR = (*((volatile unsigned long *)(0xE000ED34))) ;
  // Bus Fault Address Register
  _BFAR = (*((volatile unsigned long *)(0xE000ED38))) ;
  /* When the following line is hit, the variables contain the register values. */
  _SCB_SHCSR = SCB->SHCSR;

  __asm("BKPT #0\n") ; // Break into the debugger

  while(1){
    fake += r0;
    fake += r1;
    fake += r2;
    fake += r3;
    fake += r12;
    fake += lr;
    fake += pc;
    fake += psr;
    fake += _CFSR ;
    fake += _HFSR ;
    fake += _DFSR ;
    fake += _AFSR ;
    fake += _BFAR ;
    fake += _MMAR ;
    fake += _SCB_SHCSR;
  }
}

/* The fault handler implementation calls a function called
prvGetRegistersFromStack(). */
void HardFaultVector(void)
{
    __asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
}




void my_fault(void){
  while (TRUE){
    fake++;
  }
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

void DebugMonitorVector(void) {
  my_fault();
}
void Vector34(void) {
  my_fault();
}
void PendSVVector(void) {
  my_fault();
}
void Vector1C(void) {
  my_fault();
}
void Vector20(void) {
  my_fault();
}
void Vector24(void) {
  my_fault();
}
void Vector28(void) {
  my_fault();
}
//void HardFaultVector(void) {
//  my_fault();
//}
void MemManageVector(void) {
  my_fault();
}
volatile uint32_t rcc_cir = 0;
void NMIVector(void) {
  rcc_cir = RCC->CIR;
  my_fault();
  (void)rcc_cir;
}
void BusFaultVector(void) {
  my_fault();
}
void UsageFaultVector(void) {
  my_fault();
}

