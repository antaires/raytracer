#include <iostream>
#include <fstream>
#include "./Vec3.h"

int main(int argc, char* args[]){

  std::ofstream output;
  output.open("output.ppm");

  // drawing to screen -> using PPM
  int nx = 200;
  int ny = 100;
  output<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
  for(int j = ny-1; j >= 0; j--){
    for(int i = 0; i < nx; i++){
      Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
      int ir = int(255.99*col.x());
      int ig = int(255.99*col.y());
      int ib = int(255.99*col.z());
      output<<ir<<" "<<ig<<" "<<ib<<"\n";
    }
  }
  output.close();

  return 0;
}
