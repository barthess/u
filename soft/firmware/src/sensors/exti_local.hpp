#ifndef _EXTI_LOCAL_H_
#define _EXTI_LOCAL_H_


void ExtiInitLocal(BinarySemaphore *mag3110_sem,
                   BinarySemaphore *mma8451_sem,
                   BinarySemaphore *bmp085_sem,
                   BinarySemaphore *itg3200_sem,
                   BinarySemaphore *lsm303_sem);
void ExtiEnablePps(void);

#endif /* _EXTI_LOCAL_H_ */
