#include <iostream>
#include <fstream>
#include "./Vec3.h"
#include "./Ray.h"

Vec3 background_color(const Ray& ray){
  Vec3 unit_direction = unit_vector(ray.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}

int main(int argc, char* args[]){
  const int image_width = 200;
  const int image_height = 100;
  std::ofstream output;
  output.open("output.ppm");

  // drawing to screen using PPM
  Vec3 origin(0.0, 0.0, 0.0);
  Vec3 lower_left_corner(-2.0, -1.0, -1.0);
  Vec3 horizontal(4.0, 0.0, 0.0);
  Vec3 vertical(0.0, 2.0, 0.0);
  output<<"P3\n"<<image_width<<" "<<image_height<<"\n255\n";
  for(int j = image_height-1; j >= 0; --j){
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i < image_width; ++i){
      auto u = double(i) / image_width;
      auto v = double(j) / image_height;
      Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      Vec3 color = background_color(r);
      color.write_color(output);
      //output<<color.x()<<" "<<color.y()<<" "<<color.z()<<"\n";
    }
  }
  output.close();

  return 0;
}
