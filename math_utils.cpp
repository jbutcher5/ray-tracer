#include <math.h>

void SolveQuadratic(float a, float b, float c, float *x1, float *x2) {
  float discrim_root = sqrtf(b * b - 4 * a * c);

  *x1 = (-b + discrim_root) / (2 * a);
  *x2 = (-b - discrim_root) / (2 * a);
}
