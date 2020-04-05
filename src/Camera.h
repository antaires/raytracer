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

  Camera(){
    origin = Vec3(0.0, 0.0, 0.0);
    lower_left_corner = Vec3(-2.0, -1.0, -1.0);
    horizontal = Vec3(4.0, 0.0, 0.0);
    vertical = Vec3(0.0, 2.0, 0.0);
  }
  Ray get_ray(double u, double v){
    Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
    return ray;
  }

};

#endif
