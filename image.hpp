#pragma once
#include <netpbm/ppm.h>
#include <string>

class Image {
private:
  pixel **pixels;
  const int columns;
  const int rows;
  const std::string file_path;

public:
  Image(const std::string fp, const int cols, const int rows)
      : columns(cols), rows(rows), file_path(fp) {
    pixels = ppm_allocarray(cols, rows);
  }
  ~Image() { ppm_freearray(pixels, rows); }
  void WriteImage();
};