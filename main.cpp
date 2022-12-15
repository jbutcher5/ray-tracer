#include "image.hpp"
#include "objects.hpp"
#include <netpbm/pm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int main() {
  const std::string prog_name = "Ray Tracer";

  pm_init(prog_name.c_str(), 0);

  Image img = Image("out.ppm", 128, 128);
  img.WriteImage();

  Ray r = {Vector3(0.f, 0.f, 0.f), Vector3(1.f, 0.f, 0.f)};
  Sphere s = Sphere(Vector3(10.f, 0.f, 0.f), 3.f);

  s.hit(r, nullptr);

  return 0;
}
