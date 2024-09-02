#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    private:
        vec3 centre;
        double radius;

    public:
        sphere(const vec3& centre, double radius);

        bool hit(const ray& r, double ray_t_min, double ray_t_max, hit_record& rec) const override;
};

#endif // SPHERE_H