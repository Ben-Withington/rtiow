#include <cmath>
#include "vec3.h"

Vec3::Vec3() : vertices{0, 0, 0} {}

Vec3::Vec3(double v1, double v2, double v3)
    : vertices{v1, v2, v3} {}

double Vec3::x() const { return vertices[0]; }
double Vec3::y() const { return vertices[1]; }
double Vec3::z() const { return vertices[2]; }

Vec3 Vec3::operator-() const {
    return { -vertices[0], -vertices[1], -vertices[2] };
}

double Vec3::operator[](int i) const {
    return vertices[i];
}

double& Vec3::operator[](int i) {
    return vertices[i];
}

Vec3& Vec3::operator+=(const Vec3& vec) {
    vertices[0] += vec.x();
    vertices[1] += vec.y();
    vertices[2] += vec.z();
    return *this;
}

Vec3& Vec3::operator*=(double scalar) {
    vertices[0] *= scalar;
    vertices[1] *= scalar;
    vertices[2] *= scalar;
    return *this;
}

Vec3& Vec3::operator/=(double scalar) {
    return *this *= 1/scalar;
}

double Vec3::length() const {
    return std::sqrt(length_squared());
}

double Vec3::length_squared() const {
    return vertices[0] * vertices[0] + 
            vertices[1] * vertices[1] + 
            vertices[2] * vertices[2];
}

std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
    out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
    return out;
}