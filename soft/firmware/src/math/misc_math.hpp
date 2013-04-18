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


uint32_t pack8to32(uint8_t *buf);
uint16_t pack8to16(uint8_t *buf);
int16_t complement2signed(uint8_t msb, uint8_t lsb);
uint32_t sqrti(uint32_t x);
int32_t powi(int32_t base, uint32_t exp);
void sortf_3values(float *in, float *out, uint32_t sortmatrix);
void sortu_3values(uint32_t *in, uint32_t *out, uint32_t sortmatrix);
void sorti_3values(int32_t *in, int32_t *out, uint32_t sortmatrix);

#endif /* MISC_MATH2_H_ */
