#ifndef AABB_H
#define AABB_H

#include "./Vec3.h"
#include "./Ray.h"

class Aabb {
public:
  Vec3 _min;
  Vec3 _max;

  Aabb(){}
  Aabb(const Vec3& a, const Vec3& b){_min = a; _max = b;}
  Vec3 min() const {return _min;}
  Vec3 max() const {return _max;}
  bool hit(const Ray& ray, double t_min, double t_max) const;
};

inline Aabb surrounding_box(Aabb box0, Aabb box1){
  Vec3 small(ffmin(box0.min().x(), box1.min().x()),
             ffmin(box0.min().y(), box1.min().y()),
             ffmin(box0.min().z(), box1.min().z()));
  Vec3 big  (ffmax(box0.max().x(), box1.max().x()),
             ffmax(box0.max().y(), box1.max().y()),
             ffmax(box0.max().z(), box1.max().z()));
  return Aabb(small,big);
}

#endif
