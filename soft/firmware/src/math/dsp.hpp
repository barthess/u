#ifndef DSP_H_
#define DSP_H_


uint32_t median_filter_5(uint32_t *buf, uint32_t sample);
uint32_t median_filter_3(uint32_t *buf, uint32_t sample);


template<typename T>
class AlphaBeta{
public:
  T update(T val, int32_t len);
  T get(int32_t len);
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
T AlphaBeta<T>::get(int32_t len){
  return S / len;
}

template<typename T>
void AlphaBeta<T>::reset(T val, int32_t len){
  S = val * len;
}

#endif /* DSP_H_ */
