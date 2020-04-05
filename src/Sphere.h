#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "./Constants.h"
#include "./Object.h"


class Sphere: public Object {
private:
  double radius;
  double r2;
  Vec3 center;
  Vec3 color;
public:
  Sphere(){}
  Sphere(double r, Vec3& pos, Vec3& color);
  virtual bool hit(const Ray& ray, double tmin, double tmax, Hit_Record& rec) const;
};

#endif
