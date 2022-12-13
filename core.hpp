#pragma once
#include "vector.hpp"

class Object;

struct Ray {
  Vector3 position;
  Vector3 direction;
};

struct HitRecord {
  Vector3 position;
  Object *obj;
};

class Object {
public:
  Vector3 position = Vector3(0.f, 0.f, 0.f);
  Object(Vector3 p) { position = p; };
  virtual bool hit(Ray ray, HitRecord *record) = 0;
};
