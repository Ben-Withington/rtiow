#include <iostream>
#include <cmath>
#include <limits>
#include <memory>

#include "vec3.h"
#include "colour.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main() {
    // World
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = utility::randomDouble();
            Vec3 centre(a + 0.9 * utility::randomDouble(), 0.2, b + 0.9 * utility::randomDouble());

            if ((centre - Vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Vec3::random() * Vec3::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(centre, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Vec3::random(0.5, 1);
                    auto fuzz = utility::randomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(centre, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(centre, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Vec3(4, 1, 0), 1.0, material3));

    // Camera
    Camera cam{ 16.0 / 9.0, 854, 250, 50, 20, { 13, 2, 3 }, { 0, 0, 0 }, { 0, 1, 0 }, 0.6, 10.0 };
    cam.render(world);
}