
#ifndef VEC3_H
#define VEC3_H
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include <iostream>
#include <cmath>
#include "./Constants.h"

class Vec3 {
  public:
      Vec3() : e{0,0,0} {}
      Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

      double x() const { return e[0]; }
      double y() const { return e[1]; }
      double z() const { return e[2]; }

      double r() const { return e[0]; }
      double g() const { return e[1]; }
      double b() const { return e[2]; }


      Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
      double operator[](int i) const { return e[i]; }
      double& operator[](int i) { return e[i]; }

      Vec3& operator+=(const Vec3 &v) {
          e[0] += v.e[0];
          e[1] += v.e[1];
          e[2] += v.e[2];
          return *this;
      }

      Vec3& operator*=(const double t) {
          e[0] *= t;
          e[1] *= t;
          e[2] *= t;
          return *this;
      }

      Vec3& operator/=(const double t) {
          return *this *= 1/t;
      }

      double length() const {
          return sqrt(length_squared());
      }

      double length_squared() const {
          return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
      }

  public:
      double e[3];
};


// Vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
  return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) {
  return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
  return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
  return u.e[0] * v.e[0]
       + u.e[1] * v.e[1]
       + u.e[2] * v.e[2];
}

inline static Vec3 cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(Vec3 v) {
  return v / v.length();
}

// vector utility
inline Vec3 random_vec(){
  return Vec3(random_double(), random_double(), random_double());
}

inline Vec3 random_vec(double min, double max){
  return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

inline Vec3 random_unit_vector(){
  auto a = random_double(0, 2 * pi);
  auto z = random_double(-1, 1);
  auto r = sqrt(1 - z * z);
  return Vec3(r * cos(a), r * sin(a), z);
}

inline Vec3 random_in_unit_sphere(){
  // a rejection method for finding random point unit square
  while (true) {
    auto point = random_vec(-1, 1);
    if (point.length_squared() >= 1) continue;
    return point;
  }
}

inline Vec3 random_in_hemisphere(const Vec3& normal){
  Vec3 in_unit_sphere = random_in_unit_sphere();
  if (dot(in_unit_sphere, normal) > 0.0) {
    // in same hemisphere as normal
    return in_unit_sphere;
  } else {
    return -in_unit_sphere;
  }
}

inline Vec3 reflect(const Vec3& v, const Vec3& n){
  return v - 2 * dot(v, n) * n;
}

#endif
