#include "objects.hpp"
#include "math.h"
#include "math_utils.hpp"
#include <cmath>

bool Sphere::hit(Ray ray, HitRecord *record) {
  Vector3 origin = ray.position.Sub(position);

  float a = std::pow(ray.direction.Length(), 2);
  float b = origin.Dot(ray.direction);
  float c = origin.Dot(origin) - radius * radius;

  float discriminant = b * b - a * c;

  if (discriminant < 0)
    return false;

  float t = -b - std::sqrt(discriminant);

  Vector3 intersection = ray.At(t);

  record->t = t;
  record->intersection = intersection;
  record->obj = this;

  return true;
}
