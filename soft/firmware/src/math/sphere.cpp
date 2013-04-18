/*
 * Sorces was taken from http://www.convertalot.com/sphere_solver.html
 */
#include <math.h>

#include "uav.h"
#include "misc_math.hpp"
#include "sphere.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

//  Recursive definition of determinate using expansion by minors.
static float determinant(float a[4][4], uint32_t n)
{
  uint32_t i, j, j1, j2;
  float d = 0;
  float m[4][4] = {{0,0,0,0},
                   {0,0,0,0},
                   {0,0,0,0},
                   {0,0,0,0}};

  if (n == 2){                             // terminate recursion
    d = a[0][0]*a[1][1] - a[1][0]*a[0][1];
  }
  else{
    d = 0;
    for (j1 = 0; j1 < n; j1++){           // do each column
      for (i = 1; i < n; i++){            // create minor
        j2 = 0;
        for (j = 0; j < n; j++){
          if (j == j1) continue;
          m[i-1][j2] = a[i][j];
          j2++;
        }
      }

      // recursive call of determinant
      d += powi(-1, j1) * a[0][j1] * determinant(m, n-1);
      //d = d + powf(-1, j1)*a[0][j1]*determinant(m, n-1);
    }
  }

  return d;
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 * Calculate center and radius of sphere given four points
 * P[in]   four points of sphere organized as 2d array
 * *S[out] calculated sphere.
 *
 * How fast is it? All results in core ticks:
 * o0 - 108136
 * o2 - 80360
 * o0 - 73561 fpu
 * o2 - 38309 fpu
 */
void SolveSphere(Sphere *S, int32_t P[4][3]){
  uint32_t i;
  float m11, m12, m13, m14, m15;
  float a[4][4] = {{0,0,0,0},
                   {0,0,0,0},
                   {0,0,0,0},
                   {0,0,0,0}};

  for (i = 0; i < 4; i++){                    // find minor 11
    a[i][0] = P[i][0];
    a[i][1] = P[i][1];
    a[i][2] = P[i][2];
    a[i][3] = 1;
  }
  m11 = determinant(a, 4);

  for (i = 0; i < 4; i++){                    // find minor 12
    a[i][0] = P[i][0]*P[i][0] + P[i][1]*P[i][1] + P[i][2]*P[i][2];
    a[i][1] = P[i][1];
    a[i][2] = P[i][2];
    a[i][3] = 1;
  }
  m12 = determinant(a, 4);

  for (i = 0; i < 4; i++){                    // find minor 13
    a[i][0] = P[i][0]*P[i][0] + P[i][1]*P[i][1] + P[i][2]*P[i][2];
    a[i][1] = P[i][0];
    a[i][2] = P[i][2];
    a[i][3] = 1;
  }
  m13 = determinant(a, 4);

  for (i = 0; i < 4; i++){                    // find minor 14
    a[i][0] = P[i][0]*P[i][0] + P[i][1]*P[i][1] + P[i][2]*P[i][2];
    a[i][1] = P[i][0];
    a[i][2] = P[i][1];
    a[i][3] = 1;
  }
  m14 = determinant(a, 4);


  for (i = 0; i < 4; i++){                    // find minor 15
    a[i][0] = P[i][0]*P[i][0] + P[i][1]*P[i][1] + P[i][2]*P[i][2];
    a[i][1] = P[i][0];
    a[i][2] = P[i][1];
    a[i][3] = P[i][2];
  }
  m15 = determinant(a, 4);

  if (m11 == 0){
    chDbgPanic("Not a sphere");
  }
  else {
    S->c[0] =  0.5f * (m12 / m11);
    S->c[1] = -0.5f * (m13 / m11);
    S->c[2] =  0.5f * (m14 / m11);
    S->r    = sqrtf(S->c[0]*S->c[0] + S->c[1]*S->c[1] + S->c[2]*S->c[2] - m15/m11);
  }
}
