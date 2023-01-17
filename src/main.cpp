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

  Scene scene = Scene(fp, 480, 270, 4);

  Diffuse centre = Diffuse(Colour(0.7f, 0.3f, 0.3f));
  Mirror left = Mirror(Colour(0.8f, 0.8f, 0.8f));
  PartialDiffuse right = PartialDiffuse(0.1, Colour(0.8f, 0.6f, 0.2f));
  Diffuse ground = Diffuse(Colour(0.8f, 0.8f, 0.0f));

  Sphere s = Sphere(Vector3(0.f, 0.f, -12.f), 3.f, &centre);
  Sphere s2 = Sphere(Vector3(6.f, -0.1f, -12.f), 3.f, &right);
  Sphere s3 = Sphere(Vector3(-6.f, -0.1f, -12.f), 3.f, &left);
  Sphere s4 = Sphere(Vector3(0.f, -103.f, -12.f), 100.f, &ground);

  Vector3 vertices[3] = {Vector3(-6.f, -2.f, -12.f), Vector3(6.f, -2.f, -12.f),
                         Vector3(0.f, 9.f, -12.f)};

  std::vector<Object *> cube = LoadObj(
      "/home/james/dev/C++/ray-tracer/teapot.obj", Vector3(0.f, 0.f, 12.f));

  for (auto triangle : cube)
    scene.AddObject(triangle);

  // scene.AddObject(&s);
  // scene.AddObject(&s2);
  // scene.AddObject(&s3);
  // scene.AddObject(&s4);

  scene.DrawScene();
  scene.WriteImage();

  return 0;
}
