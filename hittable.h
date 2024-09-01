#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
    public:
        vec3 point;
        vec3 normal;
        double t;
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, double ray_t_min, double ray_t_max, hit_record& rec) const = 0;
};

#endif // HITTABLE_H