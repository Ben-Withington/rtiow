#include "colour.h"
#include "interval.h"


namespace render {
    void write_colour(std::ostream& out, const Vec3& pixel_colour) {
        double red   = pixel_colour.x();
        double green = pixel_colour.y();
        double blue  = pixel_colour.z();

        static const Interval intensity{0.000, 0.999};

        int rbyte = static_cast<int>(256 * intensity.clamp(red));
        int gbyte = static_cast<int>(256 * intensity.clamp(green));
        int bbyte = static_cast<int>(256 * intensity.clamp(blue));

        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    }
}