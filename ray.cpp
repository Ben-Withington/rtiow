#include "ray.h"

ray::ray()
{
}

ray::ray(const vec3 &origin, const vec3 &direction)
{
}

const vec3& ray::origin() const
{
    return m_origin;
}

const vec3& ray::direction() const
{
    return m_direction;
}

vec3 ray::at(double t) const
{
    return m_origin + (t * m_direction);
}
