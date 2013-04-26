/**
 * @brief  Version 0.9
 * @file   MatrixMath.h
 * @author Ernesto Palacios
 *
 * Created on 15 de septiembre de 2011, 09:44 AM.
 *
 * Develop Under  GPL v3.0 License
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 */

#ifndef  MATRIXMATH_H
#define  MATRIXMATH_H

#include "mbed.h"
#include "Matrix.h"


/**
 * @brief This class provides STATIC methods to perform operations 
 *        over Matrix Objects, version 0.9.
 */
class MatrixMath{
public:


    /**@brief
     * Transposes Matrix, return new Object.
     * @param Mat matrix to calculate
     * @return Transposed Matrix
     */
    static Matrix Transpose( const Matrix& Mat );


    /**@brief
     * Calculate the inverse of a [n,n] Matrix BUT you check first if 
     * the determinant is != 0, Same matrix will be return if Det( Mat ) == 0.
     * @param Mat matrix to calcute inverse.
     * @return Matrix Inverse
     */
    static Matrix Inv( const Matrix& Mat );


    /**@brief
     * Creates an identity [n,n] Matrix
     * @param Rows Number of Rowns and Columns
     * @return Identity Matrix of dimensions [Rows,Rows]
     */
    static Matrix Eye( int Rows );
    

    /**@brief
     * Returns the dot Product of any two same leght vectors.
     * In this case a vector is defined as a [1,n] or [n,1] Matrix.
     * Very Flexible Function.
     * @param leftM First Vector
     * @param rightM Second Vector
     * @return Dot Product or Scalar Product.
     */    
    static float dot( const Matrix& leftM, const Matrix& rightM );
    

    /**@brief Calculates the determinant of a Matrix.
     * @param Mat matrix to calculate.
     * @return the determinant.
     */
    static float det( const Matrix& Mat );


    //====  For Kinematics ====//

    /**@brief
     * Calculates the Rotation Matrix Transform along 'x' axis in radians.
     * @param radians rotation angle.
     * @return Rotation Matrix[4,4] along 'x' axis.
     */
    static Matrix RotX( float radians );


    /**@brief
     * Calculates the Rotation Matrix Transform along 'y' axis in radians.
     * @param radians rotation angle.
     * @return Rotation Matrix[4,4] along 'y' axis.
     */
    static Matrix RotY( float radians );


    /**@brief
     * Calculates the Rotation Matrix Transform along 'z' axis in radians.
     * @param radians rotation angle.
     * @return Rotation Matrix[4,4] along 'z' axis.
     */
    static Matrix RotZ( float radians );

    /**@brief
     * Calculates the Translation Matrix to coordenates (x' y' z').
     * @param x axis translation
     * @param y axis translation
     * @param z axis translation
     * @return Translation Matrix[4,4] x'y'z'.
     */
    static Matrix Transl( float x, float y, float z );

private:

    /**@brief
     * Calculates the Determinant of a 3x3 Matrix
     * @param Mat Already made sure is a 3 by 3
     * @return Float, determinant.
     */
    float Det3x3( const Matrix& Mat );

};

#endif    /* MATRIXMATH_H */
