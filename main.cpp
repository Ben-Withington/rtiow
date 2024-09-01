#include <iostream>
#include <cmath>

#include "vec3.h"
#include "colour.h"
#include "ray.h"

vec3 ray_colour(const ray& r);
double hit_sphere(const vec3& centre, double radius, const ray& r);

int main() {
    // Image
    double aspect_ratio{ 16.0 / 9.0 };
    int image_width{ 400 };

    // Calculate image height, ensure that it's at least 1
    int image_height{ static_cast<int>(image_width / aspect_ratio) };
    image_height = (image_height < 0) ? 1 : image_height;

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
            ray r{camera_centre, ray_direction};

            vec3 pixel_colour = ray_colour(r);

            render::write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.                 \n";
}

vec3 ray_colour(const ray& r) {
    double t = hit_sphere(vec3( 0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 n = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * vec3{n.x() + 1, n.y() + 1, n.z() + 1};
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}

double hit_sphere(const vec3& centre, double radius, const ray& r) {
    vec3 oc = centre - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if(discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}