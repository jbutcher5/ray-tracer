#pragma once
#include "vector.hpp"

class Object;

class Ray {
public:
  Vector3 position;
  Vector3 direction;
  Ray(Vector3 pos, Vector3 dir) : position(pos), direction(dir) {}
  Vector3 At(float t) {
    return position.Add(direction.Mul(t));
  }
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
