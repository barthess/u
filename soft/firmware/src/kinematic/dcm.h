#ifndef DCM_H_
#define DCM_H_

void dcmInit(void);
void dcmUpdate(float xacc,  float yacc,  float zacc,
               float ygyro, float xgyro, float zgyro,
               float imu_interval);

#endif /* DCM_H_ */
