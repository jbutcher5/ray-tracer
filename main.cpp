#include "image.hpp"
#include "materials.hpp"
#include "objects.hpp"
#include "scene.hpp"
#include "vector.hpp"
#include <cstdlib>
#include <ctime>
#include <netpbm/pm.h>
#include <netpbm/ppm.h>
#include <string>

int main() {
  const std::string prog_name = "Ray Tracer";
  const std::string fp = "out.ppm";

  pm_init(prog_name.c_str(), 0);
  srand48(time(NULL));

  Scene scene = Scene(fp, 1920, 1080, 16);

  Diffuse d;
  PartialDiffuse m = PartialDiffuse(0.1);

  Sphere s = Sphere(Vector3(0.f, 0.f, -12.f), 3.f, &d);
  Sphere s2 = Sphere(Vector3(0.f, -103.f, -12.f), 100.f, &m);

  scene.AddObject(&s);
  scene.AddObject(&s2);

  scene.DrawScene();
  scene.WriteImage();

  return 0;
}
