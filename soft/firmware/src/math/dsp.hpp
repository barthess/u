#ifndef DSP_H_
#define DSP_H_

/**
 * Template of alpha-beta filter class
 */
template<typename T>
class AlphaBeta{
public:
  /**
   * default constructor
   */
  AlphaBeta(void){
    S = 0;
  };

  /**
   * Constructor resetting current value to specified one
   */
  AlphaBeta(T val, int32_t len){
    reset(val, len);
  };

  /**
   * Perform addition of new sample to filter and return current filtered
   * result
   */
  T update(T val, int32_t len){
    T tmp = S / len;
    S = S - tmp + val;
    return tmp;
  };

  /**
   * Return current result without updating
   */
  T get(int32_t len){
    return S / len;
  };

  /**
   * Reset filter state
   */
  void reset(T val, int32_t len){
    S = val * len;
  }
private:
  T S;
};

/**
 * Template of median filter
 */
template<typename T, uint32_t N>
class Median{
public:
  /**
   * default constructor
   */
  Median(void){
    /* check correctness of template parameters
     * 1) length must be odd
     * 2) lenght more than 3 is inefficient
     * 3) lenght more than 5 is totally inefficient */
    chDbgCheck(((3 == N) || (5 == N)), "incorrect filter length");

    for(uint32_t i=0; i<N; i++)
      buf[i] = 0;
  };

  /**
   * Update filter state and return filtered value
   */
  T update(T sample){
    uint32_t j = 0, i = 0;
    T tmp;

    /* place new sample in fifo */
    for(j=1; j<N; j++){
      buf[j-1] = buf[j];
    }
    buf[j-1] = sample;

    /* place data in temporal buffer */
    for(j=0; j<N; j++){
      sorted[j] = buf[j];
    }

    /* booble sort */
    for(i=0; i<=(N-1); i++){
      for(j=i+1; j<N; j++){
        if(sorted[i] > sorted[j]){
          tmp = sorted[i];
          sorted[i] = sorted[j];
          sorted[j] = tmp;
        }
      }
    }

    return sorted[N/2]; /* middle of sorted buffer */
  };

private:
  /**
   * Buffer to store filter state between calls
   */
  T buf[N];

  /**
   * Temporal buffer for storing sorted results
   */
  T sorted[N];
};



#endif /* DSP_H_ */
