#ifndef CONSTANTTEXTURE_H
#define CONSTANTTEXTURE_H

#include "./Texture.h"

class ConstantTexture : public Texture {
public:
  Vec3 color;
  ConstantTexture(){}
  ConstantTexture(Vec3 color) : color(color) {}
  virtual Vec3 value(double u, double v, const Vec3& p) const {
    return color;
  }
};

#endif
