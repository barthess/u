//=====================================================================================================
// MadgwickAHRS.c
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
// 19/02/2012	SOH Madgwick	Magnetometer measurement is normalised
//
//=====================================================================================================

//---------------------------------------------------------------------------------------------------
// Header files

#include "madgwick.hpp"
#include <math.h>
#include "message.hpp"
#include "geometry.hpp"

//---------------------------------------------------------------------------------------------------
// Definitions

//#define sampleFreq	100.0f		// sample frequency in Hz
//#define dT          0.01f
//#define betaDef		  (5 * (sqrtf(3.0f/4.0f) * 3.14159265f / 180.0f))		// 2 * proportional gain
#define betaDef    (0.07557f)
#define zetaDef     1.0f

extern mavlink_scaled_imu_t mavlink_out_scaled_imu_struct;

//---------------------------------------------------------------------------------------------------
// Variable definitions

//static volatile float beta = betaDef;								// 2 * proportional gain (Kp)
static volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;	// quaternion of sensor frame relative to auxiliary frame
//static float Wb[3] = {0, 0, 0};

//---------------------------------------------------------------------------------------------------
// Function declarations

float invSqrt(float x);

//====================================================================================================
// Functions

//---------------------------------------------------------------------------------------------------
// AHRS algorithm update


