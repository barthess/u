/**
 * @brief  Source Code for the Matrix Class.
 * @file   Matrix.cpp
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

/// Rows by Cols Matrix Constructor
Matrix::Matrix(int Rows, int Cols): _nRows(Rows), _nCols(Cols)
{
    _matrix.resize(_nRows);
    for( int i = 0; i < _nRows; i++ )
        _matrix[i].resize(_nCols);

    _pRow = 0;
    _pCol = 0;

    this->Clear();  //Make all elements zero by default.
}


/// Copies one matrix into a new one
Matrix::Matrix(const Matrix& base)
{
    _nCols = base._nCols;
    _nRows = base._nRows;

    _pRow  = base._pRow;
    _pCol  = base._pCol;

    _matrix.resize(_nRows);
    for( int i = 0; i < _nRows; i++ )
        _matrix[i].resize(_nCols);

    for( int i = 0; i < _nRows; i++ )
        for( int j = 0; j < _nCols; j++ )
            _matrix[i][j] = base._matrix[i][j];
}


/// Default Constructor
Matrix::Matrix()
{
    _nCols = 0;
    _nRows = 0;

    _pRow = 0;
    _pCol = 0;

}

/***********************************************************************/

/// Returns true if matrix is full of zeros
bool Matrix::isZero() const
{
    bool zero = false;
    for( int i = 0; i < this->_nRows; i++ )
        for( int j = 0; j < this->_nCols; j++ )
            if( _matrix[i][j] != 0 )
                zero = zero || true;
    return !zero;
}


/// Returns true if Matrix is Single Row ot Single Column.
bool Matrix::isVector() const
{
    if( _nRows == 1 || _nCols == 1 )
        return true;
    else
        return false;
}

/*************************************************************************/

/// Returns all elements in Matrix as a single Row vector.
const Matrix Matrix::ToPackedVector( const Matrix& Mat )
{

    Matrix Crushed( 1, Mat._nRows * Mat._nCols );

    int cont = 0;

    for( int i = 0; i < Mat._nRows; i++ )
        for( int j = 0; j < Mat._nCols; j++ )
        {
            Crushed._matrix[0][cont] = Mat._matrix[i][j];
            cont++;
        }

    Crushed._pRow = Crushed._nRows;
    Crushed._pCol = Crushed._nCols;

    return Crushed;
}



/// To add (Insert) a Single Row to a Matrix.
void Matrix::AddRow(Matrix& Mat, int index)
{
    --index;

    if( index > Mat._nRows + 1)
    {
        printf("\n\nERROR:\nRow out of Limits @ AddRow()\n");

    }else{

       Mat._nRows++;
       Mat._matrix.resize( Mat._nRows );

       Mat._matrix[ Mat._nRows - 1 ].resize( Mat._nCols );

       for( int i = Mat._nRows - 1; i > index; i-- )
           for( int j = 0; j < Mat._nCols; j++ )
               Mat._matrix[i][j] = Mat._matrix[i - 1][j];

       for( int j = 0; j < Mat._nCols; j++ )
           Mat._matrix[index][j] = 0.0;
    }
}


void Matrix::AddRow(Matrix& Receip, const Matrix& Row, int index)
{
    Matrix::AddRow( Receip, index );  //Make Room

    --index;
    for( int i = 0; i < Receip._nCols; i++ )
        Receip._matrix[index][i] = Row._matrix[0][i];   //Copy Data.

}


/// To add (Insert) a single Column to a Matrix
void Matrix::AddCol( Matrix& Mat, int index )
{
    --index;

    if( index > Mat._nCols + 1 )
    {
        printf("\n\nERROR:\nRow out of Limits on AddCol()\n");

    }else{


            Mat._nCols++;
            for( int i = 0; i < Mat._nRows; i++ )
                Mat._matrix[i].resize( Mat._nCols );

            for( int i = 0; i < Mat._nRows; i++ )
                for( int j = Mat._nCols; j > index; j-- )
                    Mat._matrix[i][j] = Mat._matrix[i][j - 1];

            for( int i = 0; i < Mat._nRows; i++ )
                Mat._matrix[i][index] = 0.0;

    }
}


void Matrix::AddCol(Matrix& Receip, const Matrix& Row, int index)
{
    Matrix::AddCol( Receip, index ); // Make Rom

    --index;
    for( int i = 0; i < Receip._nRows; i++ )
        Receip._matrix[i][index] = Row._matrix[i][0];   //Copy Data.
}


/// Delete a Single Column From Matrix.
void Matrix::DeleteCol( Matrix& Mat, int Col)
{
    --Col; // Because of Column zero.

    if( Col > Mat._nCols )
    {
        printf("\n\nERROR:\nColumn out of Limits @ DeleteCol()\n");

    }else{

        for( int i = 0; i < Mat._nRows; i++ )
            for( int j = Col; j < Mat._nCols; j++ )
                Mat._matrix[i][j] = Mat._matrix[i][j+1];

        // If adressing last element of Column,
        // wich no longer exists
        if( Mat._pCol == Mat._nCols )
            Mat._pCol--;

        // Decrease one column
        Mat._nCols--;

        //Erase last Column
        for( int i = 0; i < Mat._nRows; i++ )
            Mat._matrix[i].reserve(Mat._nCols);

    }
}


