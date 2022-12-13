#include "objects.hpp"
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <stdio.h>
#include <stdlib.h>

struct Image {
  pixel **pixels;
  int columns;
  int rows;
};

void WriteImage(Image *img, const char *fp) {
  ppm_writeppm(pm_openw(fp), img->pixels, img->columns, img->rows, 255, 0);
}

Image *InitImage(const int columns, const int rows) {
  Image *img = (Image *)malloc(sizeof(Image));

  *img = (Image){
      ppm_allocarray(columns, rows),
      columns,
      rows,
  };

  return img;
}

void FreeImage(Image *img) {
  ppm_freearray(img->pixels, img->rows);
  free(img);
}

int main() {
  pm_init("Ray Tracer", 0);

  Image *img = InitImage(128, 128);
  WriteImage(img, "out.ppm");

  Ray r = {Vector3(0.f, 0.f, 0.f), Vector3(1.f, 0.f, 0.f)};
  Sphere s = Sphere(Vector3(10.f, 0.f, 0.f), 3.f);

  s.hit(r, nullptr);

  return 0;
}
