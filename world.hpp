#pragma once

#include "image.hpp"
#include "objects.hpp"
#include "vector.hpp"
#include <vector>

class World {
  float aspect_ratio;
  int samples_per_pixel;
  Image img;

  float viewport_height;
  float viewport_width;
  float focal_length;

  Vector3 position;
  Vector3 horizontal;
  Vector3 vertical;

  Vector3 bottom_left_corner;

  std::vector<Object *> scene;

public:
  World(const std::string fp, const int cols, const int rows,
        const int samples_per_pixel)
      : img(Image(fp, cols, rows)), samples_per_pixel(samples_per_pixel),
        position(Vector3(0.f, 0.f, 0.f)), aspect_ratio((float)cols / rows),
        viewport_height(2.f), viewport_width(aspect_ratio * viewport_height),
        focal_length(1.8f), horizontal(Vector3(viewport_width, 0.f, 0.f)),
        vertical(Vector3(0.f, viewport_height, 0.f)),
        bottom_left_corner(position.Sub(horizontal.Mul(0.5f))
                               .Sub(vertical.Mul(0.5f))
                               .Sub(Vector3(0.f, 0.f, focal_length))) {}
  void DrawScene();
  void WriteImage() { img.WriteImage(); }
  void AddObject(Object *obj) { scene.push_back(obj); }
  Colour PixelColour(int pixel_row, int pixel_col);
  Colour GetColour(Ray r, int depth);
  Colour GetColour(Ray r);
};
