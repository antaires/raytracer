#include "./MovingSphere.h"

Vec3 MovingSphere::center(double time) const {
  return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool MovingSphere::bounding_box(double t0, double t1, Aabb& output_box) const {
  // take the box of sphere at t0 and box of sphere at t1 and compute box of both
  Aabb box0(
    center(t0) - Vec3(radius, radius, radius)
    , center(t0) + Vec3(radius, radius, radius));
  Aabb box1(
    center(t1) - Vec3(radius, radius, radius)
    , center(t1) + Vec3(radius, radius, radius));
  output_box = surrounding_box(box0, box1);
  return true;
}

bool MovingSphere::hit(const Ray& ray, double t_min, double t_max, Hit_Record& rec) const {
  Vec3 oc = ray.origin() - center(ray.time());
  auto a = ray.direction().length_squared();
  auto half_b = dot(oc, ray.direction());
  auto c = oc.length_squared() - radius*radius;
  auto discriminant = half_b*half_b - a*c;

  if (discriminant > 0) {
      auto root = sqrt(discriminant);
      auto temp = (-half_b - root)/a;
      if (temp < t_max && temp > t_min) {
          rec.time = temp;
          rec.point = ray.at(rec.time);
          Vec3 outward_normal = (rec.point - center(ray.time())) / radius;
          rec.set_face_normal(ray, outward_normal);
          rec.material_ptr = material_ptr;
          return true;
      }
      temp = (-half_b + root) / a;
      if (temp < t_max && temp > t_min) {
          rec.time = temp;
          rec.point = ray.at(rec.time);
          Vec3 outward_normal = (rec.point - center(ray.time())) / radius;
          rec.set_face_normal(ray, outward_normal);
          rec.material_ptr = material_ptr;
          return true;
      }
  }
  return false;
}
