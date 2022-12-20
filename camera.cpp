#include "camera.hpp"
#include "core.hpp"
#include "objects.hpp"
#include <cstdio>
#include <netpbm/ppm.h>

void Camera::DrawScene(Sphere *s) {
  for (int j = img.rows - 1; j >= 0; --j) {
    for (int i = 0; i < img.columns; i++) {
      float u = (float)i / (img.columns - 1);
      float v = (float)j / (img.rows - 1);
      Ray ray = Ray(position, bottom_left_corner.Add(horizontal.Mul(u))
                                  .Add(vertical.Mul(v))
                                  .Sub(position));

      HitRecord record = {Vector3(0.f, 0.f, 0.f), nullptr};

      if (s->hit(ray, &record)) {
        Vector3 normal = record.intersection.Sub(record.obj->position);
        normal = normal.Mul((float)1 / 3);
        pixel p = {(pixval)abs((int)(normal.x * 255)),
                   (pixval)abs((int)(normal.y * 255)),
                   (pixval)abs((int)(normal.z * 255))};

        img.pixels[j][i] = p;
      }
    }
  }
}
