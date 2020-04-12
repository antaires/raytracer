#include "./Aabb.h"

// improved hit function from Andrew Kensler at Pixar
inline bool Aabb::hit(const Ray& ray, double tmin, double tmax) const {
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / ray.direction()[a];
        auto t0 = (min()[a] - ray.origin()[a]) * invD;
        auto t1 = (max()[a] - ray.origin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;
        if (tmax <= tmin)
            return false;
    }
    return true;
}
