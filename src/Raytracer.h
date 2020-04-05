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
#include <memory>

class Raytracer{
public:
  Output* output;
  Camera* camera;
  ObjectList objects_list;
  ~Raytracer();
  Raytracer();
  int run();
private:
  Vec3 background_color(const Ray& ray);
  Vec3 ray_color(const Ray& ray, const Object& object, int depth);
};

#endif
