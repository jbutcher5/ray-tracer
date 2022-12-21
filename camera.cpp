#include "camera.hpp"
#include "objects.hpp"
#include <netpbm/ppm.h>

void Camera::DrawScene() {
  for (int j = img.rows - 1; j >= 0; --j) {
    for (int i = 0; i < img.columns; i++) {
      float u = (float)i / (img.columns - 1);
      float v = (float)j / (img.rows - 1);
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

      if (does_hit) {
        Vector3 normal =
            record.intersection.Sub(record.obj->position).Normalize();
        pixel p = {(pixval)abs((int)(normal.x * 255)),
                   (pixval)abs((int)(normal.y * 255)),
                   (pixval)abs((int)(normal.z * 255))};

        img.pixels[j][i] = p;
      }
    }
  }
}
