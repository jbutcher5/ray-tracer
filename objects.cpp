#include "objects.hpp"
#include "math.h"
#include "math_utils.hpp"
#include <cmath>

bool Sphere::hit(Ray ray, HitRecord *record) {
  Vector3 origin = ray.position.Sub(position);

  float a = std::pow(ray.direction.Length(), 2);
  float b = origin.Dot(ray.direction);
  float c = std::pow(origin.Length(), 2) - radius * radius;

  float discriminant = b * b - a * c;

  if (discriminant < 0)
    return false;

  float x1 = (-b - std::sqrt(discriminant)) / a;
  float x2 = (-b + std::sqrt(discriminant)) / a;

  float t = x1;

  if (std::abs(x2) < std::abs(x1))
    t = x2;

  Vector3 intersection = ray.At(t);

  if (t > 0)
    return false;

  record->t = t;
  record->intersection = intersection;
  record->obj = this;
  record->normal = intersection.Sub(position).Normalize();

  return true;
}