//#include "matrix.hpp"
//#include "quaternion.hpp"
//
//static uint32_t resetCached = 0;
//
//void MadgwickAHRSupdate(float N_g, float W_g, float U_g,
//                        float N_a, float W_a, float U_a,
//                        float N_m, float W_m, float U_m,
//                        float *res, float beta, float zeta, uint32_t reset) {
//
//  float gx = -W_g - Wb[0];
//  float gy = N_g  - Wb[1];
//  float gz = U_g  - Wb[2];
//
//  float ax = -W_a;
//  float ay = N_a;
//  float az = U_a;
//
//  float mx = -W_m;
//  float my = N_m;
//  float mz = U_m;
//
//  float delta_wb[4];
//
//	float recipNorm;
//	float s0, s1, s2, s3;
//	float qDot1, qDot2, qDot3, qDot4;
//	float hx, hy;
//	float _2q0mx, _2q0my, _2q0mz, _2q1mx, _2bx, _2bz, _4bx, _4bz, _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3, q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
//
//	// Rate of change of quaternion from gyroscope
//	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
//	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
//	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
//	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);
//
//	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
//	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
//
//		// Normalise accelerometer measurement
//		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
//		ax *= recipNorm;
//		ay *= recipNorm;
//		az *= recipNorm;
//
//		// Normalise magnetometer measurement
//		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
//		mx *= recipNorm;
//		my *= recipNorm;
//		mz *= recipNorm;
//
//		// Auxiliary variables to avoid repeated arithmetic
//		_2q0mx = 2.0f * q0 * mx;
//		_2q0my = 2.0f * q0 * my;
//		_2q0mz = 2.0f * q0 * mz;
//		_2q1mx = 2.0f * q1 * mx;
//		_2q0 = 2.0f * q0;
//		_2q1 = 2.0f * q1;
//		_2q2 = 2.0f * q2;
//		_2q3 = 2.0f * q3;
//		_2q0q2 = 2.0f * q0 * q2;
//		_2q2q3 = 2.0f * q2 * q3;
//		q0q0 = q0 * q0;
//		q0q1 = q0 * q1;
//		q0q2 = q0 * q2;
//		q0q3 = q0 * q3;
//		q1q1 = q1 * q1;
//		q1q2 = q1 * q2;
//		q1q3 = q1 * q3;
//		q2q2 = q2 * q2;
//		q2q3 = q2 * q3;
//		q3q3 = q3 * q3;
//
//		// Reference direction of Earth's magnetic field
//		hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1 + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
//		hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2 - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
//		_2bx = sqrtf(hx * hx + hy * hy);
//		_2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3 - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
//		_4bx = 2.0f * _2bx;
//		_4bz = 2.0f * _2bz;
//
//		// Gradient decent algorithm corrective step
//		s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 - ax) + _2q1 * (2.0f * q0q1 + _2q2q3 - ay) - _2bz * q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q3 + _2bz * q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
//		s1 = _2q3 * (2.0f * q1q3 - _2q0q2 - ax) + _2q0 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q1 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + _2bz * q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q2 + _2bz * q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q3 - _4bz * q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
//		s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 - ax) + _2q3 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q2 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + (-_4bx * q2 - _2bz * q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q1 + _2bz * q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q0 - _4bz * q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
//		s3 = _2q1 * (2.0f * q1q3 - _2q0q2 - ax) + _2q2 * (2.0f * q0q1 + _2q2q3 - ay) + (-_4bx * q3 + _2bz * q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q0 + _2bz * q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
//		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
//		s0 *= recipNorm;
//		s1 *= recipNorm;
//		s2 *= recipNorm;
//		s3 *= recipNorm;
//
//		// Apply feedback step
//		qDot1 -= beta * s0;
//		qDot2 -= beta * s1;
//		qDot3 -= beta * s2;
//		qDot4 -= beta * s3;
//
//		float tmp[4] = {q0, -q1, -q2, -q3};
//		float tmp2[4] = {s0, s1, s2, s3};
//		QuatMult(tmp, tmp2, delta_wb);
//		delta_wb[0] *= 2 * zeta * dT;
//		delta_wb[1] *= 2 * zeta * dT;
//		delta_wb[2] *= 2 * zeta * dT;
//		delta_wb[3] *= 2 * zeta * dT;
//
////		delta_wb = 2 * zeta * dT * obj.quatmult(obj.quatcon(q), step);
//		if (resetCached != reset){
//      resetCached = reset;
//      Wb[0] = 0;
//      Wb[1] = 0;
//      Wb[2] = 0;
//		}
//
//		Wb[0] += delta_wb[1];
//		Wb[1] += delta_wb[2];
//		Wb[2] += delta_wb[3];
////	  mavlink_out_scaled_imu_struct.xgyro = (int16_t)(frad2deg(Wb[0]) * 100);
////		mavlink_out_scaled_imu_struct.ygyro = (int16_t)(frad2deg(Wb[1]) * 100);
////    mavlink_out_scaled_imu_struct.zgyro = (int16_t)(frad2deg(Wb[2]) * 100);
//	}
//
//	// Integrate rate of change of quaternion to yield quaternion
//	q0 += qDot1 * dT;
//	q1 += qDot2 * dT;
//	q2 += qDot3 * dT;
//	q3 += qDot4 * dT;
//
//	// Normalise quaternion
//	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
//	q0 *= recipNorm;
//	q1 *= recipNorm;
//	q2 *= recipNorm;
//	q3 *= recipNorm;
//
//	res[0] = q0;
//	res[1] = q2;
//	res[2] = q3;
//	res[3] = q1;
//}
//
////---------------------------------------------------------------------------------------------------
//// IMU algorithm update
//
//void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az, float beta) {
//	float recipNorm;
//	float s0, s1, s2, s3;
//	float qDot1, qDot2, qDot3, qDot4;
//	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;
//
//	// Rate of change of quaternion from gyroscope
//	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
//	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
//	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
//	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);
//
//	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
//	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
//
//		// Normalise accelerometer measurement
//		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
//		ax *= recipNorm;
//		ay *= recipNorm;
//		az *= recipNorm;
//
//		// Auxiliary variables to avoid repeated arithmetic
//		_2q0 = 2.0f * q0;
//		_2q1 = 2.0f * q1;
//		_2q2 = 2.0f * q2;
//		_2q3 = 2.0f * q3;
//		_4q0 = 4.0f * q0;
//		_4q1 = 4.0f * q1;
//		_4q2 = 4.0f * q2;
//		_8q1 = 8.0f * q1;
//		_8q2 = 8.0f * q2;
//		q0q0 = q0 * q0;
//		q1q1 = q1 * q1;
//		q2q2 = q2 * q2;
//		q3q3 = q3 * q3;
//
//		// Gradient decent algorithm corrective step
//		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
//		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
//		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
//		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
//		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
//		s0 *= recipNorm;
//		s1 *= recipNorm;
//		s2 *= recipNorm;
//		s3 *= recipNorm;
//
//		// Apply feedback step
//		qDot1 -= beta * s0;
//		qDot2 -= beta * s1;
//		qDot3 -= beta * s2;
//		qDot4 -= beta * s3;
//	}
//
//	// Integrate rate of change of quaternion to yield quaternion
//	q0 += qDot1 * dT;
//	q1 += qDot2 * dT;
//	q2 += qDot3 * dT;
//	q3 += qDot4 * dT;
//
//	// Normalise quaternion
//	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
//	q0 *= recipNorm;
//	q1 *= recipNorm;
//	q2 *= recipNorm;
//	q3 *= recipNorm;
//}

