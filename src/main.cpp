#include <iostream>
#include <cmath>
#include <limits>

#include "vec3.h"
#include "colour.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

vec3 ray_colour(const Ray& r, const Hittable& world);

int main() {
    // Image
    double aspect_ratio{ 16.0 / 9.0 };
    int image_width{ 400 };

    // Calculate image height, ensure that it's at least 1
    int image_height{ static_cast<int>(image_width / aspect_ratio) };
    image_height = (image_height < 0) ? 1 : image_height;

    // World

    HittableList world;
    world.add(std::make_shared<Sphere>(vec3{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere>(vec3{0, -100.5, -1}, 100.0));

    // Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_centre = vec3{0, 0 , 0};

    vec3 viewport_u = vec3{viewport_width, 0, 0};
    vec3 viewport_v = vec3{0, -viewport_height, 0};

    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    vec3 viewport_upper_left = camera_centre
                                - vec3{0, 0, focal_length}
                                - viewport_u / 2
                                - viewport_v / 2;
    vec3 pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for(int i = 0; i < image_width; ++i) {

            vec3 pixel_centre = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_centre - camera_centre;
            Ray r{camera_centre, ray_direction};

            vec3 pixel_colour = ray_colour(r, world);

            render::write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.                 \n";
}

vec3 ray_colour(const Ray& r, const Hittable& world) {
    HitRecord rec;

    if(world.hit(r, { 0, std::numeric_limits<double>::infinity() }, rec)) {
        return 0.5 * (rec.normal + vec3{ 1, 1, 1 });
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}