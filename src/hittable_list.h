#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable {
    public:
        std::vector<std::shared_ptr<hittable>> objects{};

        hittable_list();
        hittable_list(std::shared_ptr<hittable> object);

        void clear();
        void add(std::shared_ptr<hittable> object);
        
        bool hit(const ray& r, double ray_t_min, double ray_t_max, hit_record& rec) const override;
};

#endif // HITTABLE_LIST_H