#include "hittable_list.h"

hittable_list::hittable_list() {}

hittable_list::hittable_list(std::shared_ptr<hittable> object) {
    this->add(object);
}

void hittable_list::clear() {
    this->objects.clear();
}

void hittable_list::add(std::shared_ptr<hittable> object) {
    this->objects.emplace_back(object);
}

bool hittable_list::hit(const ray &r, double ray_t_min, double ray_t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t_max;

    for(const auto& object : this->objects) {
        if(object->hit(r, ray_t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
