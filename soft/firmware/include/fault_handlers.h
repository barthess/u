#ifndef PANIC_H_
#define PANIC_H_

/**
 * evaluates to TRUE if system boots after soft reset cause by SYSRESETREQ
 */
#define was_softreset()      (((RCC)->CSR) & RCC_CSR_SFTRSTF)

/**
 * evaluates to TRUE if system boots after reset by power pad
 */
#define was_padreset()      (((RCC)->CSR) & RCC_CSR_PADRSTF)

/**
 * clear all reset flags
 */
#define clear_reset_flags()   (((RCC)->CSR) |= RCC_CSR_RMVF)

/**
 * Evaluates to TRUE if system runs under debugger control.
 * Note. This bit resets only by power reset.
 */
#define is_under_debugger()   (((CoreDebug)->DHCSR) & CoreDebug_DHCSR_C_DEBUGEN_Msk)


void uav_panic_handler(void);


#endif /* PANIC_H_ */
