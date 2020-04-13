#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "./Vec3.h"
#include "./Texture.h"
#include <memory>

class Lambertian : public Material {
  public:
    std::shared_ptr<Texture> albedo;
    Lambertian(std::shared_ptr<Texture> albedo): albedo(albedo) {}

    virtual bool scatter(
      const Ray& ray_in, const Hit_Record& hit_record, Vec3& attenuation, Ray& scattered
    ) const {
      Vec3 scatter_direction = hit_record.surface_normal + random_unit_vector();
      scattered = Ray(hit_record.point, scatter_direction, ray_in.time());
      attenuation = albedo->value(hit_record.u, hit_record.v, hit_record.point);
      return true;

      /* color based on normals
      Vec3 N = hit_record.surface_normal; color = ( 0.5 * Vec3(N.x()+1, N.y()+1, N.z()+1) ); */

      // TWO DIFFERENT OPTIONS
      // use random_unit_vector to achieve a cos(angle from normal) distribution
      // OPTION 1 - true Lambertian Distribution
      //Vec3 target = hit_record.point + hit_record.surface_normal + random_unit_vector();

      // OPTION 2 - intuitive uniform scatter direction for all angles away from hit point
      // with no dependency on angle from normal
      // Vec3 target = hit_record.point + random_in_hemisphere(hit_record.surface_normal);
    }
};

#endif
