#ifndef _EXTI_PNS_H_
#define _EXTI_PNS_H_


void ExtiInit(BinarySemaphore *mag3110_sem,
              BinarySemaphore *mma8451_sem,
              BinarySemaphore *bmp085_sem,
              BinarySemaphore *itg3200_sem);
void ExtiEnablePps(void);

#endif /* _EXTI_PNS_H_ */