//---------------------------------------------------------------------------------------------------
// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root

//float invSqrt(float x) {
//	float halfx = 0.5f * x;
//	float y = x;
//	long i = *(long*)&y;
//	i = 0x5f3759df - (i>>1);
//	y = *(float*)&i;
//	y = y * (1.5f - (halfx * y * y));
//	return y;
//}

float invSqrt(float x) {
  return 1.0f/sqrtf(x);
}


//====================================================================================================
// Matrix based code
//====================================================================================================
#include <cmath>
#include "main.h"
#include "matrix.hpp"
#include "quaternion.hpp"

static Quaternion<float> Q(1,0,0,0);
static Quaternion<float> qcon(1,0,0,0);
static Quaternion<float> h(1,0,0,0);

static Vector3d<float> Wb;
static Vector3d<float> b;
static Vector3d<float> d;

static float Fbuf[6];
static Matrix<typeof(Fbuf[0])> F    (Fbuf,   6, 1, sizeof(Fbuf));
static Matrix<typeof(Fbuf[0])> Ftop (Fbuf,   3, 1, sizeof(Fbuf) / 2);
static Matrix<typeof(Fbuf[0])> Fdown(Fbuf+3, 3, 1, sizeof(Fbuf) / 2);

static float Jbuf[24];
static Matrix<typeof(Jbuf[0])> J    (Jbuf,    6, 4, sizeof(Jbuf));
static Matrix<typeof(Jbuf[0])> Jtop (Jbuf,    3, 4, sizeof(Jbuf) / 2);
static Matrix<typeof(Jbuf[0])> Jdown(Jbuf+12, 3, 4, sizeof(Jbuf) / 2);

/* store transposed result here */
static float JbufT[24];
static Matrix<typeof(JbufT[0])> JT(JbufT, 4, 6, sizeof(JbufT));

template<typename T>
static void J_m(const Quaternion<T> *q, Vector3d<T> *d, Matrix<T> *result){
  float dx = (*d)(0);
  float dy = (*d)(1);
  float dz = (*d)(2);
  float q1 = (*q)(0);
  float q2 = (*q)(1);
  float q3 = (*q)(2);
  float q4 = (*q)(3);

  (*result)(0,0) = 2*dy*q4 - 2*dz*q3;
  (*result)(1,0) = 2*dz*q2 - 2*dx*q4;
  (*result)(2,0) = 2*dx*q3 - 2*dy*q2;

  (*result)(0,1) = 2*dy*q3 + 2*dz*q4;
  (*result)(1,1) = 2*dx*q3 - 4*dy*q2 + 2*dz*q1;
  (*result)(2,1) = 2*dx*q4 - 2*dy*q1 - 4*dz*q2;

  (*result)(0,2) = 2*dy*q2 - 4*dx*q3 - 2*dz*q1;
  (*result)(1,2) = 2*dx*q2 + 2*dz*q4;
  (*result)(2,2) = 2*dx*q1 + 2*dy*q4 - 4*dz*q3;

  (*result)(0,3) = 2*dy*q1 - 4*dx*q4 + 2*dz*q2;
  (*result)(1,3) = 2*dz*q3 - 4*dy*q4 - 2*dx*q1;
  (*result)(2,3) = 2*dx*q2 + 2*dy*q3;
}


