#ifndef MISC_MATH2_H_
#define MISC_MATH2_H_


template<typename Type>
Type putinrange(Type v, Type vmin, Type vmax){

  Type tmp;

  /* protection from stupidity */
  if(vmin >= vmax){
    tmp = vmax;
    vmax = vmin;
    vmin = tmp;
  }

  /* brute comparison */
  if (v <= vmin)
    return vmin;
  else if (v >= vmax)
    return vmax;
  else
    return v;
}

/**
 * Sort vector of 3 values according to sorting matrix
 * |0 1 0|   |v0|
 * |1 0 0| x |v1| = |v1 v0 v2|
 * |0 0 1|   |v2|
 * using matrix multiplication formulae this operation requires
 * 9 multiplies and 6 additions. We can replace this by switch-case logic
 *
 * all possible combinations:
 * 1 2 3 4 5 6
 * -----------
 * 0 1 0 1 2 2
 * 1 0 2 2 1 0
 * 2 2 1 0 0 1
 */
template <typename T>
void sort3(T *in, T *out, uint32_t sortmatrix){
  switch (sortmatrix){
  case 0b001100010: // #6
    //   001
    //   100
    //   010
    out[0] = in[2];
    out[1] = in[0];
    out[2] = in[1];
    break;
  case 0b001010100: // #5
    //   001
    //   010
    //   100
    out[0] = in[2];
    out[1] = in[1];
    out[2] = in[0];
    break;
  case 0b010001100: // #4
    //   010
    //   001
    //   100
    out[0] = in[1];
    out[1] = in[2];
    out[2] = in[0];
    break;
  case 0b100001010: // #3
    //   100
    //   001
    //   010
    out[0] = in[0];
    out[1] = in[2];
    out[2] = in[1];
    break;
  case 0b010100001: // #2
    //   010
    //   100
    //   001
    out[0] = in[1];
    out[1] = in[0];
    out[2] = in[2];
    break;
  case 0b100010001: // #1
    //   100
    //   010
    //   001
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    break;
  default:
    chDbgPanic("bad sorting matrix");
    break;
  }
}

uint32_t pack8to32(uint8_t *buf);
uint16_t pack8to16(uint8_t *buf);
int16_t complement2signed(uint8_t msb, uint8_t lsb);
uint32_t sqrti(uint32_t x);
int32_t powi(int32_t base, uint32_t exp);

#endif /* MISC_MATH2_H_ */
