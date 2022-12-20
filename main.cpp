#include "camera.hpp"
#include "image.hpp"
#include "objects.hpp"
#include "vector.hpp"
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int main() {
  const std::string prog_name = "Ray Tracer";
  const std::string fp = "out.ppm";

  pm_init(prog_name.c_str(), 0);

  Camera camera = Camera(fp, 960, 540);

  Sphere s = Sphere(Vector3(0.f, 0.f, 10.f), 3.f);

  camera.DrawScene(&s);
  camera.WriteImage();

  return 0;
}
