#include <iostream>
#include <cmath>
#include <limits>

#include "vec3.h"
#include "colour.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main() {
    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Vec3{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere>(Vec3{0, -100.5, -1}, 100.0));

    // Camera
    Camera cam{ 16.0 / 9.0, 650 };
    cam.render(world);
}