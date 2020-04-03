#ifndef RAY_H
#define RAY_H

#include "./Vec3.h"

class Ray {
    public:
        Vec3 origin_;
        Vec3 direction_;

        Ray() {}
        Ray(const Vec3& origin, const Vec3& direction)
            : origin_(origin), direction_(direction)
        {}

        Vec3 origin() const    { return origin_; }
        Vec3 direction() const { return direction_; }

        Vec3 at(double t) const {
            return origin_ + t * direction_;
        }
};

#endif
