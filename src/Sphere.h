#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include <memory>
#include "./Constants.h"
#include "./Object.h"


class Sphere: public Object {
private:
  double radius;
  double r2;
  Vec3 center;
  std::shared_ptr<Material> material_ptr;
public:
  Sphere(){}
  Sphere(double r, Vec3& pos, std::shared_ptr<Material> material_ptr);
  virtual bool hit(const Ray& ray, double tmin, double tmax, Hit_Record& rec) const;
  virtual bool bounding_box(double t0, double t1, Aabb& output_box) const;
};

#endif
