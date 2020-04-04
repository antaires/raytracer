#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "./Vec3.h"
#include "./Ray.h"

class Sphere{
private:
  double radius;
  double r2;
  Vec3 position;
  Vec3 color;

  bool quadratic(const double& a, const double& b, const double& c, double& x0, double& x1){
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

public:
  Sphere(double r, Vec3& pos, Vec3& color): radius(r), position(pos), color(color){
    r2 = radius * radius;
  }

  double hasCollision(Ray ray){
    // number of roots == number of collisions (ie 2 is ray hitting on entrance and exit)
    // IF root < 0, intersection happens BEHIND ORIGIN (offscreen)
    double t0, t1;
    Vec3 L = ray.origin() - position;
    double a = dot(ray.unit_direction(), ray.unit_direction());
    double b = 2 * dot(ray.unit_direction(), L);
    double c = dot(L, L) - r2;
    if ( !quadratic(a, b, c, t0, t1) ){
      return -1;
    }
    if ( t0 > t1){
      double temp = t0;
      t0 = t1;
      t1 = temp;
    }
    if (t0 < 0){
      t0 = t1;
      if (t0 < 0){return -1;} // neither intersections are on screen
    }
    return t0;
  }

  Vec3 surface_normal(Ray& ray, double t){
    // for sphere, outward normal = direction of hit point minus center
    return ray.at(t) - position;
  }

};







#endif
