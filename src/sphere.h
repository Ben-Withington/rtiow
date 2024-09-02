#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
    private:
        Vec3 centre;
        double radius;
        std::shared_ptr<Material> mat;

    public:
        Sphere(const Vec3& centre, double radius, std::shared_ptr<Material> mat);

        bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;
};

#endif // SPHERE_H