#ifndef IRQ_STORM_H_
#define IRQ_STORM_H_


#if ENABLE_IRQ_STORM
  void IRQStormInit(void);
#else
  /* stub */
  #define IRQStormInit()
#endif /* ENABLE_IRQ_STORM */


#endif /* IRQ_STORM_H_ */
