#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

//transpose matrix A (m x n)  to  B (n x m)
template <typename T>
void matrix_transpose(const uint32_t m , const uint32_t n, const T *A,  T *B){
  uint32_t i, j;
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      B[j*m + i] = A[i*n + j];
}

//multiply matrix A (m x p) by  B(p x n) , put result in C (m x n)
template <typename T>
void matrix_multiply(const uint32_t m, const uint32_t p, const uint32_t n ,
                     const T *A, const T *B, T *C){
  uint32_t i, j, k;
  for(i=0; i<m; i++){     //each row in A
    for(j=0; j<n; j++){   //each column in B
      C[i*n + j] = 0;
      for(k=0; k<p; k++){ //each element in row A & column B
        C[i*n + j] += A[i*p + k] * B[k*n + j];
      }
    }
  }
}

template <typename T>
void matrix_copy(const uint32_t m, const uint32_t n, const T *A, T *B ){
  uint32_t i, j;
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      B[i*n + j] = A[i*n + j];
}

#endif
