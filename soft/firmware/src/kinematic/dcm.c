#include <math.h>

#include "ch.h"
#include "hal.h"

#include "dcm.h"
#include "vector3d.h"
#include "matrix.h"

/*
How to use this module in other projects.

Input variables are:
  adcAvg[0..6]  ADC readings of 3 axis accelerometer and 3 axis gyroscope (they are calculated in the background by adcutil.h)
  interval_us - interval in microseconds since last call to imu_update

Output variables are:
  DcmEst[0..2] which are the direction cosine of the X,Y,Z axis

First you must initialize the module with:
  imu_init();

Then call periodically every 5-20ms:
  imu_update();
  it is assumed that you also update periodicall the adcAvg[0..5] array

*/

#define ACC_WEIGHT_MAX 0.04     //maximum accelerometer weight in accelerometer-gyro fusion formula
                  //this value is tuned-up experimentally: if you get too much noise - decrease it
                  //if you get a delayed response of the filtered values - increase it
                  //starting with a value of  0.01 .. 0.05 will work for most sensors


extern uint32_t itg3200_period;


//-------------------------------------------------------------------
// Globals
//-------------------------------------------------------------------

unsigned int imu_sequence = 0;            //incremented on each call to imu_update
float dcmEst[3][3] = {{1,0,0},{0,1,0},{0,0,1}};   //estimated DCM matrix


//-------------------------------------------------------------------
//Get accelerometer reading (accelration expressed in g)
//-------------------------------------------------------------------
float getAcclOutput(unsigned char w){
  float tmpf;            //temporary variable for complex calculations
  tmpf = adcAvg[w] - config.accOffs[w]; //remove offset
  tmpf /= config.accSens[w];        //divide by sensitivity
  if(config.accInv[w])
    tmpf = -tmpf;   //invert axis value if needed
  return tmpf;
}

//-------------------------------------------------------------------
//Get gyro reading (rate of rotation expressed in deg/ms)
//-------------------------------------------------------------------
float getGyroOutput(unsigned char w){
  float tmpf;              //temporary variable for complex calculations
  tmpf = adcAvg[3+w] - config.gyroOffs[w];  //remove offset
  tmpf /= config.gyroSens[w];         //divide by sensitivity
  if(config.gyroInv[w])
    tmpf = -tmpf;   //invert axis value if needed
  return tmpf;
}

//bring dcm matrix in order - adjust values to make orthonormal (or at least closer to orthonormal)
void dcm_orthonormalize(float dcm[3][3]){
  //err = X . Y ,  X = X - err/2 * Y , Y = Y - err/2 * X  (DCMDraft2 Eqn.19)
  float err = vector3d_dot((float*)(dcm[0]),(float*)(dcm[1]));
  float delta[2][3];
  vector3d_scale(-err/2,(float*)(dcm[1]),(float*)(delta[0]));
  vector3d_scale(-err/2,(float*)(dcm[0]),(float*)(delta[1]));
  vector3d_add((float*)(dcm[0]),(float*)(delta[0]),(float*)(dcm[0]));
  vector3d_add((float*)(dcm[1]),(float*)(delta[1]),(float*)(dcm[1]));

  //Z = X x Y  (DCMDraft2 Eqn. 20) ,
  vector3d_cross((float*)(dcm[0]),(float*)(dcm[1]),(float*)(dcm[2]));
  //re-nomralization
  vector3d_normalize((float*)(dcm[0]));
  vector3d_normalize((float*)(dcm[1]));
  vector3d_normalize((float*)(dcm[2]));
}


//rotate DCM matrix by a small rotation given by angular rotation vector w
//see http://gentlenav.googlecode.com/files/DCMDraft2.pdf
void dcm_rotate(float dcm[3][3], float w[3]){
  //float W[3][3];
  //creates equivalent skew symetric matrix plus identity matrix
  //vector3d_skew_plus_identity((float*)w,(float*)W);
  //float dcmTmp[3][3];
  //matrix_multiply(3,3,3,(float*)W,(float*)dcm,(float*)dcmTmp);

  int i;
  float dR[3];
  //update matrix using formula R(t+1)= R(t) + dR(t) = R(t) + w x R(t)
  for(i=0;i<3;i++){
    vector3d_cross(w,dcm[i],dR);
    vector3d_add(dcm[i],dR,dcm[i]);
  }

  //make matrix orthonormal again
  dcm_orthonormalize(dcm);
}


