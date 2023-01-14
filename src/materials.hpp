#pragma once
#include "image.hpp"
#include "objects.hpp"

class Material {
public:
  Colour colour;
  Material() = default;
  Material(Colour colour) : colour(colour) {}
  virtual bool Scatter(Ray *ray_in, HitRecord *record, Colour *attenuation,
                       Ray *ray_out) = 0;
};

class Diffuse : public Material {
public:
  Diffuse(Colour colour) : Material(colour) {}
  bool Scatter(Ray *ray_in, HitRecord *record, Colour *attenuation,
               Ray *ray_out);
};

class Mirror : public Material {
public:
  Mirror(Colour colour) : Material(colour) {}
  bool Scatter(Ray *ray_in, HitRecord *record, Colour *attenuation,
               Ray *ray_out);
};

class PartialDiffuse : public Material {
  float roughness;

public:
  PartialDiffuse() = default;
  PartialDiffuse(float roughness, Colour colour)
      : roughness(roughness), Material(colour) {}
  bool Scatter(Ray *ray_in, HitRecord *record, Colour *attenuation,
               Ray *ray_out);
};
