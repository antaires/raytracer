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

  void write_color(Vec3& color) {
      // Write the translated [0,255] value of each color component.
      output << static_cast<int>(255.999 * color.r()) << ' '
          << static_cast<int>(255.999 * color.g()) << ' '
          << static_cast<int>(255.999 * color.b()) << '\n';
    //output<<color.x()<<" "<<color.y()<<" "<<color.z()<<"\n";
  }
};

#endif
