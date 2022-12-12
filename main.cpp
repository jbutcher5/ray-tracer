#include "objects.hpp"
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <stdio.h>
#include <stdlib.h>

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

  return 0;
}
