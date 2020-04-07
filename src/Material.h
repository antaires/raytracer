#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>

class Material {
public:
  virtual bool scatter(
    const Ray& ray_in, const Hit_Record& hit_record, Vec3& attenuation, Ray& scattered
  ) const = 0;
};

#endif
