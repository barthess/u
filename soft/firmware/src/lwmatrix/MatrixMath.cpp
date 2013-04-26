/**
 * @brief  version 0.9
 * @file   MatrixMath.cpp
 * @author Ernesto Palacios
 *
 * Created on 15 de septiembre de 2011, 09:44 AM.
 *
 * Develop Under  GPL v3.0 License
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#include "mbed.h"
#include "MatrixMath.h"

///Transpose matrix
Matrix MatrixMath::Transpose(const Matrix& Mat)
{
    Matrix result( Mat._nCols, Mat._nRows ); //Transpose Matrix

    for( int i = 0; i < result._nRows; i++ )
        for( int j = 0; j < result._nCols; j++ )
            result._matrix[i][j] = Mat._matrix[j][i];

    return result;
}

Matrix MatrixMath::Inv(const Matrix& Mat)
{
    if( Mat._nRows == Mat._nCols )
    {
        if( Mat._nRows == 2 )   // 2x2 Matrices
        {
            float det = MatrixMath::det( Mat );
            if( det != 0 )
            {
                Matrix Inv(2,2);
                Inv._matrix[0][0] =  Mat._matrix[1][1];
                Inv._matrix[1][0] = -Mat._matrix[1][0];
                Inv._matrix[0][1] = -Mat._matrix[0][1];
                Inv._matrix[1][1] =  Mat._matrix[0][0] ;

                Inv *= 1/det;

                return Inv;

            }else{
                printf( "\n\nWANRING: same matrix returned");
                printf( "\nSingular Matrix, cannot perform Invert @matrix\n " );
                Mat.print();
                printf( "\n  _____________\n" );

                return Mat;
            }

        }else{   // nxn Matrices

            float det = MatrixMath::det( Mat );
            if( det!= 0 )
            {
                Matrix Inv( Mat ); //
                Matrix SubMat;

                // Matrix of Co-factors
                for( int i = 0; i < Mat._nRows; i++ )
                    for( int j = 0; j < Mat._nCols; j++ )
                    {
                        SubMat = Mat ;

                        Matrix::DeleteRow( SubMat, i+1 );
                        Matrix::DeleteCol( SubMat, j+1 );

                        if( (i+j)%2 == 0 )
                            Inv._matrix[i][j] = MatrixMath::det( SubMat );
                        else
                            Inv._matrix[i][j] = -MatrixMath::det( SubMat );
                    }

                // Adjugate Matrix
                Inv = MatrixMath::Transpose( Inv );

                // Inverse Matrix
                Inv = 1/det * Inv;

                return Inv;

            }else{
                printf( "\n\nWANRING: same matrix returned");
                printf( "\nSingular Matrix, cannot perform Invert @matrix\n" );
                Mat.print();
                printf( "\n  _____________\n" );

                return Mat;
            }

        }

    }else{
        printf( "\n\nERROR:\nMust be square Matrix @ MatrixMath::Determinant\n" );
    }
}

Matrix MatrixMath::Eye( int Rows )
{
    Matrix Identity( Rows, Rows ); //Square Matrix

    for( int i = 0; i < Rows; i++ )
        Identity._matrix[i][i] = 1;

    return Identity;
}

// Very Versitle Function. Accepts two Vector Matrices of any type:
// Vector types may be: [n,1] dot [n,1]  
//                      [n,1] dot [1,n]  always same
//                      [1,n] dot [n,1]    'depth'
//                      [1,n] dot [1,n]
float MatrixMath::dot(const Matrix& leftM, const Matrix& rightM)
{
    if( leftM.isVector() && rightM.isVector() )
    {
        if( leftM._nRows == 1 )
        {
            if( rightM._nRows == 1 )
            {
                if( leftM._nCols == rightM._nCols )
                {
                    // Calculate ( 1,n )( 1,n )
                    float dotP;
                    Matrix Cross;

                    Cross = leftM * MatrixMath::Transpose( rightM );
                    dotP = Cross.sum();

                    return dotP;

                }else{
                    printf( "\n\nERROR:\n Matrices have diferent depths @ MatrixMath::dot()\n" );
                }

            }else{
                if( leftM._nCols == rightM._nRows )
                {
                    // Calculate (1, n)( n, 1 )
                    float dotP;
                    Matrix Cross;

                    Cross = leftM * rightM;
                    dotP = Cross.sum();

                    return dotP;

                }else{
                    printf( "\n\nERROR:\n Matrices have diferent depths @ MatrixMath::dot()\n" );
                }
            }

        }else{
            if( rightM._nRows == 1 )
            {
                if( leftM._nRows == rightM._nCols )
                {
                    // Calculate ( n,1 )( 1,n )
                    float dotP;
                    Matrix Cross;

                    Cross = MatrixMath::Transpose(leftM)  * MatrixMath::Transpose(rightM);
                    dotP = Cross.sum();

                    return dotP;

                }else{
                    printf( "\n\nERROR:\n Matrices have diferent depths @ MatrixMath::dot()\n" );
                }

            }else{
                if( leftM._nRows == rightM._nRows )
                {
                    // Calculate (n, 1)( n, 1 )
                    float dotP;
                    Matrix Cross;

                    Cross = MatrixMath::Transpose(leftM) *  rightM ;
                    dotP = Cross.sum();

                    return dotP;

                }else{
                    printf( "\n\nERROR:\n Matrices have diferent depths @ MatrixMath::dot()\n" );
                }
            }
        }

    }else{
        printf( "\n\nERROR:\n Matrix is not a Vector @ MatrixMath::dot()\n" );
    }
}


float MatrixMath::det(const Matrix& Mat)
{
    if( Mat._nRows == Mat._nCols  )
    {

        if( Mat._nRows == 2 )  // 2x2 Matrix
        {
            float det;
            det = Mat._matrix[0][0] * Mat._matrix[1][1] -
                    Mat._matrix[1][0] * Mat._matrix[0][1];
            return det;
        }
        else if( Mat._nRows == 3 ) // 3x3 Matrix
        {
            float det;
            MatrixMath dummy; //For Private Method.

            det = dummy.Det3x3( Mat );
            return det;

        } else {

            float part1= 0;
            float part2= 0;

            //Find +/- on First Row
            for( int i = 0; i < Mat._nCols; i++)
            {
                Matrix reduced( Mat );           // Copy Original Matrix
                Matrix::DeleteRow( reduced, 1); // Delete First Row

                if( i%2 == 0 ) //Even Rows
                {

                    Matrix::DeleteCol( reduced, i+1);
                    part1 += Mat._matrix[0][i] * MatrixMath::det(reduced);
                }
                else  // Odd Rows
                {
                    Matrix::DeleteCol( reduced, i+1);
                    part2 += Mat._matrix[0][i] * MatrixMath::det(reduced);
                }
            }
            return part1 - part2; 
        }

    }else{
        printf("\n\nERROR:\nMatrix must be square Matrix @ MatrixMath::det");
    }
}


/************************************/

//Private Functions

/**@brief
 * Expands the Matrix adding first and second column to the Matrix then
 * performs the Algorithm.
 * @param Mat
 * @return Determinant
 */
float MatrixMath::Det3x3(const Matrix& Mat)
{
    Matrix D( Mat );  //Copy Initial matrix

    Matrix::AddCol(D, Matrix::ExportCol(Mat, 1), 4); //Repeat First Column
    Matrix::AddCol(D, Matrix::ExportCol(Mat, 2), 5); //Repeat Second Column

    float det = 0;
    for( int i = 0; i < 3; i++ )
        det += D._matrix[0][i] * D._matrix[1][1+i] * D._matrix[2][2+i]
                - D._matrix[0][2+i] * D._matrix[1][1+i] * D._matrix[2][i];

    return det;
}