template<typename T>
static void F_m(const Quaternion<T> *q, Vector3d<T> *d, Vector3d<T> *s, Matrix<T> *result){
  float dx = (*d)(0);
  float dy = (*d)(1);
  float dz = (*d)(2);
  float q1 = (*q)(0);
  float q2 = (*q)(1);
  float q3 = (*q)(2);
  float q4 = (*q)(3);
  float sx = (*s)(0);
  float sy = (*s)(1);
  float sz = (*s)(2);

  (*result)(0,0) = 2*dx*(0.5 - q3*q3 - q4*q4) + 2*dy*(q1*q4 + q2*q3)       + 2*dz*(q2*q4 - q1*q3) - sx;
  (*result)(1,0) = 2*dx*(q2*q3 - q1*q4)       + 2*dy*(0.5 - q2*q2 - q4*q4) + 2*dz*(q1*q2 + q3*q4) - sy;
  (*result)(2,0) = 2*dx*(q1*q3 + q2*q4)       + 2*dy*(q3*q4 - q1*q2)       + 2*dz*(0.5 - q2*q2 - q3*q3) - sz;
}

void MyAHRS::update(const float *gyro, const float *acc, const float *mag,
                    Quaternion<float> *result, const float dT){
  Vector3d<float> Gyroscope(gyro);
  Vector3d<float> Accelerometer(acc);
  Vector3d<float> Magnetometer(mag);
  Quaternion<float> step(1,0,0,0);

  Accelerometer.normalize();
  Magnetometer.normalize();

  Quaternion<float> tmp;
  Quaternion<float> qDot;

  //h = quatmult(q, quatmult([0 Magnetometer].', quatcon(q)));
  Quaternion<float> qmag(0, Magnetometer(0), Magnetometer(1), Magnetometer(2));
  Q.ccon(&qcon);
  qmag.mul(&qcon, &tmp);
  Q.mul(&tmp, &h);

  //b = [norm([m_n m_e]) m_u 0];
  //% Reference direction of Earth's G feild
  //d = [0 1 0];
  b(0) = sqrtf(h(1)*h(1) + h(3)*h(3));
  b(1) = h(2);
  b(2) = 0;

  d(0) = 0;
  d(1) = 1;
  d(2) = 0;

  //Gradient decent algorithm corrective step
  F_m(&Q, &d, &Accelerometer, &Ftop);
  F_m(&Q, &b, &Magnetometer, &Fdown);

  J_m(&Q, &d, &Jtop);
  J_m(&Q, &b, &Jdown);

  J.transpose(&JT);
  JT.mul(&F, &step);
  step.normalize();
  Gyroscope -= &Wb;

  //Compute rate of change of quaternion
  //qDot_w = 0.5*quatmult(q, [0 Gyroscope(1) Gyroscope(2) Gyroscope(3)].');
  //qDot = qDot_w - obj.Beta * step;
  //obj.Q_w = q_w/norm(q_w);
  Quaternion<float> qGyr(0, gyro[0], gyro[1], gyro[2]);
  Q.mul(&qGyr, &qDot);
  qDot *= 0.5f;
  step *= betaDef;
  qDot -= &step;

  //Integrate to yield quaternion
  //q = q + qDot*obj.dT;
  //obj.Q = q/norm(q); % normalise quaternion
  qDot *= dT;
  Q += &qDot;
  Q.normalize();

  //delta_wb = 2*obj.Zeta*obj.dT * quatmult(quatcon(q), step);
  Q.ccon(&qcon);
  qcon.mul(&step, &tmp);
  tmp *= 2 * zetaDef * dT;

  //Wb = wb+delta_wb(2:4);
  Wb(0) = tmp(1);
  Wb(1) = tmp(2);
  Wb(2) = tmp(3);

  *result = Q;
}




//====================================================================================================
// END OF CODE
//====================================================================================================
