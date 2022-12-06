#include "vector.h"
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Vector3 position;
  Vector3 direction;
} Ray;

typedef struct {
  pixel **pixels;
  int columns;
  int rows;
} Image;

void WriteImage(Image *img, const char *fp) {
  ppm_writeppm(pm_openw(fp), img->pixels, img->columns, img->rows, 255, 0);
}

Image *InitImage(const int columns, const int rows) {
  Image *img = (Image *)malloc(sizeof(Image));

  *img = (Image){
      .columns = columns,
      .rows = rows,
      .pixels = ppm_allocarray(columns, rows),
  };

  return img;
}

void FreeImage(Image *img) {
  ppm_freearray(img->pixels, img->rows);
  free(img);
}

int main() {
  pm_init("Ray Tracer", 0);

  Vector3 v = {1.f, 3.f, 5.f};

  char *v_debug = Vector3Debug(&v);
  printf("%s\n", v_debug);
  free(v_debug);

  pixel **pixel_array = ppm_allocarray(128, 128);

  return 0;
}
