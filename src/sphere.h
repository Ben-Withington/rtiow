#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
    private:
        vec3 centre;
        double radius;

    public:
        Sphere(const vec3& centre, double radius);

        bool hit(const Ray& r, Interval interval, HitRecord& rec) const override;
};

#endif // SPHERE_H