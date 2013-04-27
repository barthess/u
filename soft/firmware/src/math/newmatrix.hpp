#ifndef NEWMATRIX_HPP_
#define NEWMATRIX_HPP_
#include <string.h>
#include <stdint.h>


class Matrix{
public:
  Matrix(float *m, uint32_t r, uint32_t c, size_t bufsize);
  void set(uint32_t r, uint32_t c, float v);
  void set(const float *v);
  void zero(void);
  uint32_t row;
  uint32_t col;
  float *m;
};


template<int r, int c>
class MatrixBuf : public Matrix{
private:
  float m[r*c];

public:
  MatrixBuf(void) : Matrix(m, r, c, sizeof(m)){
    for (uint32_t i=0; i<(c*r); i++)
      m[i] = 0;
  };
  MatrixBuf(const float *initvector) : Matrix(m, r, c, sizeof(m)){
    for (uint32_t i=0; i<(c*r); i++)
      m[i] = initvector[i];
  };

};

float matrix_test(void);

#endif /* NEWMATRIX_HPP_ */


