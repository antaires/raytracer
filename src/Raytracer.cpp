#include "./Raytracer.h"

Raytracer::~Raytracer(){}

Raytracer::Raytracer(){
  output = new Output();

  // build scene
  Vec3 pos(0.0, 0.0, -1.0);
  Vec3 color(50.0, 50.0, 50.0);
  Sphere sphere(0.5, pos, color);
  spheres.push_back(sphere);
}

int Raytracer::run(){
  // drawing to screen using PPM
  Vec3 origin(0.0, 0.0, 0.0);
  Vec3 lower_left_corner(-2.0, -1.0, -1.0);
  Vec3 horizontal(4.0, 0.0, 0.0);
  Vec3 vertical(0.0, 2.0, 0.0);

  for(int j = image_height-1; j >= 0; --j){
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i < image_width; ++i){

      auto u = double(i) / image_width;
      auto v = double(j) / image_height;
      Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
      Vec3 color;

      // check for collision with objects in scene
      for(auto s: spheres){
        if (s.hasCollision(ray)){
          color = Vec3(1.0, 0.0, 0.0);
        } else {
          // if no collision : background
          color = background_color(ray);
        }
      }

      output->write_color(color);
    }
  }
  return 0;
}

Vec3 Raytracer::background_color(const Ray& ray){
  Vec3 unit_direction = unit_vector(ray.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}
