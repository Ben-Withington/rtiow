#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    private:
        vec3 m_origin;
        vec3 m_direction;
    
    public:
        ray();
        ray(const vec3& origin, const vec3& direction);

        const vec3& origin() const;
        const vec3& direction() const;

        vec3 at(double t) const;
};

#endif // RAY_H