#include "world.hpp"
#include "objects.hpp"
#include <cmath>
#include <netpbm/ppm.h>

void World::DrawScene() {
  for (int pixel_col = 0; pixel_col < img.rows; pixel_col++)
    for (int pixel_row = 0; pixel_row < img.columns; pixel_row++) {
      pixel p = GetColour(pixel_row, pixel_col);
      img.pixels[pixel_col][pixel_row] = p;
    }
}

pixel World::GetColour(int pixel_row, int pixel_col) {
  pixel buffer = ppm_blackpixel();

  int pixel_side_length = std::sqrt(samples_per_pixel);

  for (int i = 0; i < pixel_side_length; i++)
    for (int j = 0; j < pixel_side_length; j++) {
      float u = ((float)pixel_row + ((float)i / pixel_side_length)) /
                (img.columns - 1);
      float v =
          ((float)pixel_col + ((float)j / pixel_side_length)) / (img.rows - 1);

      Ray ray = Ray(position, bottom_left_corner.Add(horizontal.Mul(u))
                                  .Add(vertical.Mul(v))
                                  .Sub(position)
                                  .Normalize());

      HitRecord record = {0, Vector3(0.f, 0.f, 0.f), nullptr};
      bool does_hit = false;

      for (Object *obj : scene) {
        HitRecord tmp_record = {0, Vector3(0.f, 0.f, 0.f), nullptr};
        if (obj->hit(ray, &tmp_record)) {
          if (!does_hit) {
            does_hit = true;
            record = tmp_record;
          } else if (fabs(tmp_record.t) < fabs(record.t)) {
            record = tmp_record;
          }
        }
      }

      pixel p = ppm_blackpixel();

      if (does_hit) {
        Vector3 normal =
            record.intersection.Sub(record.obj->position).Normalize();

        p = {(pixval)abs((int)(normal.x * 255)),
             (pixval)abs((int)(normal.y * 255)),
             (pixval)abs((int)(normal.z * 255))};
      }

      buffer.r += p.r;
      buffer.g += p.g;
      buffer.b += p.b;
    }

  buffer.r /= samples_per_pixel;
  buffer.g /= samples_per_pixel;
  buffer.b /= samples_per_pixel;

  return buffer;
}
