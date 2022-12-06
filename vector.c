#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Vector3 Vector3Add(Vector3 v1, Vector3 v2) {
  return (Vector3){.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z};
}

float Vector3Length(Vector3 v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

char *Vector3Debug(Vector3 *v) {
  char *buffer = (char *)malloc(128 * sizeof(char));
  sprintf(buffer, "%f %f %f", v->x, v->y, v->z);
  return buffer;
}
