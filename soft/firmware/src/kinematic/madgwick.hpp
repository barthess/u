//=====================================================================================================
// MadgwickAHRS.h
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=====================================================================================================
#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h
#include <stdint.h>

//----------------------------------------------------------------------------------------------------
// Variable declaration

//extern volatile float beta;				// algorithm gain
//extern volatile float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame

//---------------------------------------------------------------------------------------------------
// Function declarations

//#ifdef __cplusplus
//extern "C" {
//#endif
void MadgwickAHRSupdate(float gx, float gy, float gz,
                        float ax, float ay, float az,
                        float mx, float my, float mz,
                        float *res, float beta, float zeta, uint32_t reset);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz,
                           float ax, float ay, float az, float beta);
//#ifdef __cplusplus
//}
//#endif


//#include <stdint.h>
//
//template<typename T, int32_t row, int32_t col>
//class Matrix{
//public:
//  Matrix(void);
//private:
//  float _m[row*col];
//  int32_t r;
//  int32_t c;
//};
//
//class Vector3d{
//public:
//  Vector3d(void);
//  Vector3d(float v0, float v1, float v2);
//  void normalize(void);
//private:
//  float v[3];
//};
//
//
//class MyAHRS{
//public:
//  MyAHRS(void);
//  void update(float *g, float *a, float *m);
//};





#endif
//=====================================================================================================
// End of file
//=====================================================================================================
