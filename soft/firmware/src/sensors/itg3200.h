#include <stdlib.h>
#include "ch.h"

#ifndef ITG3200_H_
#define ITG3200_H_



/* buffers depth */
#define GYRO_RX_DEPTH 8
#define GYRO_TX_DEPTH 4


#define GYRO_OUT_DATA   0x1B // начиная с термометра
#define GYRO_SMPLRT_DIV 0x15
#define GYRO_INT_CFG    0x17
#define GYRO_DLPF_FS    0x16
  #define GYRO_FS_SEL   (3 << 3) //full scale range
  #define GYRO_DLPF_CFG (5)//low pass finlter bandwidth
#define GYRO_PWR_MGMT   0x3E


/* сколько взять сэмплов для определения нуля гироскопов */
#define GYRO_AVG_SAMPLES_CNT 1024


void init_itg3200(void);
void gyro_refresh_zeros(void);



#endif /* ITG3200_H_ */
