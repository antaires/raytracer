#include "./Raytracer.h"

Raytracer::~Raytracer(){}

Raytracer::Raytracer(){
  output = new Output();

  scene = new Scene();
  scene->buildScene(objects_list);

  // camera setup
  const auto aspect_ratio = double(image_width) / image_height;
  Vec3 up_direction(0, 1, 0); // level camera
  Vec3 look_from(0, 2, -5);
  Vec3 look_at(0, 0.5, 0);
  double field_of_view(40);
  double aperture(0.1);
  double focus_distance = (look_from - look_at).length();
  camera = new Camera(look_from, look_at, up_direction, field_of_view, aspect_ratio, aperture, 5.0);

}

void Raytracer::run(){
  for(int j = image_height-1; j >= 0; --j){
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for(int i = 0; i < image_width; ++i){
      // take average of many samples randomly within each pixel for antialiasing
      Vec3 color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s){
        auto u = (i + random_double() ) / image_width;
        auto v = (j + random_double() ) / image_height;

        Ray ray = camera->get_ray(u, v);

        color += ray_color(ray, objects_list, ray_depth);
      }
      output->write_color(color, samples_per_pixel);
    }
  }
}

Vec3 Raytracer::ray_color(const Ray& ray, const Object& objects_list, int depth){
  if (depth <= 0){ return Vec3(0, 0, 0); }
  // check for collision with objects in scene - min at 0.001 rather than 0 to avoid 'shadow acne'
  Hit_Record hit_record;
  if ( objects_list.hit(ray, 0.001, infinity, hit_record) ){
    Ray scattered;
    Vec3 attenuation;
    if ( hit_record.material_ptr->scatter(ray, hit_record, attenuation, scattered) ){
      return attenuation * ray_color(scattered, objects_list, depth - 1);
    } else {
      return Vec3(0, 0, 0);
    }
  } else {
    // if no collision : background
    return background_color(ray);
  }
}

Vec3 Raytracer::background_color(const Ray& ray){
  auto t = 0.5 * (ray.unit_direction().y() + 1.0);
  return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.58, 0.36, 0.64);
}
