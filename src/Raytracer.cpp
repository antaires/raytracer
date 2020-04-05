#include "./Raytracer.h"

Raytracer::~Raytracer(){}

Raytracer::Raytracer(){
  output = new Output();
  camera = new Camera();

  // build scene
  Vec3 pos(0.0, 0.0, -1.0);
  Vec3 color(50.0, 50.0, 50.0);
  auto sphere_ptr = std::make_shared<Sphere>(0.5, pos, color);
  objects_list.add(sphere_ptr);
  Vec3 pos1(0.0, -100.5, -1.0);
  Vec3 color1(50.0, 50.0, 50.0);
  auto sphere_ptr1 = std::make_shared<Sphere>(100.0, pos1, color1);
  objects_list.add(sphere_ptr1);
}

int Raytracer::run(){

  for(int j = image_height-1; j >= 0; --j){
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i < image_width; ++i){

      // take many samples randomly within each pixel for blur
      Vec3 color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s){
        auto u = (i + random_double() ) / image_width;
        auto v = (j + random_double() ) / image_height;
        Ray ray = camera->get_ray(u, v);

        // check for collision with objects in scene
        Hit_Record hit_record;
        double tmin = 0, tmax = 1000;
        if ( objects_list.hit(ray, tmin, tmax, hit_record) ){
          // use surface normals for shading
          Vec3 N = hit_record.surface_normal;
          // color based on normal
          color += ( 0.5 * Vec3(N.x()+1, N.y()+1, N.z()+1) );
        } else {
          // if no collision : background
          color += background_color(ray);
        }
      }

      output->write_color(color, samples_per_pixel);
    }
  }
  return 0;
}

Vec3 Raytracer::background_color(const Ray& ray){
  auto t = 0.5 * (ray.unit_direction().y() + 1.0);
  return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}
