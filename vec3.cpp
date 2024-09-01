#include <cmath>
#include "vec3.h"

vec3::vec3() : vertices{0, 0, 0} {}

vec3::vec3(double v1, double v2, double v3)
    : vertices{v1, v2, v3} {}

double vec3::x() const { return vertices[0]; }
double vec3::y() const { return vertices[1]; }
double vec3::z() const { return vertices[2]; }

vec3 vec3::operator-() const {
    return { -vertices[0], -vertices[1], -vertices[2] };
}

double vec3::operator[](int i) const {
    return vertices[i];
}

double& vec3::operator[](int i) {
    return vertices[i];
}

vec3& vec3::operator+=(const vec3& vec) {
    vertices[0] += vec.x();
    vertices[1] += vec.y();
    vertices[2] += vec.z();
    return *this;
}

vec3& vec3::operator*=(double scalar) {
    vertices[0] *= scalar;
    vertices[1] *= scalar;
    vertices[2] *= scalar;
    return *this;
}

vec3& vec3::operator/=(double scalar) {
    return *this *= 1/scalar;
}

double vec3::length() const {
    return std::sqrt(length_squared());
}

double vec3::length_squared() const {
    return vertices[0] * vertices[0] + 
            vertices[1] * vertices[1] + 
            vertices[2] * vertices[2];
}

std::ostream& operator<<(std::ostream& out, const vec3& vec) {
    out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
    return out;
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return { u[0] + v[0], u[1] + v[1], u[2] + v[2] };
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return { u[0] - v[0], u[1] - v[1], u[2] - v[2] };
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return { u[0] * v[0], u[1] * v[1], u[2] * v[2] };
}

inline vec3 operator*(double scalar, const vec3& v) {
    return { scalar * v[0], scalar * v[1], scalar * v[2] };
}

inline vec3 operator*(const vec3& v, double scalar) {
    return scalar * v;
}

inline vec3 operator/(const vec3& v, double scalar) {
    return (1 / scalar) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return { 
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
    };
}

inline vec3 unit_vector(const vec3& vec) {
    return vec / vec.length();
}