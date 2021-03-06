#ifndef IRQ_STORM_H_
#define IRQ_STORM_H_

#define palToggleIrqStormLed() (palTogglePad(GPIOB, GPIOB_LED_R))
#define palOffIrqStormLed()    (palSetPad(GPIOB, GPIOB_LED_R))

Thread* irqstorm_clicmd(int argc, const char * const * argv, SerialDriver *sdp);

#endif /* IRQ_STORM_H_ */
