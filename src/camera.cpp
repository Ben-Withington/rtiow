#include "camera.h"
#include "colour.h"
#include "utility.h"
#include "material.h"

Camera::Camera(double aspectRatio, 
                int imageWidth, 
                int samplesPerPixel, 
                int maxDepth, 
                double vfov,
                Vec3 lookfrom,
                Vec3 lookat,
                Vec3 up
)
    : aspectRatio{aspectRatio}, 
        imageWidth{imageWidth}, 
        samplesPerPixel{samplesPerPixel}, 
        maxDepth{maxDepth}, 
        vfov{vfov},
        lookat{lookat},
        lookfrom{lookfrom},
        up{up}
{}

void Camera::render(const Hittable& world) {
    this->initialise();

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = 0; j < imageHeight; ++j) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for(int i = 0; i < imageWidth; ++i) {
            
            Vec3 pixelColour{ 0, 0, 0 };

            for(int sample{ 0 }; sample < samplesPerPixel; ++sample) {
                Ray r{ this->getRay(i, j) };
                pixelColour += this->rayColour(r, world, maxDepth);
            }

            render::write_colour(std::cout, pixelColour / static_cast<double>(samplesPerPixel));
        }
    }

    std::clog << "\rDone.                 \n";
}

void Camera::initialise() {
    imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = std::max(1, imageHeight);

    centre = lookfrom;

    double focalLength = (lookfrom - lookat).length();
    auto theta = utility::degToRad(vfov);
    auto h = std::tan(theta / 2);
    double viewportHeight = 2 * h * focalLength;
    double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    Vec3 w = unit_vector(lookfrom - lookat);
    Vec3 u = unit_vector(cross(up, w));
    Vec3 v = cross(w, u);

    Vec3 viewportU = viewportWidth * u;
    Vec3 viewportV = viewportHeight * -v;

    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    Vec3 viewportUpperLeft{ centre - (focalLength * w) - viewportU / 2 - viewportV / 2};
    pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
}

Vec3 Camera::rayColour(const Ray &r, const Hittable &world, int depth) const
{
    if(depth <= 0) return { 0, 0, 0 };

    HitRecord rec;

    if(world.hit(r, { 0.001, std::numeric_limits<double>::infinity() }, rec)) {
        Ray scattered{};
        Vec3 attenuation{};
        if(rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * rayColour(scattered, world, depth -1);
        }
        return { 0, 0 , 0 };
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Vec3(1.0, 1.0, 1.0) + a * Vec3(0.2, 0.2, 1.0);
}

Ray Camera::getRay(int i, int j) const
{
    Vec3 offset = sampleSqure();
    Vec3 pixelSample = pixel00Location 
                        + ((i + offset.x()) * pixelDeltaU) 
                        + ((j + offset.x()) * pixelDeltaV);
    
    return {centre, pixelSample - centre};
}

Vec3 Camera::sampleSqure() const {
    return { utility::randomDouble() - 0.5, utility::randomDouble() - 0.5, 0};
}