//-------------------------------------------------------------------
// imu_init
//-------------------------------------------------------------------
void dcmInit(){
  //TODO: load coefficients from param struct
  return;
}



//-------------------------------------------------------------------
// imu_update
//-------------------------------------------------------------------
#define ACC_WEIGHT 0.01   //accelerometer data weight relative to gyro's weight of 1
#define ACC_ERR_MAX 0.3   //maximum accelerometer errror relative to 1g , when error exceeds this value accelerometer weight becomes 0
              //this helps reject external accelerations (non-gravitational innertial forces caused by device acceleration)
#define MAG_WEIGHT 0.0    //magnetometer data weight relative to gyro's weight of 1
#define MAG_ERR_MAX 0.3   //maximum magnetometer error relative to normal value of 1 (corresponding to earth's magnetic field)
              //when error exceeds this value magnetometer weight becomes 0
              //this helps reject magnetic forces that are not attributed to earth's magnetic field

float imu_interval_ms = 0;    //interval since last call to imu_update
float Kacc[3];          //K(b) vector according to accelerometer in body's coordinates
float Imag[3];          //I(b) vector accordng to magnetometer in body's coordinates

void imu_update(){
  int i;
  imu_sequence++;

  //interval since last call
  imu_interval_ms = itg3200_period;

  //---------------
  // I,J,K unity vectors of global coordinate system I-North,J-West,K-zenith
  // i,j,k unity vectors of body's coordiante system  i-"nose", j-"left wing", k-"top"
  //---------------
  //        [I.i , I.j, I.k]
  // DCM =  [J.i , J.j, J.k]
  //        [K.i , K.j, K.k]

  //---------------
  //Acelerometer
  //---------------
  //Accelerometer measures gravity vector G in body coordinate system
  //Gravity vector is the reverse of K unity vector of global system expressed in local coordinates
  //K vector coincides with the z coordinate of body's i,j,k vectors expressed in global coordinates (K.i , K.j, K.k)

  //Acc can estimate global K vector(zenith) measured in body's coordinate systems (the reverse of gravitation vector)
  Kacc[0] = -getAcclOutput(0);
  Kacc[1] = -getAcclOutput(1);
  Kacc[2] = -getAcclOutput(2);
  vector3d_normalize(Kacc);
  //calculate correction vector to bring dcmEst's K vector closer to Acc vector (K vector according to accelerometer)
  float wA[3];
  vector3d_cross(dcmEst[2],Kacc,wA);  // wA = Kgyro x  Kacc , rotation needed to bring Kacc to Kgyro

  //---------------
  //Magnetomer
  //---------------
  //calculate correction vector to bring dcmEst's I vector closer to Mag vector (I vector according to magnetometer)
  float wM[3];
  //in the absense of magnetometer let's assume North vector (I) is always in XZ plane of the device (y coordinate is 0)
  Imag[0] = sqrtf(1-dcmEst[0][2]*dcmEst[0][2]);
  Imag[1] = 0;
  Imag[2] = dcmEst[0][2];

  vector3d_cross(dcmEst[0],Imag,wM);  // wM = Igyro x Imag, roation needed to bring Imag to Igyro

  //---------------
  //dcmEst
  //---------------
  //gyro rate direction is usually specified (in datasheets) as the device's(body's) rotation
  //about a fixed earth's (global) frame, if we look from the perspective of device then
  //the global vectors (I,K,J) rotation direction will be the inverse
  float w[3];         //gyro rates (angular velocity of a global vector in local coordinates)
  w[0] = -getGyroOutput(1); //rotation rate about accelerometer's X axis (GY output) in rad/ms
  w[1] = -getGyroOutput(0); //rotation rate about accelerometer's Y axis (GX output) in rad/ms
  w[2] = -getGyroOutput(2); //rotation rate about accelerometer's Z axis (GZ output) in rad/ms
  for(i=0;i<3;i++){
    w[i] *= imu_interval_ms;  //scale by elapsed time to get angle in radians
    //compute weighted average with the accelerometer correction vector
    w[i] = (w[i] + ACC_WEIGHT*wA[i] + MAG_WEIGHT*wM[i])/(1.0+ACC_WEIGHT+MAG_WEIGHT);
  }

  dcm_rotate(dcmEst,w);
}


