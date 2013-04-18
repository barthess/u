#ifndef MISC_H_
#define MISC_H_

#define putinrange(v, vmin, vmax){                                            \
  chDbgCheck(vmin <= vmax, "");                                               \
  if (v <= vmin)                                                              \
    v = vmin;                                                                 \
  else if (v >= vmax)                                                         \
    v = vmax;                                                                 \
}

uint32_t pack8to32(uint8_t *buf);
uint16_t pack8to16(uint8_t *buf);

int32_t Simpson(int32_t a, int32_t b, int32_t c, int32_t t);
int32_t Simpson38(int32_t a, int32_t b, int32_t c, int32_t d, int32_t t);

int16_t complement2signed(uint8_t msb, uint8_t lsb);

uint32_t sqrti(uint32_t x);
int32_t powi(int32_t base, uint32_t exp);

void sortf_3values(float *in, float *out, uint32_t sortmatrix);
void sortu_3values(uint32_t *in, uint32_t *out, uint32_t sortmatrix);
void sorti_3values(int32_t *in, int32_t *out, uint32_t sortmatrix);

#endif /* MISC_H_ */
