#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    private:
        vec3 m_origin;
        vec3 m_direction;
    
    public:
        Ray();
        Ray(const vec3& origin, const vec3& direction);

        const vec3& origin() const;
        const vec3& direction() const;

        vec3 at(double t) const;
};

#endif // RAY_H