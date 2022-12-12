#pragma once
#include "core.hpp"
#include "vector.hpp"

class Sphere : public Object {
public:
  float radius;
  bool hit(Ray ray, HitRecord *record) { return false; }
};
