#include "colour.h"
#include "interval.h"
#include <cmath>


namespace render {
    void write_colour(std::ostream& out, const Vec3& pixel_colour) {
        double red   = linearToGamma(pixel_colour.x());
        double green = linearToGamma(pixel_colour.y());
        double blue  = linearToGamma(pixel_colour.z());

        static const Interval intensity{0.000, 0.999};

        int rbyte = static_cast<int>(256 * intensity.clamp(red));
        int gbyte = static_cast<int>(256 * intensity.clamp(green));
        int bbyte = static_cast<int>(256 * intensity.clamp(blue));

        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    }
    double linearToGamma(double linearComponent)
    {
        return (linearComponent > 0) ? std::sqrt(linearComponent) : 0.0;
    }
}