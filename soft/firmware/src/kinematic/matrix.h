#ifndef MATRIX_H
#define MATRIX_H

//transpose matrix A (m x n)  to  B (n x m)
void matrix_transpose(int m , int n, float* A,  float* B){
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			B[j*m+i] = A[i*n+j];
}

//multiply matrix A (m x p) by  B(p x n) , put result in C (m x n)
void matrix_multiply( int m, int p, int n , float *A, float *B,  float *C){
	int i,j,k;
	for(i=0;i<m;i++)		//each row in A
		for(j=0;j<n;j++){	//each column in B
			C[i*n+j] = 0;
			for(k=0;k<p;k++){//each element in row A & column B
				C[i*n+j] += A[i*p+k]*B[k*n+j];
				//printf("i=%d j=%d k=%d a=%f b=%f c=%f ",i,j,k,(double)(A[i*p+k]),(double)(B[k*n+j]),(double)(C[i*n+j]));
			}
			//printf("\n");
		}
};


void matrix_copy(int m, int n, float* A, float* B ){
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			B[i*n+j] = A[i*n+j];	
}

//print a Matrix
void matrix_print(int m, int n, float* A){
	int i,j;
	for(i=0;i<m;i++){
		printf("{");
		for(j=0;j<n;j++){
			if(j>0) printf(",");
			printf("%f", (double)(A[i*n+j]));
		}
		printf("},\n");
	}
}


// Matrix Inversion Routine from http://www.arduino.cc/playground/Code/MatrixMath
// * This function inverts a matrix based on the Gauss Jordan method.
// * Specifically, it uses partial pivoting to improve numeric stability.
// * The algorithm is drawn from those presented in 
//	 NUMERICAL RECIPES: The Art of Scientific Computing.
// * The function returns 1 on success, 0 on failure.
// * NOTE: The argument is ALSO the result matrix, meaning the input matrix is REPLACED
int matrix_inverse(int n, float* A)
{
	// A = input matrix AND result matrix
	// n = number of rows = number of columns in A (n x n)
	int pivrow;		// keeps track of current pivot row
	int k,i,j;		// k: overall index along diagonal; i: row index; j: col index
	int pivrows[n]; // keeps track of rows swaps to undo at end
	float tmp;		// used for finding max value and making column swaps
	
	for (k = 0; k < n; k++)
	{
		// find pivot row, the row with biggest entry in current column
		tmp = 0;
		for (i = k; i < n; i++)
		{
			if (fabs(A[i*n+k]) >= tmp)	// 'Avoid using other functions inside abs()?'
			{
				tmp = fabs(A[i*n+k]);
				pivrow = i;
			}
		}
		
		// check for singular matrix
		if (A[pivrow*n+k] == 0.0f)
		{
			//Inversion failed due to singular matrix
			return 0;
		}
		
		// Execute pivot (row swap) if needed
		if (pivrow != k)
		{
			// swap row k with pivrow
			for (j = 0; j < n; j++)
			{
				tmp = A[k*n+j];
				A[k*n+j] = A[pivrow*n+j];
				A[pivrow*n+j] = tmp;
			}
		}
		pivrows[k] = pivrow;	// record row swap (even if no swap happened)
		
		tmp = 1.0f/A[k*n+k];	// invert pivot element
		A[k*n+k] = 1.0f;		// This element of input matrix becomes result matrix
		
		// Perform row reduction (divide every element by pivot)
		for (j = 0; j < n; j++)
		{
			A[k*n+j] = A[k*n+j]*tmp;
		}
		
		// Now eliminate all other entries in this column
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				tmp = A[i*n+k];
				A[i*n+k] = 0.0f;  // The other place where in matrix becomes result mat
				for (j = 0; j < n; j++)
				{
					A[i*n+j] = A[i*n+j] - A[k*n+j]*tmp;
				}
			}
		}
	}
	
	// Done, now need to undo pivot row swaps by doing column swaps in reverse order
	for (k = n-1; k >= 0; k--)
	{
		if (pivrows[k] != k)
		{
			for (i = 0; i < n; i++)
			{
				tmp = A[i*n+k];
				A[i*n+k] = A[i*n+pivrows[k]];
				A[i*n+pivrows[k]] = tmp;
			}
		}
	}
	return 1;
}


#endif
