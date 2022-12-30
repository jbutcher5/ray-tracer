#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Vector3 {
public:
  float x;
  float y;
  float z;

  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3() : x(0), y(0), z(0) {}
  Vector3 Add(Vector3 v);
  Vector3 Sub(Vector3 v);
  Vector3 Mul(float k);
  Vector3 Div(float k);
  Vector3 Normalize();
  static Vector3 Random(float min, float max);
  float Dot(Vector3 v);
  float Length();
  char *Debug();
};
