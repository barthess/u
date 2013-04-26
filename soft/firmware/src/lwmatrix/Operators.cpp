/**
 * @brief  Source Code for the Operator of Matrix Class.
 * @file   Operators.cpp
 * @author Ernesto Palacios
 * 
 * Created on September 2011.
 *
 * Develop Under  GPL v3.0 License
 * http://www.gnu.org/licenses/gpl-3.0.html
 * 
 */
#include "mbed.h"
#include "Matrix.h"

/// Subindex in Matrix left side
float& Matrix::operator ()(int row, int col)
{
    --row; --col;

    if( row >= _nRows || col >= _nCols)
    {
        printf("\n\nError:\nOut of limits @ Matrix::operator()\n");
    }else{
        return _matrix[row][col];
    }
}

/// Subindex in Matrix right side
float Matrix::operator ()(int row, int col) const
{
    --row; --col;

    if( row >= _nRows || col >= _nCols)
    {
        printf("\n\nError:\nOut of limits @ Matrix::operator()\n");
    }else{
        return _matrix[row][col];
    }
}


/// Overloaded Asign Operator. Resizes Matrix
Matrix& Matrix::operator = ( const Matrix& rightM )
{
    if (this != &rightM )
    {

         _nRows = rightM._nRows;
         _nCols = rightM._nCols;

         _matrix.resize( rightM._nRows );
         for( int i = 0; i < rightM._nRows; i++ )
             _matrix [i].resize(rightM._nCols);

         for( int i = 0; i < _nRows; i++ )
             for( int j = 0; j < _nCols; j++ )
                 _matrix[i][j] = rightM._matrix[i][j];
    }
     return *this;

}


const Matrix Matrix::operator -()
{
    Matrix result( _nRows, _nCols );

     for( int i = 0; i < _nRows; i++ )
           for( int j = 0; j < _nCols; j++ )
              result._matrix[i][j] = _matrix[i][j] * -1;

    return result;
}


/// Comapre element by element
bool operator == ( const Matrix& leftM, const Matrix& rightM )
{
    if( leftM._nRows == rightM._nRows  &&  leftM._nCols == rightM._nCols )
    {
        bool equal = false;

        for( int i = 0; i < leftM._nRows; i++ )
            for( int j = 0; j < leftM._nCols; j++ )
                if( leftM._matrix[i][j] != rightM._matrix[i][j] )
                    equal = equal || true;

        return !equal;

    }else{  return false;  }
}


/// Calls for '==' operator
bool operator != ( const Matrix& leftM, const Matrix& rightM )
{
    return !( leftM == rightM );
}


/// Matrices must be same size.
/// Element by element adition.
Matrix& operator +=( Matrix& leftM, const Matrix& rightM )
{
    if( leftM._nRows == rightM._nRows  &&  leftM._nCols == rightM._nCols )
    {
        for( int i = 0; i < leftM._nRows; i++ )
            for( int j = 0; j < leftM._nCols; j++ )
                leftM._matrix[i][j] += rightM._matrix[i][j];

        return leftM;

    }else{ printf( "\n\nERROR:\nDiferent Dimensions @ += operator\n" );  }
}


/// Matrices must be same size.
/// Element by element Substraction
Matrix& operator -=( Matrix& leftM, const Matrix& rightM )
{
    if( leftM._nRows == rightM._nRows  &&  leftM._nCols == rightM._nCols )
    {
        for( int i = 0; i < leftM._nRows; i++ )
            for( int j = 0; j < leftM._nCols; j++ )
                leftM._matrix[i][j] -= rightM._matrix[i][j];

        return leftM;

    }else{
        printf( "\n\nERROR:\nDiferent Dimensions @ -= operator\n" );
    }
}


Matrix& operator *=( Matrix& leftM, const Matrix& rightM )
{
    if( leftM._nCols == rightM._nRows )
    {
        Matrix resultM ( leftM._nRows, rightM._nCols );

        for( int i = 0; i < resultM._nRows; i++ )
            for( int j = 0; j < resultM._nCols; j++ )
                for( int m = 0; m < rightM._nRows; m++ )
                    resultM._matrix[i][j] += leftM._matrix[i][m] * rightM._matrix[m][j];

        return resultM;
    }else{
        printf( "\n\nERROR:\nDiferent Dimensions @ *= operator\n" );
    }
}


