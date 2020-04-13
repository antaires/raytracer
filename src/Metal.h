#ifndef METAL_H
#define METAL_H

#include "./Vec3.h"
#include "./Texture.h"
#include <memory>

class Metal : public Material {
  public:
    std::shared_ptr<Texture> albedo;
    double fuzz;
    Metal(std::shared_ptr<Texture> albedo, double fuzz): albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1){}

    virtual bool scatter(
      const Ray& ray_in, const Hit_Record& hit_record, Vec3& attenuation, Ray& scattered
    ) const {
      Vec3 reflected = reflect(unit_vector(ray_in.direction()), hit_record.surface_normal);
      scattered = Ray(hit_record.point, reflected + fuzz * random_in_unit_sphere(), ray_in.time());
      attenuation = albedo->value(hit_record.u, hit_record.v, hit_record.point);
      return (dot(scattered.direction(), hit_record.surface_normal) > 0);
    }
};

#endif
