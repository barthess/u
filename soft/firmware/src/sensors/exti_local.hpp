#ifndef _EXTI_LOCAL_H_
#define _EXTI_LOCAL_H_


void ExtiInitLocal(chibios_rt::BinarySemaphore *mag3110_sem,
                   chibios_rt::BinarySemaphore *mma8451_sem,
                   chibios_rt::BinarySemaphore *bmp085_sem,
                   chibios_rt::BinarySemaphore *itg3200_sem,
                   chibios_rt::BinarySemaphore *lsm303_sem);
void ExtiEnablePps(void);

#endif /* _EXTI_LOCAL_H_ */
