#include <cmath>
#include "main.h"
#include "quaternion.hpp"
#include "madgwick.hpp"
#include "message.hpp"
#include "param_registry.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
extern ParamRegistry param_registry;

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */
static Quaternion<float> h(1,0,0,0);

static Vector3d<float> Wb(0,0,0); /* Gyro bias drift */
static Vector3d<float> b; /* earth magnetic field */
static Vector3d<float> d(0,1,0); /* earth gravity field */

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

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */
/**
 *
 */
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

/**
 *
 */
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

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
MadgwickAHRS::MadgwickAHRS(void){
  ready = false;
}

/**
 *
 */
void MadgwickAHRS::update(const float *gyro, const float *acc, const float *mag,
                    Quaternion<float> *Q, const float dT){

  chDbgCheck(true == ready, "AHRS not ready");

  Vector3d<float> Gyroscope(gyro);
  Vector3d<float> Accelerometer(acc);
  Vector3d<float> Magnetometer(mag);
  Quaternion<float> step(1,0,0,0);

  Accelerometer.normalize();
  Magnetometer.normalize();

  Quaternion<float> tmp;
  Quaternion<float> qDot;
  Quaternion<float> qcon(1,0,0,0); /* complex conjunction to main quaternion */

  //h = quatmult(q, quatmult([0 Magnetometer].', quatcon(q)));
  Quaternion<float> qmag(0, Magnetometer(0), Magnetometer(1), Magnetometer(2));
  Q->ccon(&qcon);
  qmag.mul(&qcon, &tmp);
  Q->mul(&tmp, &h);

  //b = [norm([m_n m_e]) m_u 0];
  //% Reference direction of Earth's G feild
  //d = [0 1 0];
  b(0) = sqrtf(h(1)*h(1) + h(3)*h(3));
  b(1) = h(2);
  b(2) = 0;

  //Gradient decent algorithm corrective step
  F_m(Q, &d, &Accelerometer, &Ftop);
  F_m(Q, &b, &Magnetometer, &Fdown);

  J_m(Q, &d, &Jtop);
  J_m(Q, &b, &Jdown);

  J.transpose(&JT);
  JT.mul(&F, &step);
  step.normalize();
  Gyroscope -= &Wb;

  //Compute rate of change of quaternion
  //qDot_w = 0.5*quatmult(q, [0 Gyroscope(1) Gyroscope(2) Gyroscope(3)].');
  //qDot = qDot_w - obj.Beta * step;
  //obj.Q_w = q_w/norm(q_w);
  tmp(0) = 0;
  tmp(1) = gyro[0];
  tmp(2) = gyro[1];
  tmp(3) = gyro[2];

  Q->mul(&tmp, &qDot);
  qDot *= 0.5f;
  step *= *beta;
  qDot -= &step;

  //Integrate to yield quaternion
  //q = q + qDot*obj.dT;
  //obj.Q = q/norm(q); % normalise quaternion
  qDot *= dT;
  *Q += &qDot;
  Q->normalize();

  //delta_wb = 2*obj.Zeta*obj.dT * quatmult(quatcon(q), step);
  Q->ccon(&qcon);
  qcon.mul(&step, &tmp);
  tmp *= *zeta * 2 * dT;

  //Wb = wb+delta_wb(2:4);
  Wb(0) = tmp(1);
  Wb(1) = tmp(2);
  Wb(2) = tmp(3);
}

/**
 *
 */
void MadgwickAHRS::start(void){
  beta = (const float*)param_registry.valueSearch("IMU_beta");
  zeta = (const float*)param_registry.valueSearch("IMU_zeta");

  ready = true;
}
