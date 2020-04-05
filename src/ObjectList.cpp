#include "./ObjectList.h"

bool ObjectList::hit(const Ray& r, double tmin, double tmax, Hit_Record& rec) const {
  Hit_Record temp_rec;
  bool hit_anything = false;
  double closest_so_far = tmax;
  for(const auto& object : objects){
    if ( object->hit(r, tmin, closest_so_far, temp_rec) ){
      hit_anything = true;
      closest_so_far = temp_rec.time;
      rec = temp_rec;
    }
  }
  return hit_anything;
}
