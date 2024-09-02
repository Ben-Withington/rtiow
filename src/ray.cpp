#include "ray.h"

Ray::Ray() {}

Ray::Ray(const vec3 &origin, const vec3 &direction)
    : m_origin{origin}, m_direction{direction} {}

const vec3& Ray::origin() const
{
    return m_origin;
}

const vec3& Ray::direction() const {
    return m_direction;
}

vec3 Ray::at(double t) const {
    return m_origin + (t * m_direction);
}
