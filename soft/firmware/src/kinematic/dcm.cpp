/*
 *      Author: starlino
 *              http://www.starlino.com/dcm_tutorial.html
 */

#include <math.h>

#include "main.h"
#include "global_flags.h"
#include "dcm.hpp"
#include "vector3d.hpp"
#include "param_registry.hpp"

/*
Output variables are:
  DcmEst[0..2] which are the direction cosine of the X,Y,Z axis
*/

/* maximum accelerometer weight in accelerometer-gyro fusion
 * formula this value is tuned-up experimentally:
 * if you get too much noise - decrease it if you get a delayed
 * response of the filtered values - increase it starting with
 * a value of  0.01 .. 0.05 will work for most sensors */

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/* maximum accelerometer errror relative to 1g ,
 * when error exceeds this value accelerometer weight becomes 0
 * this helps reject external accelerations (non-gravitational
 * innertial forces caused by device acceleration) */
#define ACC_ERR_MAX 0.3f

/* maximum magnetometer error relative to normal value of 1
 * (corresponding to earth's magnetic field) when error exceeds this
 * value magnetometer weight becomes 0 this helps reject magnetic
 * forces that are not attributed to earth's magnetic field */
#define MAG_ERR_MAX 0.2f

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern GlobalFlags_t GlobalFlags;
extern ParamRegistry param_registry;
extern float dcmEst[3][3];

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/* accelerometer data weight relative to gyro's weight of 1 */
static float const *accweight = NULL;

/* magnetometer data weight relative to gyro's weight of 1. */
static float const *magweight = NULL;

/* length of magnetic vector without external sources of magnetic field */
static uint32_t const *magvectorlen = NULL;

/* increments on each call to imu_update */
static uint32_t imu_step;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */

/* bring dcm matrix in order - adjust values to make
 * orthonormal (or at least closer to orthonormal) */
static void dcm_orthonormalize(float dcm[3][3]){
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
static void dcm_rotate(float dcm[3][3], float w[3]){
  //float W[3][3];
  //creates equivalent skew symetric matrix plus identity matrix
  //vector3d_skew_plus_identity((float*)w,(float*)W);
  //float dcmTmp[3][3];
  //matrix_multiply(3,3,3,(float*)W,(float*)dcm,(float*)dcmTmp);

  uint32_t i;
  float dR[3];
  //update matrix using formula R(t+1)= R(t) + dR(t) = R(t) + w x R(t)
  for(i=0;i<3;i++){
    vector3d_cross(w, dcm[i], dR);
    vector3d_add(dcm[i], dR, dcm[i]);
  }

  //make matrix orthonormal again
  dcm_orthonormalize(dcm);
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */

/* accelerations in g (scale does not matter because values will be normolized),
 * angular rates in rad/s (scale is MATTER),
 * magnetic flux in uT (scale does not matter because values will be normolized),
 * time in s */
void dcmUpdate(float *acc, float *gyro, float *mag, float imu_interval){

  uint32_t i = 0;
  float Kacc[3];  //K(b) vector according to accelerometer in body's coordinates
  float Imag[3];  //I(b) vector accordng to magnetometer in body's coordinates
  float w[3];     //gyro rates (angular velocity of a global vector in local coordinates)
  float wA[3];    //correction vector to bring dcmEst's K vector closer to Acc
  float wM[3];    //correction vector to bring dcmEst's I vector closer

  //interval since last call
  //imu_interval_ms = itg3200_period;

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
  /* Accelerometer measures gravity vector G in body coordinate system
  Gravity vector is the reverse of K unity vector of global system
  expressed in local coordinates K vector coincides with the z
  coordinate of body's i,j,k vectors expressed in global
  coordinates (K.i , K.j, K.k)

  Acc can estimate global K vector(zenith) measured in body's coordinate
  systems (the reverse of gravitation vector) */

//  Kacc[0] = -xacc;
//  Kacc[1] = -yacc;
//  Kacc[2] = -zacc;

  /* Поскольку на вход функции мы подаем значения измеренных ускорений по осям,
  а не вектор гравитации, то ничего инвертировать не надо.
  Вектор кажущегося ускорения совпадает с зенитным вектором К. */
  for (i = 0; i<3; i++)
    Kacc[i] = acc[i];
  nue2nwu(Kacc);

  vector3d_normalize(Kacc);

  // calculate correction vector to bring dcmEst's K vector closer to Acc
  // vector (K vector according to accelerometer)
  // wA = Kgyro x  Kacc , rotation needed to bring Kacc to Kgyro
  vector3d_cross(dcmEst[2], Kacc, wA);

  //---------------
  //Magnetomer
  //---------------
  // calculate correction vector to bring dcmEst's I vector closer
  // to Mag vector (I vector according to magnetometer)
  // in the absense of magnetometer let's assume North vector (I) is
  // always in XZ plane of the device (y coordinate is 0)
  //    Imag[0] = sqrtf(1 - dcmEst[0][2] * dcmEst[0][2]);
  //    Imag[1] = 0;
  //    Imag[2] = dcmEst[0][2];
  for (i = 0; i<3; i++)
    Imag[i] = mag[i];
  nue2nwu(Imag);

  /* Проработать комплексирование с нижним рядом DCM вместо вектора
   * гравитации. Какие-то непонятные результаты получаются, или я их
   * готовить не умею. */
  float tmpM[3];
  vector3d_normalize(Imag);
  //vector3d_cross(Kacc, Imag, tmpM);
  vector3d_cross(dcmEst[2], Imag, tmpM);
  vector3d_normalize(tmpM);
  //vector3d_cross(tmpM, Kacc, Imag);
  vector3d_cross(tmpM, dcmEst[2], Imag);
  vector3d_normalize(Imag);
  // wM = Igyro x Imag, roation needed to bring Imag to Igyro
  vector3d_cross(dcmEst[0], Imag, wM);

  //---------------
  //dcmEst
  //---------------
  //gyro rate direction is usually specified (in datasheets) as the device's(body's) rotation
  //about a fixed earth's (global) frame, if we look from the perspective of device then
  //the global vectors (I,K,J) rotation direction will be the inverse
  //rotation rate about accelerometer's X axis (GY output)
  //rotation rate about accelerometer's Y axis (GX output)
  //rotation rate about accelerometer's Z axis (GZ output)
  for (i = 0; i<3; i++)
    w[i] = -gyro[i];
  nue2nwu(w);

  /* correction factors for accelerometer and mognetometer weights */
  float magcor, acccor;
  if (1 == GlobalFlags.gyro_cal){
    acccor = 10;
    magcor = 10;
  }
  else{
    acccor = 1;
    magcor = 1;
  }

  float aw = *accweight * acccor;
  float mw = *magweight * magcor;

  for(i=0; i<3; i++){
    w[i] *= imu_interval;  //scale by elapsed time to get angle in radians
    //compute weighted average with the accelerometer correction vector
    w[i] = (w[i] + aw * wA[i] + mw * wM[i]) /
                  (1.0f + aw + mw);
  }

  dcm_rotate(dcmEst, w);
  imu_step++;
}

//-------------------------------------------------------------------
// imu_init
//-------------------------------------------------------------------
void dcmInit(){
  magweight = (float*)param_registry.valueSearch("IMU_magweight");
  accweight = (float*)param_registry.valueSearch("IMU_accweight");
  magvectorlen = (uint32_t*)param_registry.valueSearch("MAG_vectorlen");
}






