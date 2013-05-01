#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <misc_math.hpp>

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
#include "main.h"

/**
 * Main matrix class
 */
template<typename T>
class Matrix{
public:
  /**
   * @brief Constructor
   *
   * @param[in] m         pointer to a linear array of matrix data
   * @param[in] r         number of rows
   * @param[in] c         number of columns
   * @param[in] bufsize   size of data array in bytes. Need to check correctness
   *                      of sizes
   */
  Matrix(T *m, const uint32_t r, const uint32_t c, const size_t bufsize){
    chDbgCheck(((0 != r) && (0 != c)), "Zero sizes forbidden");
    chDbgCheck(bufsize == (r * c * sizeof(T)), "Probable overflow");
    this->m = m;
    this->col = c;
    this->row = r;
  };

  /**
   * Initialize matrix using vector of values starting from 0th element
   */
  void init(const T *v){
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++)
      this->m[i] = v[i];
  };

  /**
   * Initialize matrix using pattern
   */
  void init(const T pattern){
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++)
      this->m[i] = pattern;
  };

  /**
   * Return pointer to raw matrix data
   */
  T *getArray(void){
    return this->m;
  };

  /**
   * Return pointer to raw matrix data
   */
  uint32_t getCol(void){
    return this->col;
  };

  /**
   * Return pointer to raw matrix data
   */
  uint32_t getRow(void){
    return this->row;
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
   * The function returns 1 on success, 0 on failure.
   */
  int32_t inverse(){
    chDbgCheck(this->col == this->row, "matrix must be square");
    return matrix_inverse(this->col, this->m);
  };

  /**
   * Reshape matrix
   */
  void reshape(const uint32_t r, const uint32_t c){
    chDbgCheck((this->col * this->row) == (c * r), "resulted matrix size differ");
    this->col = c;
    this->row = r;
  };

  /**
   * Trnaspose matrix storing result in different matrix
   */
  void transpose(Matrix *result){
    chDbgCheck(result != this,
        "this functions can not work inplace");

    chDbgCheck((col == result->row) && (row == result->col),
        "matrix sizes incorrect");
    matrix_transpose(col, row, m, result->m);
  };

  /**
   * Transpose inplace
   * Matrix must be square or
   * one of dimensions must be equal to 1
   */
  void transpose(void){
    chDbgCheck((1 == col) || (1 == row) || (row == col),
        "matrix sizes unsupported");

    /* single dimmension vector simly reshaped */
    if((1 == col) || (1 == row)){
      uint32_t tmp = col;
      col = row;
      row = tmp;
    }

    /* square matrix can be transposed element by element */
    else{
      T tmp;
      uint32_t submatrix = 0;
      uint32_t i=0, k=0, p=0;
      for (submatrix=0; submatrix<(row - 1); submatrix++){
        for (i=submatrix+1; i<col; i++){
          k = i + submatrix*col;
          p = i*col + submatrix;
          tmp = m[k];
          m[k] = m[p];
          m[p] = tmp;
        }
      }
    }
  };

  /**
   *
   */
  void operator += (const T v){
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++){
      m[i] += v;
    }
  };

  /**
   *
   */
  void operator += (const Matrix *M){
    chDbgCheck((M->col == col) && (M->row == row), "matrix sizes must be same");
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++){
      m[i] += M->m[i];
    }
  };

  /**
   *
   */
  void operator -= (const T v){
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++){
      m[i] -= v;
    }
  };

  /**
   *
   */
  void operator -= (const Matrix *M){
    chDbgCheck((M->col == col) && (M->row == row), "matrix sizes must be same");
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++){
      m[i] -= M->m[i];
    }
  };

  /**
   * Scale matrix elemets by constant
   */
  void operator *= (const T v){
    uint32_t len = col * row;
    for (uint32_t i=0; i<len; i++)
      this->m[i] *= v;
  };

  /**@brief
   * Subindex for Matrix elements assignation.
   * @param r
   * @param c
   * @return pointer to the element.
   */
  float& operator() (const uint32_t r, const uint32_t c){
    return this->m[calc_subindex(r,c)];
  };

  /**@brief
   * Subindex for Matrix element.
   * @param r
   * @param c
   * @return the element.
   */
  float operator() (const uint32_t r, const uint32_t c) const{
    return this->m[calc_subindex(r,c)];
  };

  /**
   * Matrix multiplication
   */
  void mul(const Matrix<T> *right, Matrix<T> *result){

    chDbgCheck(((this != right) && (this != result) && (result != right)),
                                    "this functions can not work inplace");

    chDbgCheck(((this->col == right->row) &&
                (result->row == this->row) &&
                (result->col == right->col)), "sizes inconsistent");

    matrix_multiply(this->row, this->col, right->col,
                    this->m, right->m, result->m);
  }

