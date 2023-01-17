#include "image/image.hpp"
#include "math_utils/vector.hpp"
#include "objects/materials.hpp"
#include "objects/objects.hpp"
#include "objects/parse_obj.hpp"
#include "scene/scene.hpp"
#include <cstdio>
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

  Scene scene = Scene(fp, 1920, 1080, 1);

  std::vector<Object *> teapot = LoadObj("teapot.obj", Vector3(0, 1.f, -3.f));
  for (auto triangle : teapot)
    scene.AddObject(triangle);

  scene.DrawScene();
  scene.WriteImage();

  return 0;
}
