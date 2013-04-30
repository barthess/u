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


#include "quaternion.hpp"

class MyAHRS{
public:
  void update(const float *gyro, const float *acc, const float *mag,
      Quaternion<float> *result, const float interval);
};




#endif
//=====================================================================================================
// End of file
//=====================================================================================================
