#ifndef SCENE_H
#define SCENE_H

#include "./Constants.h"
#include "./Vec3.h"
#include "./Sphere.h"
#include "./Object.h"
#include "./ObjectList.h"
#include "./Material.h"
#include "./Metal.h"
#include "./Lambertian.h"
#include "./Dielectric.h"

class Scene{
public:
  Scene(){}
  void buildScene(ObjectList& objects_list){

    // scene with random spheres

    // ground
    Vec3 pos0(0,-1000,0);
    Vec3 albedo0(0.1, 0.5, 0.8);
    auto lambertian0 = std::make_shared<Lambertian>(albedo0);
    auto sphere_ptr0 = std::make_shared<Sphere>(1000, pos0, lambertian0);
    objects_list.add(sphere_ptr0);
    // main ball
    Vec3 pos1(0,1,0);
    Vec3 albedo1(0.8, 0.5, 0.2);
    auto metal0 = std::make_shared<Metal>(albedo1, 0.0);
    auto sphere_ptr1 = std::make_shared<Sphere>(1.0, pos1, metal0);
    objects_list.add(sphere_ptr1);
    // first ring
    double arrX[] = {-1.25, -1.25,  1.25, 1.25};
    double arrZ[] = {-1.25,  1.25, -1.25, 1.25};
    for(int i = 0; i < 4; ++i){
      Vec3 pos1(arrX[i],0.5,arrZ[i]);
      Vec3 albedo1(random_double(0.5, 1), random_double(0, 0.5), random_double());
      auto metal1 = std::make_shared<Metal>(albedo1, 0.2);
      auto sphere_ptr1 = std::make_shared<Sphere>(0.5, pos1, metal1);
      objects_list.add(sphere_ptr1);
    }
    /*
    // second ring
    double arrX2[] = {-1.95, -1.95,  1.95, 1.95};
    double arrZ2[] = {-1.95,  1.95, -1.95, 1.95};
    for(int i = 0; i < 4; ++i){
      Vec3 pos1(arrX2[i],0.4,arrZ2[i]);
      auto glass = std::make_shared<Dielectric>(1.5);
      auto sphere_ptr1 = std::make_shared<Sphere>(0.4, pos1, glass);
      objects_list.add(sphere_ptr1);
    }*/

    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_vec() * random_vec();
                    auto lambertian = std::make_shared<Lambertian>(albedo);
                    auto sphere_ptr = std::make_shared<Sphere>(0.2, center, lambertian);
                    objects_list.add(sphere_ptr);

                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_vec(.5, 1);
                    auto fuzz = random_double(0, .5);
                    auto metal = std::make_shared<Metal>(albedo, fuzz);
                    auto sphere_ptr = std::make_shared<Sphere>(0.2, center, metal);
                    objects_list.add(sphere_ptr);

                } else {
                    // glass
                    auto glass = std::make_shared<Dielectric>(1.5);
                    auto sphere_ptr = std::make_shared<Sphere>(0.2, center, glass);
                    objects_list.add(sphere_ptr);
                }
            }
        }
    }

    /*
    Vec3 pos1(0, 1, 0);
    auto dielectric1 = std::make_shared<Dielectric>(1.5);
    auto sphere_ptr1 = std::make_shared<Sphere>(1.0, pos1, dielectric1);
    objects_list.add(sphere_ptr1);

    Vec3 pos2(-4, 1, 0);
    Vec3 albedo2(0.4, 0.2, 0.1);
    auto lambertian2 = std::make_shared<Lambertian>(albedo0);
    auto sphere_ptr2 = std::make_shared<Sphere>(1.0, pos2, lambertian2);
    objects_list.add(sphere_ptr2);

    Vec3 pos3(4, 1, 0);
    Vec3 albedo3(0.7, 0.6, 0.5);
    auto metal1 = std::make_shared<Metal>(albedo3, 0.0);
    auto sphere_ptr3 = std::make_shared<Sphere>(1.0, pos3, metal1);
    objects_list.add(sphere_ptr3);
    /*

    /* SCENE 1
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
    */
  }
};

#endif
