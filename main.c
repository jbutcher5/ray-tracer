#include "vector.h"
#include <netpbm/ppm.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Vector3 position;
  Vector3 direction;
} Ray;

int main() {
  Vector3 v = {1.f, 3.f, 5.f};

  char *v_debug = Vector3Debug(&v);
  printf("%s\n", v_debug);
  free(v_debug);

  return 0;
}
