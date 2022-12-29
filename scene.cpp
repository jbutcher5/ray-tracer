#include "scene.hpp"
#include "image.hpp"
#include "objects.hpp"
#include "vector.hpp"
#include <cmath>
#include <netpbm/ppm.h>

void Scene::DrawScene() {
  for (int pixel_col = 0; pixel_col < img.columns; pixel_col++)
    for (int pixel_row = 0; pixel_row < img.rows; pixel_row++) {
      Colour colour = PixelColour(pixel_col, pixel_row);
      img.SetPixel(pixel_row, pixel_col, colour);
    }
}

Colour Scene::PixelColour(int pixel_col, int pixel_row) {
  Colour buffer = Colour::Black();

  int pixel_side_length = std::sqrt(samples_per_pixel);

  for (int i = 0; i < pixel_side_length; i++)
    for (int j = 0; j < pixel_side_length; j++) {
      float u = ((float)pixel_col + ((float)i / pixel_side_length)) /
                (img.columns - 1);
      float v =
          ((float)pixel_row + ((float)j / pixel_side_length)) / (img.rows - 1);

      Ray ray = Ray(position, bottom_left_corner.Add(horizontal.Mul(u))
                                  .Add(vertical.Mul(v))
                                  .Sub(position));

      Colour colour = GetColour(ray);

      buffer.r += colour.r;
      buffer.g += colour.g;
      buffer.b += colour.b;
    }

  buffer.r /= samples_per_pixel;
  buffer.g /= samples_per_pixel;
  buffer.b /= samples_per_pixel;

  return buffer;
}

Colour Scene::GetColour(Ray r) { return GetColour(r, 0); }

Colour Scene::GetColour(Ray r, int depth) {
  if (depth > 50)
    return Colour::Black();

  HitRecord record = {0, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f),
                      nullptr};
  bool does_hit = false;

  for (Object *obj : scene) {
    HitRecord tmp_record = {0, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f),
                            nullptr};
    if (obj->hit(r, &tmp_record)) {
      if (!does_hit) {
        does_hit = true;
        record = tmp_record;
      } else if (fabs(tmp_record.t) < fabs(record.t)) {
        record = tmp_record;
      }
    }
  }

  if (does_hit) {

    Vector3 normal = record.normal.Normalize();

    Colour colour = {(double)((normal.x + 1) / 2), (double)((normal.y + 1) / 2),
                     (double)((normal.z + 1) / 2)};

    return colour;
  }

  return Colour((pixel){20, 50, 200});
}
