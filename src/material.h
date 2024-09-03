#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class Material {
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray& in, const HitRecord& record, Vec3& attenuation, Ray& scattered) const;
};

class Lambertian : public Material {
    private:
        Vec3 albedo;

    public:
        Lambertian(const Vec3& albedo);

        bool scatter(const Ray& in, const HitRecord& record, Vec3& attenuation, Ray& scattered) const override;
};

class Metal : public Material {
    private:
        Vec3 albedo;
        double fuzz;

    public:
        Metal(const Vec3& albedo, double fuzz = 0.0);

        bool scatter(const Ray& in, const HitRecord& record, Vec3& attenuation, Ray& scattered) const override;
};

#endif // MATERIAL_H