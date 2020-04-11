#ifndef CAMERA_H
#define CAMERA_H

#include "./Ray.h"
#include "./Vec3.h"

class Camera {
public:
  Vec3 origin;
  Vec3 lower_left_corner;
  Vec3 horizontal;
  Vec3 vertical;
  Vec3 u, v, w;
  double lens_radius;
  double time0, time1; // shutter open/close times

  Camera() = default;
  void set_up(Vec3 look_from, Vec3 look_at, Vec3 view_up
            , double field_of_view, double aspect_ratio, double aperture, double focus_distance
            , double t0 = 0, double t1 = 0){
    origin = look_from;
    lens_radius = aperture / 2;
    time0 = t0;
    time1 = t1;

    // specify in degrees and convert to radians
    auto theta = degrees_to_radians(field_of_view); // top to bottom in degrees
    auto half_height = std::tan(theta / 2);
    auto half_width = aspect_ratio * half_height;
    w = unit_vector(look_from - look_at);
    u = unit_vector( cross(view_up, w) );
    v = cross(w, u);
    lower_left_corner = origin
                      - half_width * focus_distance * u
                      - half_height * focus_distance * v
                      - focus_distance * w;
    horizontal = 2 * half_width * focus_distance * u;
    vertical = 2 * half_height * focus_distance * v;
  }

  Ray get_ray(double s, double t) {
      Vec3 rd = lens_radius * random_in_unit_disk();
      Vec3 offset = u * rd.x() + v * rd.y();
      return Ray(
          origin + offset
          , lower_left_corner + s*horizontal + t*vertical - origin - offset
          , random_double(time0, time1)
      );
  }

};

#endif
