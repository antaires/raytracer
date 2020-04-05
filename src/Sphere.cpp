#include "./Sphere.h"

Sphere::Sphere(double r, Vec3& pos, std::shared_ptr<Material> material_ptr): radius(r), center(pos), r2(radius * radius), material_ptr(material_ptr){}

bool Sphere::hit(const Ray& ray, double tmin, double tmax, Hit_Record& rec) const {
  // number of roots == number of collisions (ie 2 is ray hitting on entrance and exit)
  // IF root < 0, intersection happens BEHIND ORIGIN (offscreen)
  double t0, t1;
  Vec3 L = ray.origin() - center;
  double a = dot(ray.unit_direction(), ray.unit_direction());
  double b = 2 * dot(ray.unit_direction(), L);
  double c = dot(L, L) - r2;
  if ( !quadratic(a, b, c, t0, t1) ){
    return false;
  }
  if ( t0 > t1){
    double temp = t0;
    t0 = t1;
    t1 = temp;
  }
  if (t0 < tmin){
    t0 = t1;
  }
  if (t0 < tmax && t0 > tmin){
    rec.time = t0;
    rec.point = ray.at(t0);
    rec.surface_normal = unit_vector(rec.point - center);
    rec.material_ptr = material_ptr;
    return true;
  }
  return false;
}
