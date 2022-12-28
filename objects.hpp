#pragma once
#include "vector.hpp"
#include <netpbm/ppm.h>

class Object;

class Ray {
public:
  Vector3 position;
  Vector3 direction;
  Ray(Vector3 pos, Vector3 dir) : position(pos), direction(dir) {}
  Vector3 At(float t) { return position.Add(direction.Mul(t)); }
};

struct HitRecord {
  float t;
  Vector3 normal;
  Vector3 intersection;
  Object *obj;
};

class Object {
public:
  pixel colour = {255, 0, 0};
  Vector3 position = Vector3(0.f, 0.f, 0.f);
  Object(Vector3 p) { position = p; };
  virtual bool hit(Ray ray, HitRecord *record) = 0;
};

class Sphere : public Object {
public:
  float radius;
  Sphere(Vector3 p, float r) : Object(p) { radius = r; }
  bool hit(Ray ray, HitRecord *record);
};
