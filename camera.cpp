#include "camera.hpp"
#include "objects.hpp"
#include <cmath>
#include <netpbm/ppm.h>

void Camera::DrawScene() {
  pixel *pixel_colour = (pixel *)malloc(sizeof(pixel) * samples_per_pixel);

  int pixel_side_length = std::sqrt(samples_per_pixel);

  for (int pixel_col = 0; pixel_col < img.rows; pixel_col++)
    for (int pixel_row = 0; pixel_row < img.columns; pixel_row++) {
      int colour_counter = 0;

      for (int i = 0; i < pixel_side_length; i++)
        for (int j = 0; j < pixel_side_length; j++) {
          float u = ((float)pixel_row + ((float)i / pixel_side_length)) /
                    (img.columns - 1);
          float v = ((float)pixel_col + ((float)j / pixel_side_length)) /
                    (img.rows - 1);

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

          pixel p = {0, 0, 0};

          if (does_hit) {
            Vector3 normal =
                record.intersection.Sub(record.obj->position).Normalize();

            p = {(pixval)abs((int)(normal.x * 255)),
                 (pixval)abs((int)(normal.y * 255)),
                 (pixval)abs((int)(normal.z * 255))};
          }

          pixel_colour[colour_counter] = p;
          colour_counter++;
        }

      pixel average_pixel = {0, 0, 0};

      for (int index = 0; index < samples_per_pixel; index++) {
        pixel p = pixel_colour[index];

        average_pixel.r += p.r;
        average_pixel.g += p.g;
        average_pixel.b += p.b;
      }

      average_pixel.r /= samples_per_pixel;
      average_pixel.g /= samples_per_pixel;
      average_pixel.b /= samples_per_pixel;

      img.pixels[pixel_col][pixel_row] = average_pixel;
    }

  free(pixel_colour);
}
