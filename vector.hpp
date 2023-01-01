#pragma once
#include <stdio.h>

class Vector3 {
public:
  float x;
  float y;
  float z;

  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3() {}
  Vector3 Normalize();

  Vector3 operator+(Vector3 v) { return Vector3(x + v.x, y + v.y, z + v.z); }
  Vector3 operator-(Vector3 v) { return *this + v * -1; }
  Vector3 operator*(Vector3 v) { return Vector3(x * v.x, y * v.y, z * v.z); }
  Vector3 operator/(Vector3 v) { return Vector3(x / v.x, y / v.y, z / v.z); }

  void operator+=(Vector3 v) { *this = *this + v; }
  void operator-=(Vector3 v) { *this = *this - v; }
  void operator*=(Vector3 v) { *this = *this * v; }
  void operator/=(Vector3 v) { *this = *this / v; }

  Vector3 operator+(float k) { return Vector3(x + k, y + k, z + k); }
  Vector3 operator-(float k) { return Vector3(x - k, y - k, z - k); }
  Vector3 operator*(float k) { return Vector3(x * k, y * k, z * k); }
  Vector3 operator/(float k) { return Vector3(x / k, y / k, z / k); }

  void operator+=(float k) { *this = *this + k; }
  void operator-=(float k) { *this = *this - k; }
  void operator*=(float k) { *this = *this * k; }
  void operator/=(float k) { *this = *this / k; }

  static Vector3 Random(float min, float max);
  Vector3 Lerp(Vector3 v, float scale) { return *this + (v - *this) * scale; }
  float Dot(Vector3 v);
  float Length();
  float LengthSquared();
  char *Debug();
};
