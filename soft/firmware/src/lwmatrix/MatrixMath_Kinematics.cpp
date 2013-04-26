/**
 * @brief  Simple Kinematics Operations
 * @file   MatrixMath_Kinematics.cpp
 * @author Ernesto Palacios
 *
 * Created on september 2011, 09:44 AM.
 *
 * Develop Under  GPL v3.0 License
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#include "mbed.h"
#include "Matrix.h"
#include "MatrixMath.h"


Matrix MatrixMath::RotX( float radians )
{
    float cs = cos( radians );
    float sn = sin( radians );

    Matrix rotate( 4, 4 );

    rotate << 1 << 0  <<  0  << 0
           << 0 << cs << -sn << 0
           << 0 << sn <<  cs << 0
           << 0 << 0  <<  0  << 1;

    return rotate;

}

Matrix MatrixMath::RotY( float radians )
{
    float cs = cos( radians );
    float sn = sin( radians );

    Matrix rotate( 4, 4 );

    rotate << cs   << 0   <<  sn  << 0
           <<  0   << 1   <<  0   << 0
           << -sn  << 0   <<  cs  << 0
           <<  0   << 0   <<  0   << 1;

    return rotate;
}

Matrix MatrixMath::RotZ( float radians )
{
    float cs = cos( radians );
    float sn = sin( radians );

    Matrix rotate( 4, 4 );

    rotate << cs   << -sn  <<  0  << 0
           << sn   <<  cs  <<  0  << 0
           <<  0   <<  0   <<  1  << 0
           <<  0   <<  0   <<  0  << 1;

    return rotate;
}


Matrix MatrixMath::Transl( float x, float y, float z )
{
    Matrix Translation = MatrixMath::Eye( 3 );  //Identity Matrix
    Matrix Position( 4, 1 );                   // Position Matrix

    Position << x << y << z << 1;            // position @ x,y,z

    Matrix::AddRow( Translation, 4 );             // Add Row
    Matrix::AddCol( Translation, Position, 4 );  // Add Position Matrix

    return Translation;
}