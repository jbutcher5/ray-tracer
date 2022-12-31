#pragma once
#include "objects.hpp"

class Material {
public:
  Material() {}
  virtual bool Scatter(Ray *ray_in, HitRecord *record, Ray *ray_out) = 0;
};

class Diffuse : public Material {
  bool Scatter(Ray *ray_in, HitRecord *record, Ray *ray_out);
};

class Mirror : public Material {
  bool Scatter(Ray *ray_in, HitRecord *record, Ray *ray_out);
};
