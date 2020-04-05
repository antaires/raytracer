#ifndef RAY_H
#define RAY_H

#include "./Vec3.h"

class Ray {
    public:
        Vec3 origin_;
        Vec3 direction_;
        Vec3 unit_direction_;

        Ray() {}
        Ray(const Vec3& origin, const Vec3& direction)
            : origin_(origin), direction_(direction), unit_direction_(unit_vector(direction))
        {}

        Vec3 origin() const    { return origin_; }
        Vec3 direction() const { return direction_; }
        Vec3 unit_direction() const { return unit_direction_; }

        Vec3 at(double t) const {
            return origin_ + (t * direction_);
        }

        bool insideSphere(Vec3 surface_normal){
          if ( dot(unit_direction_, surface_normal) > 0.0 ){
            return true;
          }
          return false;
        }
};

#endif
