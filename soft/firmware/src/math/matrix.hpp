#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <math.h>

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

// Same as previouse but B is matrix of pointers to values
template <typename T>
void matrix_multiply(const uint32_t m, const uint32_t p, const uint32_t n ,
                     const T *A, const T **B, T *C){
  uint32_t i, j, k;
  for(i=0; i<m; i++){     //each row in A
    for(j=0; j<n; j++){   //each column in B
      C[i*n + j] = 0;
      for(k=0; k<p; k++){ //each element in row A & column B
        C[i*n + j] += A[i*p + k] * *(B[k*n + j]);
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

// Matrix Inversion Routine from http://www.arduino.cc/playground/Code/MatrixMath
// * This function inverts a matrix based on the Gauss Jordan method.
// * Specifically, it uses partial pivoting to improve numeric stability.
// * The algorithm is drawn from those presented in
//   NUMERICAL RECIPES: The Art of Scientific Computing.
// * The function returns 1 on success, 0 on failure.
// * NOTE: The argument is ALSO the result matrix, meaning the input matrix is REPLACED
template <typename T>
int32_t matrix_inverse(int32_t n, T *A)
{
  // A = input matrix AND result matrix
  // n = number of rows = number of columns in A (n x n)
  int32_t pivrow = 0; // keeps track of current pivot row
  int32_t k,i,j;      // k: overall index along diagonal; i: row index; j: col index
  int32_t pivrows[n]; // keeps track of rows swaps to undo at end
  T tmp;    // used for finding max value and making column swaps

  for (k = 0; k < n; k++){
    // find pivot row, the row with biggest entry in current column
    tmp = 0;
    for (i = k; i < n; i++){
      if ((T)fabs(A[i*n+k]) >= tmp){ // 'Avoid using other functions inside abs()?'
        tmp = (T)fabs(A[i*n+k]);
        pivrow = i;
      }
    }

    // check for singular matrix
    if (A[pivrow*n+k] == (T)0.0)
      return 0; //Inversion failed due to singular matrix

    // Execute pivot (row swap) if needed
    if (pivrow != k) {
      for (j = 0; j < n; j++) {// swap row k with pivrow
        tmp = A[k*n+j];
        A[k*n+j] = A[pivrow*n+j];
        A[pivrow*n+j] = tmp;
      }
    }
    pivrows[k] = pivrow;  // record row swap (even if no swap happened)

    tmp = (T)1.0 / A[k*n+k];  // invert pivot element
    A[k*n+k] = (T)1.0;    // This element of input matrix becomes result matrix

    // Perform row reduction (divide every element by pivot)
    for (j = 0; j < n; j++)
      A[k*n+j] = A[k*n+j]*tmp;

    // Now eliminate all other entries in this column
    for (i = 0; i < n; i++){
      if (i != k){
        tmp = A[i*n+k];
        A[i*n+k] = (T)0.0;  // The other place where in matrix becomes result mat
        for (j = 0; j < n; j++)
          A[i*n+j] = A[i*n+j] - A[k*n+j]*tmp;
      }
    }
  }

  // Done, now need to undo pivot row swaps by doing column swaps in reverse order
  for (k = n-1; k >= 0; k--){
    if (pivrows[k] != k){
      for (i = 0; i < n; i++){
        tmp = A[i*n+k];
        A[i*n+k] = A[i*n+pivrows[k]];
        A[i*n+pivrows[k]] = tmp;
      }
    }
  }
  return 1;
}

#endif
