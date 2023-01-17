#include "objects.hpp"
#include "math_utils/math_utils.hpp"
#include <cmath>
#include <math.h>

#define EPSILON 0.001f

bool Sphere::hit(Ray ray, HitRecord *record) {
  Vector3 origin = ray.position - position;

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

  if (t < EPSILON)
    return false;

  record->t = t;
  record->intersection = intersection;
  record->obj = this;
  record->normal = (intersection - position).Normalize();

  return true;
}

bool Triangle::hit(Ray ray, HitRecord *record) {

  Vector3 edges[2] = {v2 - v1, v3 - v1};
  Vector3 h, s, q;
  float a, f, u, v;

  h = ray.direction.Cross(edges[1]);
  a = edges[0].Dot(h);

  if (a > -EPSILON && a < EPSILON)
    return false;

  f = 1.0 / a;
  s = ray.position - v1;
  u = f * s.Dot(h);

  if (u < 0.0 || u > 1.0)
    return false;

  q = s.Cross(edges[0]);
  v = f * ray.direction.Dot(q);

  if (v < 0.0 || u + v > 1.0)
    return false;

  float t = f * edges[2].Dot(q);

  Vector3 intersection = ray.At(t);

  record->t = t;
  record->intersection = intersection;
  record->obj = this;
  record->normal = edges[0].Cross(edges[1]).Normalize();

  return true;
}
