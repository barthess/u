#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

void matrix_transposef(const uint32_t m , const uint32_t n, const float* A,  float* B);
void matrix_multiplyf(const uint32_t m, const uint32_t p, const uint32_t n , const float *A, const float *B,  float *C);
void matrix_copyf(const uint32_t m, const uint32_t n, const float* A, float* B );

void matrix_transpose(const uint32_t m , const uint32_t n, const double* A,  double* B);
void matrix_multiply(const uint32_t m, const uint32_t p, const uint32_t n , const double *A, const double *B,  double *C);
void matrix_copy(const uint32_t m, const uint32_t n, const double* A, double* B );

#endif