Matrix& operator *=( Matrix& leftM, float number )
{
    for( int i = 0; i < leftM._nRows; i++ )
            for( int j = 0; j < leftM._nCols; j++ )
                leftM._matrix[i][j] *= number;

    return leftM;
}


/*****************************************************************************/

// Overload operators


const Matrix operator +=( Matrix& leftM, float number )
{
    for( int i = 0; i < leftM._nRows; i++ )
           for( int j = 0; j < leftM._nCols; j++ )
              leftM._matrix[i][j] += number;
    return leftM;
}


const Matrix operator -=( Matrix& leftM, float number )
{
    for( int i = 0; i < leftM._nRows; i++ )
           for( int j = 0; j < leftM._nCols; j++ )
              leftM._matrix[i][j] -= number;
    return leftM;
}


const Matrix operator +( const Matrix& leftM, const Matrix& rightM)
{
    if( leftM._nRows == rightM._nRows  &&  leftM._nCols == rightM._nCols )
    {
        Matrix result( leftM._nRows, leftM._nCols );

        for( int i = 0; i < leftM._nRows; i++ )
           for( int j = 0; j < leftM._nCols; j++ )
              result._matrix[i][j] = leftM._matrix[i][j] + rightM._matrix[i][j];

        return result;

    }else{
        printf( "\n\nERROR\nDiferent Dimensions @ + operator \n" );
        //Matrix error(4);
        //error.Clear();
        //return error;
    }
}


const Matrix operator +( const Matrix& leftM, float number )
{
    Matrix result( leftM._nRows, leftM._nCols );

    for( int i = 0; i < leftM._nRows; i++ )
        for( int j = 0; j < leftM._nCols; j++ )
            result._matrix[i][j] = leftM._matrix[i][j] + number;

    return result;
}


const Matrix operator +( float number, const Matrix& leftM )
{
    return ( leftM + number );
}


const Matrix operator -( const Matrix& leftM, const Matrix& rightM )
{
    if( leftM._nRows == rightM._nRows  &&  leftM._nCols == rightM._nCols )
    {
        Matrix result( leftM._nRows, leftM._nCols );

        for( int i = 0; i < leftM._nRows; i++ )
           for( int j = 0; j < leftM._nCols; j++ )
              result._matrix[i][j] = leftM._matrix[i][j] - rightM._matrix[i][j];

        return result;

    }else{
        printf( "\n\nERROR:\nDiferent Dimensions @ + operator \n" );

    }
}


const Matrix operator -( const Matrix& leftM, float number )
{
    Matrix result( leftM._nRows, leftM._nCols );

    for( int i = 0; i < leftM._nRows; i++ )
       for( int j = 0; j < leftM._nCols; j++ )
          result._matrix[i][j] = leftM._matrix[i][j] - number;

    return result;
}


const Matrix operator -( float number, const Matrix& leftM )
{
    return ( leftM - number );
}


const Matrix operator *( const Matrix& leftM, const Matrix& rightM )
{
    if( leftM._nCols == rightM._nRows )
    {
        Matrix resultM ( leftM._nRows, rightM._nCols );
        resultM.Clear();

        for( int i = 0; i < resultM._nRows; i++ )
            for( int j = 0; j < resultM._nCols; j++ )
                for( int m = 0; m < rightM._nRows; m++ )
                    resultM._matrix[i][j] += leftM._matrix[i][m] * rightM._matrix[m][j];

        return resultM;

    } else {

        printf("\n\nERROR:\nDiferent Dimension matrices @ * operator");
    }

}


const Matrix operator *( const Matrix& leftM, float number )
{
    Matrix result( leftM._nRows, leftM._nCols );

    for( int i = 0; i < leftM._nRows; i++ )
       for( int j = 0; j < leftM._nCols; j++ )
          result._matrix[i][j] = leftM._matrix[i][j] * number;

    return result;
}

const Matrix operator *( float number, const Matrix& leftM )
{
    return ( leftM * number );
}


Matrix& operator <<( Matrix& leftM, float number )
{
    if( leftM._pCol == leftM._nCols ) //end of Row
    {
        leftM._pCol = 0;
        leftM._pRow++;
    }
    if( leftM._pRow > leftM._nRows )
    {
        printf( "\n\nERROR:\nAssignment out of limits @ << operator" );
        return leftM;

    }else{

        leftM._matrix[ leftM._pRow ][ leftM._pCol ] = number;
        leftM._pCol++;

        return leftM;
    }
}
