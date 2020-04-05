#include "./Sphere.h"

Sphere::Sphere(double r, Vec3& pos, Vec3& color): radius(r), center(pos), color(color), r2(radius * radius){}

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
    rec.t = t0;
    rec.p = ray.at(t0);
    rec.surface_normal = unit_vector(rec.p - center);
    return true;
  }
  return false;
}

bool Sphere::quadratic(const double& a, const double& b, const double& c, double& x0, double& x1) const {
  double discr = b * b - 4 * a * c;
  if (discr < 0){return false;}
  else if (discr == 0){
    x0 = x1 = -0.5 * b / a;
  }
  else {
    double q = (b > 0) ?
      -0.5 * (b + sqrt(discr)) :
      -0.5 * (b - sqrt(discr));
    x0 = q / a;
    x1 = c / q;
  }
  return true;
}
