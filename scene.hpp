#pragma once

#include "image.hpp"
#include "objects.hpp"
#include "vector.hpp"
#include <vector>

class Scene {
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
  Scene(const std::string fp, const int cols, const int rows,
        const int samples_per_pixel);
  void DrawScene();
  void WriteImage() { img.WriteImage(); }
  void AddObject(Object *obj) { scene.push_back(obj); }
  Colour PixelColour(int pixel_row, int pixel_col);
  Colour GetColour(Ray r, int depth);
  Colour GetColour(Ray r);
  Colour SkyColour(Ray r);
};
