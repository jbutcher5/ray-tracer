#include "world.hpp"
#include "objects.hpp"
#include <cmath>
#include <cstdio>
#include <netpbm/ppm.h>

void World::DrawScene() {
  for (int pixel_col = 0; pixel_col < img.columns; pixel_col++)
    for (int pixel_row = 0; pixel_row < img.rows; pixel_row++) {
      pixel p = PixelColour(pixel_col, pixel_row);
      img.pixels[pixel_row][pixel_col] = p;
    }
}

pixel World::PixelColour(int pixel_col, int pixel_row) {
  pixel buffer = ppm_blackpixel();

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

      pixel p = GetColour(ray);

      buffer.r += p.r;
      buffer.g += p.g;
      buffer.b += p.b;
    }

  buffer.r /= samples_per_pixel;
  buffer.g /= samples_per_pixel;
  buffer.b /= samples_per_pixel;

  return buffer;
}

pixel World::GetColour(Ray r) { return GetColour(r, 0); }

pixel World::GetColour(Ray r, int depth) {
  if (depth > 50)
    return {0, 0, 0};

  HitRecord record = {0, Vector3(0.f, 0.f, 0.f), nullptr};
  bool does_hit = false;

  for (Object *obj : scene) {
    HitRecord tmp_record = {0, Vector3(0.f, 0.f, 0.f), nullptr};
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
    Vector3 normal = record.intersection.Sub(record.obj->position).Normalize();

    // Ray r2 = Ray(record.intersection,
    // normal.Add(Vector3::Random(-1.f, 1.f)));

    // pixel colour = GetColour(r2, depth + 1);
    // colour.r /= 2;
    // colour.g /= 2;
    // colour.b /= 2;

    pixel p = {(pixval)((normal.x + 1) * 128), (pixval)((normal.y + 1) * 128),
               (pixval)((normal.z + 1) * 128)};

    return p;
  }

  return {0, 0, 0};
}
