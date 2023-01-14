#include "image.hpp"
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <string>

inline double clamp(double x, double min, double max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

inline Colour Colour::Clamp() {
  return Colour(clamp(r, 0, 0.999), clamp(g, 0, 0.999), clamp(b, 0, 0.999));
}

void Image::WriteImage() {
  FILE *f = pm_openw(file_path.c_str());
  ppm_writeppm(f, pixels, columns, rows, 255, 0);
}

void Image::SetPixel(int row, int col, Colour colour, int samples_per_pixel) {
  auto scale = 1.0 / samples_per_pixel;
  colour = (colour * scale).Clamp();

  pixels[row][col] = colour.ToPixel();
};
