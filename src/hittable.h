#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"

class hit_record {
    public:
        vec3 point;
        vec3 normal;
        double t;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal);
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, Interval interval, hit_record& rec) const = 0;
};

#endif // HITTABLE_H