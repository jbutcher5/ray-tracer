#pragma once
#include "vector.hpp"

class Object;

class Ray {
  Vector3 position;
  Vector3 direction;
};

struct HitRecord {
  Vector3 position;
  Object *obj;
};

class Object {
public:
  Vector3 position;
  virtual bool hit(Ray ray, HitRecord *record) = 0;
};
