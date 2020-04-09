#include "./Raytracer.h"

Raytracer::~Raytracer(){}

Raytracer::Raytracer(){
  output = new Output();

  // camera setup
  const auto aspect_ratio = double(image_width) / image_height;
  Vec3 up_direction(0, 1, 0); // level camera
  Vec3 look_from(3, 3, 2);
  Vec3 look_at(0, 0, -1);
  double field_of_view(20);
  double aperture(2.0);
  double focus_distance = (look_from - look_at).length();
  camera = new Camera(look_from, look_at, up_direction, field_of_view, aspect_ratio, aperture, focus_distance);

  // build sscene
  Vec3 pos(0.0, 0.0, -1.0);
  Vec3 albedo(0.1, 0.2, 0.5);
  auto lambertian = std::make_shared<Lambertian>(albedo);
  auto sphere_ptr = std::make_shared<Sphere>(0.5, pos, lambertian);
  objects_list.add(sphere_ptr);

  Vec3 pos1(0.0, -100.5, -1.0);
  Vec3 albedo2(0.8, 0.8, 0.0);
  auto lambertian1 = std::make_shared<Lambertian>(albedo2);
  auto sphere_ptr1 = std::make_shared<Sphere>(100.0, pos1, lambertian1);
  objects_list.add(sphere_ptr1);

  //Metal
  Vec3 albedo3(0.8, 0.6, 0.2);
  auto metal = std::make_shared<Metal>(albedo3, 0.0);
  Vec3 pos3(1.0, 0, -1.0);
  auto sphere_ptr3 = std::make_shared<Sphere>(0.5, pos3, metal);
  objects_list.add(sphere_ptr3);

  auto glass = std::make_shared<Dielectric>(1.5);
  Vec3 pos4(-1.0, 0, -1.0);
  auto sphere_ptr4 = std::make_shared<Sphere>(0.45, pos4, glass);
  objects_list.add(sphere_ptr4);

}

int Raytracer::run(){
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
  return 0;
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
  return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}
