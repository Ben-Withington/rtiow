#include "hittable_list.h"

HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> object) {
    this->add(object);
}

void HittableList::clear() {
    this->objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object) {
    this->objects.emplace_back(object);
}

bool HittableList::hit(const Ray& r, Interval interval, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = interval.max;

    for(const auto& object : this->objects) {
        if(object->hit(r, Interval{ interval.min, closest_so_far }, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
