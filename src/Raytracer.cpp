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
      // take average of many samples randomly within each pixel for blur
      Vec3 color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s){
        auto u = (i + random_double() ) / image_width;
        auto v = (j + random_double() ) / image_height;
        Ray ray = camera->get_ray(u, v);
        color += ray_color(ray, objects_list, 20);
      }
      output->write_color(color, samples_per_pixel);
    }
  }
  return 0;
}

Vec3 Raytracer::ray_color(const Ray& ray, const Object& objects_list, int depth){
  Hit_Record hit_record;
  // stop once max depth reached
  if (depth <= 0){ return Vec3(0, 0, 0); }
  // check for collision with objects in scene
  Vec3 color(0, 0, 0);
  // start at 0.001 rather than 0 to avoid 'shadow acne'
  if ( objects_list.hit(ray, 0.001, infinity, hit_record) ){
    /* color based on normals
    Vec3 N = hit_record.surface_normal; color = ( 0.5 * Vec3(N.x()+1, N.y()+1, N.z()+1) ); */

    // TWO DIFFERENT OPTIONS
    // use random_unit_vector to achieve a cos(angle from normal) distribution
    // OPTION 1 - true Lambertian Distribution
    Vec3 target = hit_record.point + hit_record.surface_normal + random_unit_vector();

    // OPTION 2 - intuitive uniform scatter direction for all angles away from hit point
    // with no dependency on angle from normal
    // Vec3 target = hit_record.point + random_in_hemisphere(hit_record.surface_normal);

    return 0.5 * ray_color(Ray(hit_record.point, target - hit_record.point), objects_list, depth - 1);
  } else {
    // if no collision : background
    return background_color(ray);
  }
}

Vec3 Raytracer::background_color(const Ray& ray){
  auto t = 0.5 * (ray.unit_direction().y() + 1.0);
  return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}
