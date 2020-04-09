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

  Camera(Vec3 look_from, Vec3 look_at, Vec3 view_up, double field_of_view, double aspect_ratio){
    origin = look_from;
    // specify in degrees and convert to radians
    auto theta = degrees_to_radians(field_of_view); // top to bottom in degrees
    auto half_height = std::tan(theta / 2);
    auto half_width = aspect_ratio * half_height;
    Vec3 w = unit_vector(look_from - look_at);
    Vec3 u = unit_vector( cross(view_up, w) );
    Vec3 v = cross(w, u);
    lower_left_corner = origin - half_width * u - half_height * v - w;
    horizontal = 2 * half_width * u;
    vertical = 2 * half_height * v;
  }

  Ray get_ray(double u, double v){
    Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    return ray;
  }

};

#endif
