#pragma once
#include "core.hpp"
#include "vector.hpp"

class Sphere : public Object {
public:
  float radius;
  Sphere(Vector3 p, float r) : Object(p) { radius = r; }
  bool hit(Ray ray, HitRecord *record);
};
