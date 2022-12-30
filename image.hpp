#pragma once
#include <netpbm/ppm.h>
#include <string>
#define PIXVAL_LIMIT 255

class Colour {
public:
  double r;
  double g;
  double b;
  Colour(double r, double g, double b) : r(r), g(g), b(b) {}
  Colour(pixel p)
      : Colour((double)p.r / PIXVAL_LIMIT, (double)p.g / PIXVAL_LIMIT,
               (double)p.b / PIXVAL_LIMIT) {}
  pixel ToPixel() {
    return (pixel){(pixval)(r * 255), (pixval)(g * 255), (pixval)(b * 255)};
  };
  static Colour Black() { return Colour(0, 0, 0); }
  static Colour White() { return Colour(1, 1, 1); }
  Colour Mul(Colour c) { return Colour(c.r * r, c.g * g, c.b * b); }
  Colour Mul(double k) { return Colour(k * r, k * g, k * b); }
  Colour Add(Colour c) { return Colour(c.r + r, c.g + g, c.b + b); }
  Colour Clamp();
};

class Image {
  pixel **pixels;

public:
  const std::string file_path;
  const int columns;
  const int rows;

  Image(const std::string fp, const int cols, const int rows)
      : columns(cols), rows(rows), file_path(fp) {
    pixels = ppm_allocarray(cols, rows);
  }
  ~Image() { ppm_freearray(pixels, rows); }
  void WriteImage();
  void SetPixel(int row, int col, Colour colour, int samples_per_pixel);
};
