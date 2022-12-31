#include "materials.hpp"

Vector3 RandomInUnitSphere() {
  while (true) {
    Vector3 v = Vector3::Random(-1, 1);
    if (v.LengthSquared() >= 1)
      continue;
    return v;
  }
}

bool Diffuse::Scatter(Ray *ray_in, HitRecord *record, Ray *ray_out) {
  *ray_out = Ray(record->intersection, record->normal + RandomInUnitSphere());

  return true;
}

bool Mirror::Scatter(Ray *ray_in, HitRecord *record, Ray *ray_out) {
  Vector3 direction =
      ray_in->direction -
      record->normal * 2 * record->normal.Dot(ray_in->direction);

  *ray_out = Ray(record->intersection, direction);

  return true;
}
