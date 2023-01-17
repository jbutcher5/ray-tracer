#include "objects/parse_obj.hpp"
#include "math_utils/vector.hpp"
#include "objects/materials.hpp"
#include "objects/objects.hpp"
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <vector>

#define PREFIX(pre, str) (strncmp((pre), (str), strlen((pre))) == 0)

/* Load object file data into mesh */
std::vector<Object *> LoadObj(const char *fname) {
  FILE *f = fopen(fname, "r");
  char buf[128];

  std::vector<Vector3> vertex_positions;
  std::vector<Vector3> vertex_normals;
  std::vector<Object *> faces;

  /* Count number of vertices, vertex normals, texture coords and faces */
  while (fgets(buf, 128, f)) {
    Vector3 v;

    if (PREFIX("v ", buf)) {
      sscanf(buf, "v %f %f %f", &v.x, &v.y, &v.z);
      vertex_positions.push_back(v);
    }
    if (PREFIX("vn ", buf)) {
      sscanf(buf, "vn %f %f %f", &v.z, &v.y, &v.z);
      vertex_normals.push_back(v);
    }
    if (PREFIX("f ", buf)) {
      int vi[3];
      int ni[3];
      int ti[3];
      sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d", vi, ti, ni, vi + 1, ti + 1,
             ni + 1, vi + 2, ti + 2, ni + 2);

      Vector3 *points = new Vector3[3]{vertex_positions[vi[0] - 1],
                                       vertex_positions[vi[1] - 1],
                                       vertex_positions[vi[2] - 1]};

      Triangle *t = new Triangle(points, new Diffuse(Colour(0.7f, 0.3f, 0.3f)));

      faces.push_back(t);
    }
  }

  return faces;
}
