#include "vector.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>

Vector3 Vector3::Normalize() { return *this / Length(); }

Vector3 Vector3::Random(float min, float max) {
  float delta = max - min;

  float x = min + delta * drand48();
  float y = min + delta * drand48();
  float z = min + delta * drand48();

  return Vector3(x, y, z);
}

float Vector3::Dot(Vector3 v) { return x * v.x + y * v.y + z * v.z; }

float Vector3::Length() { return std::sqrt(LengthSquared()); }

float Vector3::LengthSquared() { return x * x + y * y + z * z; }

char *Vector3::Debug() {
  char *buffer = (char *)malloc(128 * sizeof(char));
  sprintf(buffer, "%f %f %f", x, y, z);
  return buffer;
}
