#include "image.hpp"
#include "objects.hpp"
#include "vector.hpp"
#include "world.hpp"
#include <cstdio>
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <string>

int main() {
  const std::string prog_name = "Ray Tracer";
  const std::string fp = "out.ppm";

  pm_init(prog_name.c_str(), 0);

  World world = World(fp, 960, 540);

  Sphere s = Sphere(Vector3(0.f, 0.f, 5.f), 3.f);
  Sphere s2 = Sphere(Vector3(5.f, 0.f, 20.f), 15.f);

  world.AddObject(&s);
  world.AddObject(&s2);

  Vector3 rand = Vector3::Random(-1.f, 1.f);

  world.DrawScene();
  world.WriteImage();

  return 0;
}
