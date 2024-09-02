#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

#include <iostream>

namespace render {
    void write_colour(std::ostream& out, const Vec3& pixel_colour);
    double linearToGamma(double linearComponent);
}

#endif // COLOUR_H