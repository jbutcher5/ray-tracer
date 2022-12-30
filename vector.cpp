#include "vector.hpp"
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Vector3 Vector3::Add(Vector3 v) { return Vector3(x + v.x, y + v.y, z + v.z); }

Vector3 Vector3::Sub(Vector3 v) { return Vector3(x - v.x, y - v.y, z - v.z); }

Vector3 Vector3::Mul(float k) { return Vector3(x * k, y * k, z * k); }

Vector3 Vector3::Div(float k) { return Mul(1.f / k); }

Vector3 Vector3::Normalize() { return Div(Length()); }

Vector3 Vector3::Random(float min, float max) {
  float delta = max - min;

  float scalar = (float)rand() / (float)RAND_MAX;
  float x = min + delta * scalar;

  scalar = (float)rand() / (float)RAND_MAX;
  float y = min + delta * scalar;

  scalar = (float)rand() / (float)RAND_MAX;
  float z = min + delta * scalar;

  return {x, y, z};
}

float Vector3::Dot(Vector3 v) { return x * v.x + y * v.y + z * v.z; }

float Vector3::Length() { return std::sqrt(LengthSquared()); }

float Vector3::LengthSquared() { return x * x + y * y + z * z; }

char *Vector3::Debug() {
  char *buffer = (char *)malloc(128 * sizeof(char));
  sprintf(buffer, "%f %f %f", x, y, z);
  return buffer;
}
