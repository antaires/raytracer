#ifndef CHECKERTEXTURE_H
#define CHECKERTEXTURE_H

#include "./Texture.h"
#include "./Vec3.h"
#include <memory>
#include <cmath>

class CheckerTexture : public Texture {
public:
  std::shared_ptr<Texture> odd;
  std::shared_ptr<Texture> even;
  CheckerTexture(){}
  CheckerTexture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1): even(t0), odd(t1) {}

  virtual Vec3 value(double u, double v, const Vec3& point) const {
    auto sines = sin(10 * point.x()) * sin(10 * point.y()) * sin(10 * point.z());
    if (sines < 0){
      return odd->value(u, v, point);
    } else {
      return even->value(u, v, point);
    }
  }
};

#endif
