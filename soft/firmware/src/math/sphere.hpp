#ifndef SPHERE_H_
#define SPHERE_H_

/**
 * Structure for data exchange with confimation capability.
 */
typedef struct Sphere Sphere;
struct Sphere{
  /**
   * @brief   Coordinates of center (x0, y0, z0).
   */
  float c[3];

  /**
   * Radius.
   */
  float r;
};

void SolveSphere(Sphere *S, float P[4][3]);

#endif /* SPHERE_H_ */
