#include "scene.hpp"
#include "image.hpp"
#include "materials.hpp"
#include "objects.hpp"
#include "vector.hpp"
#include <cmath>
#include <netpbm/ppm.h>

#define MAX_RAY_DEPTH 5

Scene::Scene(const std::string fp, const int cols, const int rows,
             const int samples_per_pixel)
    : img(Image(fp, cols, rows)) {
  this->samples_per_pixel = samples_per_pixel;
  aspect_ratio = (float)cols / rows;
  viewport_height = 2.f;
  viewport_width = aspect_ratio * viewport_height;
  focal_length = 1.8f;
  horizontal = Vector3(viewport_width, 0.f, 0.f);
  vertical = Vector3(0.f, viewport_height, 0.f);
  bottom_left_corner = position - horizontal / 2 - vertical / 2 -
                       Vector3(0.f, 0.f, focal_length);
}

Colour Scene::SkyColour(Ray r) {
  Vector3 dir = r.direction.Normalize();
  float t = 0.5 * (dir.y + 1);

  return Colour::White() * (1 - t) + Colour(0.5, 0.7, 1.0) * t;
}

void Scene::DrawScene() {
#pragma omp parallel for schedule(dynamic, 1)
  for (int pixel_col = 0; pixel_col < img.columns; pixel_col++)
    for (int pixel_row = 0; pixel_row < img.rows; pixel_row++) {
      Colour colour = PixelColour(pixel_col, pixel_row);
      img.SetPixel(pixel_row, pixel_col, colour, samples_per_pixel);
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
          ((float)(img.rows - pixel_row) + ((float)j / pixel_side_length)) /
          (img.rows - 1);

      Ray ray = Ray(position, bottom_left_corner + horizontal * u +
                                  vertical * v - position);

      Colour colour = GetColour(ray);

      buffer.r += colour.r;
      buffer.g += colour.g;
      buffer.b += colour.b;
    }

  return buffer;
}

Colour Scene::GetColour(Ray r) { return GetColour(r, 0); }

Colour Scene::GetColour(Ray r, int depth) {
  if (depth > MAX_RAY_DEPTH)
    return Colour::Black();

  HitRecord record;

  bool does_hit = false;

  for (Object *obj : scene) {
    HitRecord tmp_record;

    if (obj->hit(r, &tmp_record)) {
      if (!does_hit) {
        does_hit = true;
        record = tmp_record;
      } else if (fabs(tmp_record.t) < fabs(record.t)) {
        record = tmp_record;
      }
    }
  }

  if (!does_hit)
    return SkyColour(r);

  Ray ray_out;
  Colour attenuation;
  record.obj->material->Scatter(&r, &record, &attenuation, &ray_out);

  Colour colour = GetColour(ray_out, depth + 1) * attenuation;
  return colour;
}
