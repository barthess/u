#include "matrix.hpp"
#include "newmatrix.hpp"
#include "uav.h"


Matrix::Matrix(float *m, const uint32_t r, const uint32_t c, const size_t bufsize){

  chDbgCheck(bufsize == (r * c * sizeof(m[0])), "Probable overflow");
  this->m = m;
  this->col = c;
  this->row = r;
}

void Matrix::set(uint32_t r, uint32_t c, float v){
  this->m[c*r] = v;
}

void Matrix::set(const float *v){
  for (uint32_t i=0; i<(col*row); i++)
    this->m[i] = v[i];
}

void Matrix::zero(void){
  for (uint32_t i=0; i<(col*row); i++)
    this->m[i] = 0;
}

static void mul(Matrix *left, Matrix *right, Matrix *result){
  chDbgCheck(((left->col == right->row) &&
              (result->row == left->row) &&
              (result->col == right->col)), "sizes inconsistent");

  matrix_multiply(left->row, left->col, right->col,
                  left->m, right->m, result->m);
}

static const float Minit[9] = {0,1,0, 1,0,0, 0,0,1};
static const float Ninit[3] = {2,3,4};
static MatrixBuf<3, 3> M(Minit);
static MatrixBuf<3, 1> N(Ninit);
static MatrixBuf<3, 1> X;

float matrix_test(void){
  mul(&M, &N, &X);
  //return sizeof(X);//.get(0,0);
  return sizeof(X);
}



