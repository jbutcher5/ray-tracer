#include "objects.hpp"
#include "math.h"
#include "math_utils.hpp"
#include "stdio.h"

bool Sphere::hit(Ray ray, HitRecord *record) {
  Vector3 origin = ray.position.Sub(position);

  float a = ray.direction.Dot(ray.direction);
  float b = 2.f * origin.Dot(ray.direction);
  float c = origin.Dot(origin) - radius * radius;

  float x1, x2;

  SolveQuadratic(a, b, c, &x1, &x2);

  if (isnan(x2))
    return false;

  Vector3 intersection = ray.At(x2);

  record->intersection = intersection;
  record->obj = this;

  return true;
}
