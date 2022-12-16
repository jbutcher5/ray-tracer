#include "objects.hpp"
#include "math_utils.hpp"
#include "stdio.h"

bool Sphere::hit(Ray ray, HitRecord *record) {
  Vector3 origin = ray.position.Sub(position);

  float a = ray.direction.Dot(ray.direction);
  float b = 2.f * origin.Dot(ray.direction);
  float c = origin.Dot(origin) - radius * radius;

  float x1, x2;

  SolveQuadratic(a, b, c, &x1, &x2);

  Vector3 intersection = ray.At(x2);

  printf("%f %f (%f %f %f)\n", x1, x2, intersection.x, intersection.y,
         intersection.z);

  return true;
}
