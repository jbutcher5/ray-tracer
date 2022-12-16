#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Vector3 {
public:
  float x;
  float y;
  float z;

  Vector3(float x, float y, float z) : x(x), y(y), z(z){};
  Vector3 Add(Vector3 v);
  Vector3 Sub(Vector3 v);
  Vector3 Mul(float k);
  float Dot(Vector3 v);
  float Length();
  char *Debug();
};
