#include "image.hpp"
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <string>

void Image::WriteImage() {
  FILE *f = pm_openw(file_path.c_str());

  ppm_writeppm(f, pixels, columns, rows, 255, 0);
}
