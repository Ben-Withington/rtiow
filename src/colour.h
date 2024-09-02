#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

#include <iostream>

namespace render {
    void write_colour(std::ostream& out, const vec3& pixel_colour);
}

#endif // COLOUR_H