#include "stdlib.h"
#include "stdio.h"

typedef struct {
  float x;
  float y;
  float z;
} Vector3;

typedef struct {
  Vector3 position;
  Vector3 direction;
} Ray;

Vector3 Vector3Add(Vector3 v1, Vector3 v2) {
  return (Vector3){.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z};
}

char* Vector3Debug(Vector3 *v) {
  char* buffer = malloc(128*sizeof(char)); 
  sprintf(buffer, "%f %f %f", v->x, v->y, v->z);
  return buffer;
} 

int main() {
  Vector3 v = {1.f, 3.f, 5.f};

  char* v_debug = Vector3Debug(&v);
  printf("%s\n", v_debug);
  free(v_debug);

  return 0;
}
