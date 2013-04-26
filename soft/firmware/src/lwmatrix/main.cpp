/* 
 * File:   main.cpp
 * Author: ernesto
 *
 * Created on 20 de septiembre de 2011, 11:04 AM
 */

//#include <cstdlib>
#include "Matrix.h"
#include "MatrixMath.h"


int main(int argc, char** argv) {

/*

//---
    Matrix myMatrix(3,3);
    Matrix anotherMatrix;

    // Fill Matrix with data.
    myMatrix << 1  << 2  << 3
             << 4  << 5  << 6
             << 7  << 8  << 9;

    printf( "\nmyMatrix \n");
    myMatrix.print();
    printf( "\n" );

    
    // Matrix operations //

    // Add 5 to negative Matrix 
    anotherMatrix = - myMatrix + 5;

    printf( "Result Matrix: anotherMatrix = - myMatrix + 5\n" );
    anotherMatrix.print();
    printf( "\n" );
    
    // Matrix Multiplication *
    anotherMatrix *=  myMatrix;

    printf( "anotherMatrix = anotherMatrix * myMatrix\n" );
    anotherMatrix.print();
    printf( "\n" );
    
    // Scalar Matrix Multiplication anotherMatrix *= 0.5
    anotherMatrix *= 0.5;

    printf( "Result Matrix *= 0.5:\n" );
    anotherMatrix.print();
    printf( "    _______________________________ \n" );


    printf("** MEMBER OPERATIONS ** \n\n");

    //Copy myMatrix
    Matrix temp( myMatrix );

    // Resize Matrix
    temp.Resize(4,4);
    printf("\nAdded one Column, one Row to the limitsof myMatrix saved in temp Matrix\n");
    temp.print();

    //Delete those new elements, we don't need them anyway.
    Matrix::DeleteRow( temp, 4 );
    Matrix::DeleteCol( temp, 4 );

    printf("\nBack to normal\n");
    temp.print();

    
    // Make room at the begining of Matrix
    Matrix::AddRow( temp, 1 );
    Matrix::AddCol( temp, 1 );
    
    printf("\nAdded Just one Row and column to the beginning\n");
    temp.print();

    // Take the second Row as a New Matrix
    anotherMatrix = Matrix::ExportRow( temp, 2 );
    printf("\nExport Second Row \n");
    anotherMatrix.print();

    // The second Column as a ner Matrix, then transpose it to make it a Row
    anotherMatrix = Matrix::ExportCol( temp, 2 );
    anotherMatrix = MatrixMath::Transpose( anotherMatrix );
    printf("\nAnd Export Second Column and Transpose it \n");
    anotherMatrix.print();

    // This will Check to see if your are reduce to a single Row or Column
    temp = Matrix::ToPackedVector( myMatrix );
    printf("\nInitial Matrix turned into a single Row\n");
    temp.print();
           
    //  Matrix Math  //
    printf("\n Matrix Inverse and Determinant\n");
    
    Matrix BigMat( 5, 5 );
    BigMat   << 1 << 0  << 1 << 1 << 3
             << 2 << 3  << 4 << 0 << 4
             << 1 << 6  << 1 << 1 << 2
             << 1 << 0  << 2 << 1 << 1
             << 2 << 3  << 4 << 2 << 0;

    printf( "\nBigMat:\n");
    BigMat.print();
    printf( "\n" );

    float determ = MatrixMath::det( BigMat );

    printf( "\nBigMat's Determinant is: %f \n", determ);
    printf( "\n" );

    Matrix myInv = MatrixMath::Inv( BigMat );

    printf( "\nBigMat's Inverse is:\n");
    myInv.print();
    printf( "\n" );

//---

    Matrix rot;

    printf( " RotX  0.5 rad \n" );
    rot = MatrixMath::RotX(0.5);
    rot.print();
    printf( "    _______________________________ \n\n" );

    printf( " RotY  0.5 rad \n" );
    rot = MatrixMath::RotY(0.5);
    rot.print();
    printf( "    _______________________________ \n\n" );

    printf( " RotZ  0.5 rad \n" );
    rot = MatrixMath::RotZ(0.5);
    rot.print();
    printf( "    _______________________________ \n\n" );

    printf( " Transl  5x 3y 4z rad \n" );
    rot = MatrixMath::Transl( 5, 3, 4 );
    rot.print();
    printf( "    _______________________________ \n\n" );

 *
 */
    Matrix vect1 ( 3, 1 );
    Matrix vect2 ( 3, 1 );
    float ans;

    vect1 << 1 << 2 << 3;
    vect2 << 4 << 5 << 6;

    vect1(2,1) = vect2( 2,1);

    printf( "\n" );
    vect1.print();
    printf( "\n" );
    vect2.print();
    printf( "\n" );

    ans = MatrixMath::dot( vect1, vect2 );

    printf( "Dot Product = %f \n", ans );

    return 0;
}

