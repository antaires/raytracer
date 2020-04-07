#ifndef DIELECTRIC_H
#define DIELECTRIC_H

class Dielectric : public Material {
public:
  double refractive_index;
  Dielectric(double ri) : refractive_index(ri){}
  virtual bool scatter(
    const Ray& ray_in, const Hit_Record& hit_record, Vec3& attenuation, Ray& scattered
  ) const {
    attenuation = Vec3(1.0, 1.0, 1.0);
    double etai_over_etat;
    if(hit_record.front_face){
      etai_over_etat = 1.0 / refractive_index;
    } else {
      etai_over_etat = refractive_index;
    }

    Vec3 unit_direction = unit_vector(ray_in.direction());
    double cos_theta = ffmin(dot(-unit_direction, hit_record.surface_normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    if (etai_over_etat * sin_theta > 1.0){
      // must reflect
      Vec3 reflected = reflect(unit_direction, hit_record.surface_normal);
      scattered = Ray(hit_record.point, reflected);
      return true;
    }
    // schlick simple version of complex form.
    double reflect_prob = schlick(cos_theta, etai_over_etat);
    if (random_double() < reflect_prob){
      Vec3 reflected = reflect(unit_direction, hit_record.surface_normal);
      scattered = Ray(hit_record.point, reflected);
      return true;
    }
    // refract
    Vec3 refracted = refract(unit_direction, hit_record.surface_normal, etai_over_etat);
    scattered = Ray(hit_record.point, refracted);
    return true;

    // NOTE: negative radius on sphere gives a hollow bubble, because geometry
    // unaffected but surface normal points inward
  }
};

#endif
