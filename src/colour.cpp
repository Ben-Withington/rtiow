#include "colour.h"


namespace render {
    void write_colour(std::ostream& out, const Vec3& pixel_colour) {
        double red   = pixel_colour.x();
        double green = pixel_colour.y();
        double blue  = pixel_colour.z();

        int rbyte = static_cast<int>(255.999 * red);
        int gbyte = static_cast<int>(255.999 * green);
        int bbyte = static_cast<int>(255.999 * blue);

        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    }
}