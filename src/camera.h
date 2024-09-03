#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "ray.h"

class Camera {
    public:
        Camera(double aspectRatio   = 1.0, 
                int imageWidth      = 100, 
                int samplesPerPixel = 10, 
                int maxDepth        = 10, 
                double vfov         = 90,
                Vec3 lookfrom       = { 0, 0, 0 },
                Vec3 lookat         = { 0, 0, 0 },
                Vec3 up             = { 0, 1, 0 }
        );

        void render(const Hittable& world);

    private:
        double aspectRatio;
        int imageWidth;
        int samplesPerPixel;
        int imageHeight;
        Vec3 centre;
        Vec3 pixel00Location;
        Vec3 pixelDeltaU;
        Vec3 pixelDeltaV;
        int maxDepth;
        double vfov;
        Vec3 lookfrom;
        Vec3 lookat;
        Vec3 up;

        void initialise();
        Vec3 rayColour(const Ray& r, const Hittable& world, int depth) const;
        Ray getRay(int i, int j) const;
        Vec3 sampleSqure() const;
};

#endif // CAMERA_H