/// Delete a Single Row form Matrix
void Matrix::DeleteRow(Matrix& Mat, int Row)
{
    --Row;

    if( Row > Mat._nRows )
    {
        printf("\n\nERROR:\nColumn out of Limits @ DeleteCol()\n");

    }else{

        for( int i = Row; i < Mat._nRows - 1; i++ )

            for( int j = 0; j < Mat._nCols; j++ )
                Mat._matrix[i][j] = Mat._matrix[i+1][j];
        Mat._nRows--;
        Mat._matrix.resize(Mat._nRows);
    }
}

/*****************************************************************************************/

/// Extracts a single row form calling matrix and saves it to another matrix.
const Matrix Matrix::ExportRow( const Matrix& Mat, int row )
{
    --row;

    if( row > Mat._nRows )
    {
        printf( "\n\nERROR:\nRow out of dimmensions @ GetRow\n"
                "Nothing Done.\n\n" );

    }else{

        Matrix SingleRow( 1 , Mat._nCols );
        SingleRow.Clear();

        for( int j = 0; j < Mat._nCols; j++ )
        SingleRow._matrix[0][j] = Mat._matrix[row][j];

        SingleRow._pCol = SingleRow._nCols;
        SingleRow._pRow = 0;

        return SingleRow;
    }
}


/// Extracts a single column form calling matrix and saves it to another matrix.
const Matrix Matrix::ExportCol( const Matrix& Mat, int col )
{
    --col;

    if( col > Mat._nCols )
    {
        printf( "\n\nERROR:\nColumn out of dimmensions.\n"
                "Nothing Done.\n\n" );
    }else{

        Matrix SingleCol( Mat._nRows, 1 );
        for(int i = 0; i < Mat._nRows; i++ )
            SingleCol._matrix[i][0] = Mat._matrix[i][col];

        SingleCol._pCol = 0;
        SingleCol._pRow = SingleCol._nRows;

        return SingleCol;
    }
}


/// Makes matrix Bigger!
void Matrix::Resize( int Rows, int Cols )
{
    _nRows = Rows;  //Decreases one because internally
    _nCols = Cols; // Index starts at zero.

    _matrix.resize( _nRows );

    for( int i = 0; i< _nRows ; i++ )
        _matrix[i].resize(_nCols);

    _pRow = 0; // If matrix is resized the <<
    _pCol = 0; // operator overwrites everything!
}


/// Ask user for elemnts in Matrix
void Matrix::FillMatrix()
{
    for(int i = 0; i < _nRows; i++)
    {
        for(int j = 0; j < _nCols; j++)
        {
            printf( "Position [%u][%u]: ", i, j );
            float numero;
            scanf( "%f", &numero );
            printf("%.3f ", numero);
            this->_matrix[i][j] = numero;
        }
        printf("\n");
    }
    printf("\n");

    _pRow = _nRows;
    _pCol = _nCols;
}


/// Prints out Matrix.
void Matrix::print() const
{
    for( int i = 0; i < _nRows; i++ )
    {
        for( int j = 0; j < _nCols; j++ )
        {
            printf( "%.3f, ",_matrix[i][j] );

        }
        printf( "\n" );
    }
}


/// Fills matrix with zeros.
void Matrix::Clear()
{
    for( int i = 0; i < _nRows; i++ )
       for( int j = 0; j < _nCols; j++ )
           _matrix[i][j] = 0;

    _pCol = 0;  // New data can be added
    _pRow = 0;
}

/********************************************************************************/


/// Inserts a Single element in a desired Position( Index starts at [1][1] );
void Matrix::add(int Row, int Col, float number)
{
    --Col; --Row;

    if( Row > _nRows || Col > _nCols )
    {
        printf("\n\nERROR:\nOut of limits of Matrix @ mat.Add()");

    }else{
        _matrix[Row][Col] = number;
    }
}


/// Adds all elements in matrix and returns the answer.
float Matrix::sum() const
{
    float total = 0;

    for( int i = 0; i < _nRows; i++ )
        for( int j = 0; j < _nCols; j++ )
            total += _matrix[i][j];
    return total;
}


/// Returns the specified element. Index Starts at [1][1].
float Matrix::getNumber( int Row, int Col ) const
{ return this->_matrix[Row -1][Col - 1]; }

/// Returns the number of Rows in Matrix.
int Matrix::getRows() const{ return this->_nRows; }


/// Returns the number of Columns in Matrix.
int Matrix::getCols() const{ return this->_nCols; }