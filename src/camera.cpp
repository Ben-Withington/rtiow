#include "camera.h"
#include "colour.h"

Camera::Camera(double aspectRatio, int imageWidth)
    : aspectRatio{aspectRatio}, imageWidth{imageWidth} {}

void Camera::render(const Hittable& world) {
    this->initialise();

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = 0; j < imageHeight; ++j) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for(int i = 0; i < imageWidth; ++i) {

            Vec3 pixelCentre = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
            Vec3 rayDirection = pixelCentre - centre;
            Ray r{centre, rayDirection};

            render::write_colour(std::cout, this->rayColour(r, world));
        }
    }

    std::clog << "\rDone.                 \n";
}

void Camera::initialise() {
    imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = std::max(1, imageHeight);

    centre = { 0, 0, 0 };

    double focalLength = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

    Vec3 viewportU{ viewportWidth, 0, 0};
    Vec3 viewportV{ 0, -viewportHeight, 0};

    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    Vec3 viewportUpperLeft{ centre - Vec3{0, 0, focalLength } - viewportU / 2 - viewportV / 2};
    pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
}

Vec3 Camera::rayColour(const Ray &r, const Hittable &world) const
{
    HitRecord rec;

    if(world.hit(r, { 0, std::numeric_limits<double>::infinity() }, rec)) {
        return 0.5 * (rec.normal + Vec3{ 1, 1, 1 });
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Vec3(1.0, 1.0, 1.0) + a * Vec3(0.5, 0.7, 1.0);
}
