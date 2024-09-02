#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "ray.h"

class Camera {
    public:
        Camera(double aspectRatio = 1.0, int imageWidth = 100, int  = 10);

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

        void initialise();
        Vec3 rayColour(const Ray& r, const Hittable& world) const;
        Ray getRay(int i, int j) const;
        Vec3 sampleSqure() const;
};

#endif // CAMERA_H