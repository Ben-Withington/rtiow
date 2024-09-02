#include "sphere.h"
#include <cmath>

Sphere::Sphere(const vec3 &centre, double radius)
    : centre{centre}, radius{std::fmax(0, radius)} {}

bool Sphere::hit(const Ray &r, Interval interval, HitRecord &rec) const {

    vec3 oc{ this->centre - r.origin() };
    double a{ r.direction().length_squared() };
    double h{ dot(r.direction(), oc) };
    double c{ oc.length_squared() - radius * radius };

    double discriminant = h * h - a * c;

    if(discriminant < 0) return false;

    double sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (h - sqrtd) / a;
    if(!interval.surrounds(root)) {
        root = (h + sqrtd) / a;
        if(!interval.surrounds(root)) {
            return false;
        }
    }

    rec.t = root;
    rec.point = r.at(rec.t);
    vec3 outward_normal = (rec.point - this->centre) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}
