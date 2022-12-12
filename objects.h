#pragma once
#include "vector.h"

typedef struct {
  Vector3 position;
} Object;

typedef struct {
  Vector3 position;
  Vector3 direction;
} Ray;

typedef struct {
  Vector3 position;
  float radius;
} Sphere;
