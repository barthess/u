#ifndef DCM_H_
#define DCM_H_

void dcmInit(void);
void dcmUpdate(float xacc,  float yacc,  float zacc,
               float xgyro, float ygyro, float zgyro,
               float xmag,  float ymag,  float zmag,
               float imu_interval);

#endif /* DCM_H_ */
