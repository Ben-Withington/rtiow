#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    private:
        Vec3 m_origin;
        Vec3 m_direction;
    
    public:
        Ray();
        Ray(const Vec3& origin, const Vec3& direction);

        const Vec3& origin() const;
        const Vec3& direction() const;

        Vec3 at(double t) const;
};

#endif // RAY_H