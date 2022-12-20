#pragma once

#include "core.hpp"
#include "image.hpp"
#include "objects.hpp"
#include "vector.hpp"
#include <cstdio>
#include <netpbm/ppm.h>

class Camera {
  float aspect_ratio;
  Image img;

  float viewport_height;
  float viewport_width;
  float focal_length;

  Vector3 position;
  Vector3 horizontal;
  Vector3 vertical;

  Vector3 bottom_left_corner;

public:
  Camera(const std::string fp, const int cols, const int rows)
      : img(Image(fp, cols, rows)), position(Vector3(0.f, 0.f, 0.f)),
        aspect_ratio((float)cols / rows), viewport_height(2.f),
        viewport_width(aspect_ratio * viewport_height), focal_length(1.f),
        horizontal(Vector3(viewport_width, 0.f, 0.f)),
        vertical(Vector3(0.f, viewport_height, 0.f)),
        bottom_left_corner(position.Sub(horizontal.Mul(0.5f))
                               .Sub(vertical.Mul(0.5f))
                               .Sub(Vector3(0.f, 0.f, focal_length))) {}
  void DrawScene(Sphere *s) {
    for (int j = img.rows - 1; j >= 0; --j) {
      for (int i = 0; i < img.columns; i++) {
        float u = (float)i / (img.columns - 1);
        float v = (float)j / (img.rows - 1);
        Ray ray = Ray(position, bottom_left_corner.Add(horizontal.Mul(u))
                                    .Add(vertical.Mul(v))
                                    .Sub(position));

        HitRecord record = {Vector3(0.f, 0.f, 0.f), nullptr};

        if (s->hit(ray, &record)) {
          img.pixels[j][i] = ppm_whitepixel(255);
        }
      }
    }
  }

  void WriteImage() { img.WriteImage(); }
};
