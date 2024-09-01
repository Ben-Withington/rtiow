#include "sphere.h"
#include <cmath>

sphere::sphere(const vec3 &centre, double radius)
    : centre{centre}, radius{std::fmax(0, radius)} {}

bool sphere::hit(const ray &r, double ray_t_min, double ray_t_max, hit_record &rec)
{
    vec3 oc{ centre - r.origin() };
    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() - radius * radius;

    double discriminant = h * h - a * c;

    if(discriminant < 0) return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (h - sqrtd) / a;
    if(root <= ray_t_min || ray_t_max <= root) {
        root = (h + sqrtd) / a;
        if(root <= ray_t_min || ray_t_max <= root) {
            return false;
        }
    }

    rec.t = root;
    rec.point = r.at(rec.t);
    rec.normal = (rec.point - centre) / radius;

    return true;
}
