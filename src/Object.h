#ifndef OBJECT_H
#define OBJECT_H

// abstract class for anything a ray can hit

struct Hit_Record {
  double t;
  Vec3 p;
  Vec3 surface_normal;
};

class Object{
public:
  virtual bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const = 0;
};


#endif
