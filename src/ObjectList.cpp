#include "./ObjectList.h"

bool ObjectList::bounding_box(double t0, double t1, Aabb& output_box) const {
  if(objects.empty()){return false;}
  Aabb temp_box;
  bool first_true = objects.at(0)->bounding_box(t0, t1, temp_box);
  if (!first_true){
    return false;
  }
  output_box = temp_box;
  for(const auto& object: objects){
    if (!object->bounding_box(t0, t1, temp_box)){return false;}
    output_box = surrounding_box(output_box, temp_box);
  }
  return true;
}

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
