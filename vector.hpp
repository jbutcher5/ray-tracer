#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float x;
  float y;
  float z;
} Vector3;

Vector3 Vector3Add(Vector3 v1, Vector3 v2);
float Vector3Length(Vector3 v);
char *Vector3Debug(Vector3 *v);
