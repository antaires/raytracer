
#include "./Raytracer.h"
#include <thread>

int main(int argc, char* args[]){

  Raytracer* raytracer = new Raytracer();
  raytracer->run();

  return 0;
}
