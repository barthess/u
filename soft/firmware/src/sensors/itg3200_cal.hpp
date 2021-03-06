#ifndef ITG3200_CAL_HPP_
#define ITG3200_CAL_HPP_

#include "dsp.hpp"


enum itg3200_cal_state{
  ITG3200_CAL_UNINIT,
  ITG3200_CAL_SLEEP,
  ITG3200_CAL_COLLECTING,
};


class ITG3200calibrator{
public:
  ITG3200calibrator(void);
  void start(void);
  void update(const int32_t *raw, uint32_t still_msk);
  bool trig(void);
  void abort(void);
  bool isCalibrating(void);

private:
  void reset_stats(void);
  int32_t sample;
  AlphaBeta<float> abeta[3];
  itg3200_cal_state state;
  int32_t  const *zeroflen,  *zerocnt;
};


#endif /* ITG3200_CAL_HPP_ */
