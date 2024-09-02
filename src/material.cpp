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

Metal::Metal(const Vec3 &albedo)
    : albedo{albedo} {}

bool Metal::scatter(const Ray &in, const HitRecord &record, Vec3 &attenuation, Ray &scattered) const
{
    Vec3 reflected = reflect(in.direction(), record.normal);
    scattered = Ray(record.point, reflected);  
    attenuation = albedo;
    return true;
}
