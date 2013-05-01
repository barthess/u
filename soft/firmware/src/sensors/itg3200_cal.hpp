#ifndef ITG3200_CAL_HPP_
#define ITG3200_CAL_HPP_

#include "dsp.hpp"


enum cal_state{
  UNINIT,
  SLEEP,
  COLLECTING,
};


class ITG3200calibrator{
public:
  ITG3200calibrator(void);
  void start(void);
  void update(const int32_t *raw, uint32_t still_msk);
  void trig(void);
  void abort(void);
  bool isCalibrating(void);

private:
  void reset_stats(void);
  int32_t sample;
  AlphaBeta<float> abeta[3];
  cal_state state;
  float          *x_offset,  *y_offset,  *z_offset;
  int32_t  const *zeroflen,  *zerocnt;
};


#endif /* ITG3200_CAL_HPP_ */
