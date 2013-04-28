#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <math.h>

/*
 ******************************************************************************
 * LOW LEVEL
 * Hi speed functions without size checks
 ******************************************************************************
 */
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

// Same as previouse but A is matrix of pointers to values
template <typename T>
void matrix_multiply(const uint32_t m, const uint32_t p, const uint32_t n ,
                     const T **A, const T *B, T *C){
  uint32_t i, j, k;
  for(i=0; i<m; i++){     //each row in A
    for(j=0; j<n; j++){   //each column in B
      C[i*n + j] = 0;
      for(k=0; k<p; k++){ //each element in row A & column B
        C[i*n + j] += *A[i*p + k] * B[k*n + j];
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

/*
 ******************************************************************************
 * HI LEVEL
 * Classes performing size checks
 ******************************************************************************
 */
#include "uav.h"

/**
 * Main matrix class
 */
template<typename T>
class Matrix{
public:
  /**
   * default constructor
   */
  Matrix(T *m, uint32_t r, uint32_t c, size_t bufsize){
    chDbgCheck(((0 != r) && (0 != c)), "Zero sizes forbidden");
    chDbgCheck(bufsize == (r * c * sizeof(T)), "Probable overflow");
    this->m = m;
    this->col = c;
    this->row = r;
  };

  /**
   * Set single matrix element
   */
  void set(uint32_t r, uint32_t c, T v){
    this->m[c*r] = v;
  };

  /**
   * Return single matrix element
   */
  T get(uint32_t r, uint32_t c){
    return this->m[c*r];
  };

  /**
   * Return pointer to raw matrix data
   */
  T *getRaw(void){
    return this->m;
  };

  /**
   * Initialize matrix using vector of values starting from 0th element
   */
  void set(const T *v){
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++)
      this->m[i] = v[i];
  };

  /**
   * Initialize matrix using pattern
   */
  void set(T v){
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++)
      this->m[i] = v;
  };

  /**
   * Scale matrix elemets by constant
   */
  void scale(T v){
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++)
      this->m[i] *= v;
  };

  /**
   * Modulus
   */
  T modulus(void){
    T R = 0;
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++)
      R += this->m[i] * this->m[i];
    return sqrt(R);
  }

  /**
   * normalize
   */
  void normalize(void){
    T R = this->modulus();
    chDbgCheck((R > 0), "divizion by zero");
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++)
      this->m[i] /= R;
  };

  /**
   * Invers matrix itself
   */
  int32_t inverse(){
    chDbgCheck(this->col == this->row, "matrix must be square");
    return matrix_inverse(this->col, this->m);
  };

public:
  uint32_t row;
  uint32_t col;
  T *m;
};

/**
 * Class representing a static buffer for matrix
 */
template<typename T, int r, int c>
class MatrixBuf : public Matrix<T>{
private:
   T m[r*c];

public:
  MatrixBuf(void) :
    Matrix<T>(m, r, c, sizeof(m))
  {
    for (uint32_t i=0; i<(c*r); i++)
      m[i] = 0;
  };

  MatrixBuf(const T *initvector) :
    Matrix<T>(m, r, c, sizeof(m))
  {
    for (uint32_t i=0; i<(c*r); i++)
      m[i] = initvector[i];
  };

  MatrixBuf(T pattern) :
    Matrix<T>(m, r, c, sizeof(m))
  {
    for (uint32_t i=0; i<(c*r); i++)
      m[i] = pattern;
  };
};

/*
 ******************************************************************************
 * STATIC METHODS
 * Fucntions working with classes instances
 ******************************************************************************
 */

/**
 * Matrix multiplication
 */
template<typename T>
static void mul(Matrix<T> *left, Matrix<T> *right, Matrix<T> *result){
  chDbgCheck(((left->col == right->row) &&
              (result->row == left->row) &&
              (result->col == right->col)), "sizes inconsistent");

  matrix_multiply(left->row, left->col, right->col,
                  left->m, right->m, result->m);
}

/**
 * Dot product of 2 vectors
 */
template<typename T>
static T dot(Matrix<T> *left, Matrix<T> *right){
  MatrixBuf<T, 1, 1> result;
  mul(left, right, &result);
  return result.get(0,0);
}

/**
 * cross product in right handed 3-d space
 */
template<typename T>
static void cross(Matrix<T> *left, Matrix<T> *right, Matrix<T> *result){
  chDbgCheck((
      (1 == left->col) && (1 == right->col) && (1 == result->col) &&
      (3 == left->row) && (3 == right->row) && (3 == result->row)),
      "sizes inconsistent");

  result->m[0] = left->m[1]*right->m[2] - left->m[2]*right->m[1];
  result->m[1] = left->m[2]*right->m[0] - left->m[0]*right->m[2];
  result->m[2] = left->m[0]*right->m[1] - left->m[1]*right->m[0];
}

#endif /* MATRIX_H */
