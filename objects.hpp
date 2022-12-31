#pragma once
#include "vector.hpp"
#include <cstdlib>
#include <netpbm/ppm.h>

class Material;
class Object;

class Ray {
public:
  Vector3 position;
  Vector3 direction;
  Ray() {}
  Ray(Vector3 pos, Vector3 dir) : position(pos), direction(dir) {}
  Vector3 At(float t) { return position + direction * t; }
};

class HitRecord {
public:
  float t;
  Vector3 normal;
  Vector3 intersection;
  Object *obj;
  HitRecord() {}
};

class Object {
public:
  pixel colour = {255, 0, 0};
  Vector3 position;
  Material *material;
  Object() {}
  Object(Vector3 p, Material *material) {
    position = p;
    this->material = material;
  }
  virtual bool hit(Ray ray, HitRecord *record) = 0;
};

class Sphere : public Object {
public:
  float radius;
  Sphere(Vector3 p, float r, Material *material) : Object(p, material) {
    radius = r;
  }
  bool hit(Ray ray, HitRecord *record);
};
