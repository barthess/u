#ifndef LSM303_CAL_HPP_
#define LSM303_CAL_HPP_

#include "dsp.hpp"
#include "sphere.hpp"


enum lsm303_cal_state{
  LSM303_CAL_UNINIT,
  LSM303_CAL_SLEEP,        /* wait command to start collection of very first point */
  LSM303_CAL_COLLECTING,   /* collecting statistics for one of the points */
  LSM303_CAL_WAIT_NEXT,    /* wait trig command to proceed to next poing collecting */
};


class LSM303calibrator{
public:
  LSM303calibrator(void);
  void start(void);
  void update(const float *data, uint32_t still_msk);
  bool trig(void);
  void abort(void);
  bool isCalibrating(void);

private:
  void collecting(const float *data, uint32_t still_msk);
  int32_t sample;
  uint32_t point; /* currently collecting point from 4 ones */
  Sphere S;
  float P[4][3];
  systime_t last_point_timestamp; /* for timeout handling */
  AlphaBeta<float> abeta[3];
  lsm303_cal_state state;
//  float          *x_offset,  *y_offset,  *z_offset;
  int32_t  const *zeroflen,  *zerocnt;
};


#endif /* LSM303_CAL_HPP_ */
