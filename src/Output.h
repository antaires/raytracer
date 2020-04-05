#ifndef OUTPUT_H
#define OUTPUT_H

#include "./Vec3.h"
#include <iostream>
#include <fstream>

// drawing to screen using PPM
class Output{
private:
  std::ofstream output;
public:
  ~Output(){
    output.close();
  }
  Output(){
    output.open("output.ppm");
    output<<"P3\n"<<image_width<<" "<<image_height<<"\n255\n";
  }

  void write_color(Vec3& color, int samples_per_pixel) {
      // divide color by number of samples and gamma correct for Gamma value 2.0
      auto scale = 1.0 / samples_per_pixel;
      auto r = sqrt(scale * color.r());
      auto g = sqrt(scale * color.g());
      auto b = sqrt(scale * color.b());

      // Write the translated [0,255] value of each color component.
      output << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
          << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
          << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
    //output<<color.x()<<" "<<color.y()<<" "<<color.z()<<"\n";
  }
};

#endif
