#include "material.h"

bool Material::scatter(const Ray &in, const HitRecord& record, Vec3 &attenuation, Ray &scattered) const {
    return false;
}

Lambertian::Lambertian(const Vec3 &albedo) 
    : albedo{albedo} {}

bool Lambertian::scatter(const Ray &in, const HitRecord& record, Vec3 &attenuation, Ray &scattered) const
{
    Vec3 scatterDirection{ record.normal + randomUnitVector() };

    if(scatterDirection.nearZero())
        scatterDirection = record.normal;

    scattered = Ray{ record.point, scatterDirection };
    attenuation = albedo;
    return true;
}

Metal::Metal(const Vec3 &albedo, double fuzz)
    : albedo{albedo}, fuzz{fuzz < 1.0 ? fuzz : 1.0} {}

bool Metal::scatter(const Ray &in, const HitRecord &record, Vec3 &attenuation, Ray &scattered) const
{
    Vec3 reflected = reflect(in.direction(), record.normal);
    reflected = unit_vector(reflected) + (fuzz * randomUnitVector());
    scattered = Ray(record.point, reflected);  
    attenuation = albedo;
    return dot(scattered.direction(), record.normal) > 0;
}
