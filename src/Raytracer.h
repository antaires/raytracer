#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
#include "./Constants.h"
#include "./Vec3.h"
#include "./Ray.h"
#include "./Output.h"
#include "./Sphere.h"
#include "./Object.h"
#include "./ObjectList.h"
#include "./Camera.h"
#include "./Scene.h"
#include "./Material.h"
#include "./Metal.h"
#include "./Lambertian.h"
#include "./Dielectric.h"
#include <memory>

class Raytracer{
public:
  Output output;
  Camera camera;
  Scene scene;
  ObjectList objects_list;
  ~Raytracer();
  Raytracer();
  void run();
private:
  Vec3 background_color(const Ray& ray);
  Vec3 ray_color(const Ray& ray, const Object& object, int depth);
};

#endif
