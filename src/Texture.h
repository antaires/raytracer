#ifndef TEXTURE_H
#define TEXTURE_H

#include "./Vec3.h"

class Texture{
public:
  virtual Vec3 value(double u, double v, const Vec3& p) const = 0;
};

#endif
