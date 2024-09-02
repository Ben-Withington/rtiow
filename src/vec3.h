#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vec3 {
private:
    double vertices[3];

public:
    Vec3();
    Vec3(double v1, double v2, double v3);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vec3& operator+=(const Vec3& vec);
    Vec3& operator*=(double scalar);
    Vec3& operator/=(double scalar);

    double length() const;
    double length_squared() const;

    friend std::ostream& operator<<(std::ostream& out, const Vec3& vec);
};

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    return { u[0] + v[0], u[1] + v[1], u[2] + v[2] };
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
    return { u[0] - v[0], u[1] - v[1], u[2] - v[2] };
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
    return { u[0] * v[0], u[1] * v[1], u[2] * v[2] };
}

inline Vec3 operator*(double scalar, const Vec3& v) {
    return { scalar * v[0], scalar * v[1], scalar * v[2] };
}

inline Vec3 operator*(const Vec3& v, double scalar) {
    return scalar * v;
}

inline Vec3 operator/(const Vec3& v, double scalar) {
    return (1 / scalar) * v;
}

inline double dot(const Vec3& u, const Vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
    return { 
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
    };
}

inline Vec3 unit_vector(const Vec3& vec) {
    return vec / vec.length();
}

#endif // VEC3_H