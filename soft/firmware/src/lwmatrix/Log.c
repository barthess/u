/**  
 * @brief  Keep track of changes since version 1.6             e-mail: mecatronica.mid@gmail.com
 * @file   Log.c
 * @author Ernesto Palacios
 */
 
/*    
1.6.4.0    30/10/2011
           -->> MATRIX_H
            *  Eliminated namespace std; already included in mbed.h
            *  Operator Overloaded (). For assignment and getValue.
            *  Almost all operators declared as friend functions.

            -->> MATRIXMATH_H
            *  Added Function Eye(). Creates an identity Matrix of specified dimensions.
            *  Added Function dotProduct(). to find the dot product of two vectors.
               -->> You need to pass two Vector Matrices of any dimmensions.
                    They could be in the form: A( 1,n ) B( 1,n )
                                               A( n,1 ) B( 1,n )
                                               A( n,1 ) B( n,1 )
                                               A( 1,n ) B( n,1 )
                    As long as have same 'depth' and are vectors, the dot product.
                    will be returned.

            -->> MATRIXMATH_Kinematics.cpp
            *  Created file MatrixMath_Kinematics.cpp To Hold the definitions of
               kinematic operations.

            *  Define Functions RotX, RotY, RotZ, Transl. for Matrix Transformation
               operations.


1.6.2.0     22/10/2011
            -->> MATRIX_H
            *  Changed static member Matrix::AddColumn( ... )  -> Matrix::AddCol( ... )
            *  Overload AddCol/AddRow, it now can accept SingleCol/ SingleRow as arguments.
               Still works the same for inserting new Col/Row. Usage:

               Matrix::AddRow( myMatrix, 3 );  // Inserts an empty col at index 3 of myMatrix

               Matrix::AddCol( myMatrix, SingleCol, 3 ); // Inserts a SingleCol Matrix into index 3 of myMarix

            -->> MATRIXMATH_H
            *  float det = MatrixMath::det( myMatrix );
               Returns the determinant of any nxn Matrix.

            *  Matrix Inv = MatrixMath::Inv( myMatrix )
               Returns the determinant of any nxn Matrix, if it's not a Singular matrix


               WARNING: If it is a Singular Matrix it will return the same Matrix.
                        A singular Matrix is one whose inverse does not exists.

1.6.0.1     21/10/2011
            First class ready to work. but still some rough edges to polish. Better use 1.6.2

1.0         15/09/2011

            First Version.- Buggy and no longer supported.

*/