private:
  /**
   * @brief calculate subindex from row and col values
   */
  uint32_t calc_subindex(const uint32_t r, const uint32_t c){
    chDbgCheck((c < col) && (r < row), "overflow");
    return r*col + c;
  };

  uint32_t row;
  uint32_t col;
  T *m;
};

/**
 * Convenient class
 * representing matrix with automatically allocated static buffer
 */
template<typename T, int r, int c>
class MatrixBuf : public Matrix<T>{
protected:
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

/**
 * Convenient class
 * 1-d matrix
 */
template<typename T, int N>
class Vector : public Matrix<T>{
protected:
  T m[N];

public:
  Vector(void) :
    Matrix<T>(m, N, 1, sizeof(m))
  {
    for (uint32_t i=0; i<N; i++)
      m[i] = 0;
  };

  Vector(const T *initvector) :
    Matrix<T>(m, N, 1, sizeof(m))
  {
    for (uint32_t i=0; i<N; i++)
      m[i] = initvector[i];
  };

  Vector(T pattern) :
    Matrix<T>(m, N, 1, sizeof(m))
  {
    for (uint32_t i=0; i<N; i++)
      m[i] = pattern;
  };

  /**@brief
   * Subindex for Matrix elements assignation. Single dimension variant.
   * @param v
   * @return pointer to the element.
   */
  float& operator() (const uint32_t v){
    chDbgCheck(v < sizeof(m)/sizeof(m[0]),
        "overflow");
    return this->m[v];
  };

  /**@brief
   * Subindex for Matrix element. Single dimmension variant.
   * @param v
   * @return the element.
   */
  float operator() (const uint32_t v) const{
    chDbgCheck(v < sizeof(m)/sizeof(m[0]),
        "overflow");
    return this->m[v];
  };
};


/**
 * Vector3d.
 * Convenience class. 3 component vector.
 */
template<typename T>
class Vector3d : public Vector<T, 3>{

public:
  Vector3d(void) :
    Vector<T, 3>()
  {
  };

  Vector3d(T m0, T m1, T m2) :
    Vector<T, 3>()
  {
    this->m[0] = m0;
    this->m[1] = m1;
    this->m[2] = m2;
  };

  Vector3d(const T *initvector) :
    Vector<T, 3>(initvector)
  {
  };

  Vector3d(const T pattern) :
    Vector<T, 3>(pattern)
  {
  };

  /**
   * Dot product of 2 vectors
   */
  T dot(Vector3d<T> *right){
    T *a = this->m;
    T *b = right->m;
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  }

  /**
   * cross product in right handed 3-d space
   */
  void cross(Vector3d<T> *right, Vector3d<T> *result){
    T *b = right->m;
    T *res = result->m;
    T *m = this->m;

    chDbgCheck(((b != res) && (b != m) && (res != m)),
        "this functions can not work inplace");

    res[0] = m[1]*b[2] - m[2]*b[1];
    res[1] = m[2]*b[0] - m[0]*b[2];
    res[2] = m[0]*b[1] - m[1]*b[0];
  }
};

#endif /* MATRIX_H */
