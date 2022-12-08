#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Vector3 Vector3Add(Vector3 v1, Vector3 v2) {
  return (Vector3){.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z};
}

float Vector3DotProduct(Vector3 v1, Vector3 v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void SolveQuadratic(float a, float b, float c, float *x1, float *x2) {
  float discrim_root = sqrtf(b * b - 4 * a * c);

  *x1 = (-b + discrim_root) / (2 * a);
  *x2 = (-b - discrim_root) / (2 * a);
}

float Vector3Length(Vector3 v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

char *Vector3Debug(Vector3 *v) {
  char *buffer = (char *)malloc(128 * sizeof(char));
  sprintf(buffer, "%f %f %f", v->x, v->y, v->z);
  return buffer;
}
