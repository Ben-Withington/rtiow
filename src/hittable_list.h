#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
    public:
        std::vector<std::shared_ptr<Hittable>> objects{};

        HittableList();
        HittableList(std::shared_ptr<Hittable> object);

        void clear();
        void add(std::shared_ptr<Hittable> object);
        
        bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;
};

#endif // HITTABLE_LIST_H