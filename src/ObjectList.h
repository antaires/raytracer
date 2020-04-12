#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "./Object.h"
#include <memory>
#include <vector>

class ObjectList : public Object {
public:
  std::vector<std::shared_ptr<Object>> objects;
  ObjectList(){}
  ObjectList(std::shared_ptr<Object> object){ add(object); }

  void clear(){ objects.clear();}
  void add(std::shared_ptr<Object> object){ objects.push_back(object); }
  virtual bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const;
  virtual bool bounding_box(double t0, double t1, Aabb& output_box) const;
};


#endif
