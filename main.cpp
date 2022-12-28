#include "image.hpp"
#include "objects.hpp"
#include "vector.hpp"
#include "world.hpp"
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <string>

int main() {
  const std::string prog_name = "Ray Tracer";
  const std::string fp = "out.ppm";

  pm_init(prog_name.c_str(), 0);

  World world = World(fp, 960, 540, 1);

  Sphere s = Sphere(Vector3(0.f, 0.f, 12.f), 3.f);
  Sphere s2 = Sphere(Vector3(0.f, -103.f, 12.f), 100.f);

  world.AddObject(&s);
  world.AddObject(&s2);

  world.DrawScene();
  world.WriteImage();

  return 0;
}
