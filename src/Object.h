#ifndef OBJECT_H
#define OBJECT_H

#include "./Vec3.h"
#include "./Ray.h"
#include "./Aabb.h"
#include <memory>

// abstract class for anything a ray can hit

class Material; // alert compiler that material_ptr is to a class

struct Hit_Record {
  double time;
  Vec3 point;
  Vec3 surface_normal;
  bool front_face;
  std::shared_ptr<Material> material_ptr;

  inline void set_face_normal(const Ray& ray, const Vec3& outward_normal){
    // normals in this program are always opp direction of ray
    front_face = dot(ray.direction(), outward_normal) < 0;
    surface_normal = front_face ? outward_normal : -outward_normal;
  }
};

class Object{
public:
  virtual bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const = 0;
  virtual bool bounding_box(double t0, double t1, Aabb& output_box) const = 0;
};


#endif
