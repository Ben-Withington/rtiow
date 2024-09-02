#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>

#include "ray.h"
#include "interval.h"

class Material;

class HitRecord {
    public:
        Vec3 point;
        Vec3 normal;
        double t;
        bool front_face;
        std::shared_ptr<Material> mat;

        void set_face_normal(const Ray& r, const Vec3& outward_normal);
};

class Hittable {
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& r, Interval interval, HitRecord& rec) const = 0;
};

#endif // HITTABLE_H