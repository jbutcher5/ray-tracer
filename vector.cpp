#include "vector.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Vector3 Vector3::Add(Vector3 v) { return Vector3(x + v.x, y + v.y, z + v.z); }

Vector3 Vector3::Sub(Vector3 v) { return Vector3(x - v.x, y - v.y, z - v.z); }

float Vector3::Dot(Vector3 v) { return x * v.x + y * v.y + z * v.z; }

float Vector3::Length() { return sqrtf(x * x + y * y + z * z); }

char *Vector3::Debug() {
  char *buffer = (char *)malloc(128 * sizeof(char));
  sprintf(buffer, "%f %f %f", x, y, z);
  return buffer;
}
