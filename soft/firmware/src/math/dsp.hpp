#ifndef DSP_H_
#define DSP_H_

typedef int32_t q31_t;
typedef q31_t alphabeta_instance_q31;
typedef float alphabeta_instance_float;

q31_t alphabeta_q31(alphabeta_instance_q31 *S, q31_t val, uint32_t len);
float alphabeta_float(alphabeta_instance_float *S, float val, uint32_t len);

uint32_t median_filter_5(uint32_t *buf, uint32_t sample);
uint32_t median_filter_3(uint32_t *buf, uint32_t sample);


template<typename T>
class AlphaBeta{
public:
  T update(T val, int32_t len);
  void reset(T val, int32_t len);
private:
  T S;
};

template<typename T>
T AlphaBeta<T>::update(T val, int32_t len){
  T tmp = S / len;
  S = S - tmp + val;
  return tmp;
}

template<typename T>
void AlphaBeta<T>::reset(T val, int32_t len){
  S = val * len;
}

#endif /* DSP_H_ */
