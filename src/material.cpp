#include "material.h"
#include "utility.h"

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

double Dielectric::reflectance(double cosine, double refractionIndex)
{
    auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

Dielectric::Dielectric(double refractionIndex)
    : refractionIndex{refractionIndex} {}

bool Dielectric::scatter(const Ray &in, const HitRecord &record, Vec3 &attenuation, Ray &scattered) const
{
    attenuation = Vec3{1.0, 1.0, 1.0};
    double ri = record.front_face ? (1.0 / refractionIndex) : refractionIndex;

    Vec3 unitDirection = unit_vector(in.direction());
    double cosTheta = std::fmin(dot(-unitDirection, record.normal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = ri * sinTheta > 1.0;
    Vec3 scatter{};

    if(cannotRefract || reflectance(cosTheta, ri) > utility::randomDouble())
        scatter = reflect(unitDirection, record.normal);
    else
        scatter = refract(unitDirection, record.normal, ri);

    scattered = Ray{record.point, scatter};
    return true; 
}
