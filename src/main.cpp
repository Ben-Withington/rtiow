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

    auto material_ground = std::make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Vec3(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Dielectric>(1.5);
    auto material_bubble   = std::make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = std::make_shared<Metal>(Vec3(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Vec3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(std::make_shared<Sphere>(Vec3( 1.0,    0.0, -1.0),   0.5, material_right));

    // Camera
    Camera cam{ 16.0 / 9.0, 854, 100, 50, 20, {-2, 2, 1}, { 0, 0, -1}, { 0, 1, 0} };
    cam.render(world);
}