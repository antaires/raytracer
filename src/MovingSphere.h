#ifndef MOVINGSPHERE_H
#define MOVINGSPHERE_H

#include <cmath>
#include <memory>
#include "./Constants.h"
#include "./Object.h"

class MovingSphere : public Object {
public:
  Vec3 center0, center1;
  double time0, time1;
  double radius;
  std::shared_ptr<Material> material_ptr;

  MovingSphere(){}
  MovingSphere(double r, Vec3 center0, Vec3 center1, double t0, double t1, std::shared_ptr<Material> mat):
    center0(center0), center1(center1), time0(t0), time1(t1), radius(r), material_ptr(mat) {}

  virtual bool hit(const Ray& ray, double t_min, double t_max, Hit_Record& rec) const;
  virtual bool bounding_box(double t0, double t1, Aabb& output_box) const;
  Vec3 center(double time) const;

};

#endif
