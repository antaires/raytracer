#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>

class Material {
public:
  virtual bool scatter(
    const Ray& ray_in, const Hit_Record& hit_record, Vec3& attenuation, Ray& scattered
  ) const = 0;

  double schlick(double cosine, double ref_idx){
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow(1 - cosine, 5);
  }
};

#endif
