#include "matrix.hpp"

static const float Minit[9] = {0,1,0, 1,0,0, 0,0,1};
static const float Ninit[3] = {2,3,4};
static MatrixBuf<float, 3, 3> M(Minit);
static MatrixBuf<float, 3, 1> N(Ninit);
static MatrixBuf<float, 3, 1> X;
static MatrixBuf<float, 1, 1> C;

float matrix_test(void){
  MatrixBuf<float, 3, 3> Y;
  mul(&M, &N, &X);
  X.set(0,0,23);
  N.normalize();

  Y = M;
  Y.inverse();

  //return dot(&N, &X);
  //return sizeof(X);//.get(0,0);
  return sizeof(C);
}



