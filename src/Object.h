#ifndef OBJECT_H
#define OBJECT_H

#include "./Vec3.h"
#include "./Ray.h"
#include <memory>

// abstract class for anything a ray can hit

class Material; // alert compiler that material_ptr is to a class

struct Hit_Record {
  double time;
  Vec3 point;
  Vec3 surface_normal;
  std::shared_ptr<Material> material_ptr;
};

class Object{
public:
  virtual bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const = 0;
};


#endif
