#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

#include "utility.h"

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

    bool nearZero() const;

    static Vec3 random();
    static Vec3 random(double min, double max);

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

inline Vec3 randomInUnitDisk() {
    while(true) {
        auto p = Vec3{ utility::randomDouble(-1, 1), utility::randomDouble(-1, 1), 0 };
        if(p.length_squared() < 1)
            return p;
    }
}

inline Vec3 randomUnitVector() {
    while(true) {
        Vec3 p = Vec3::random(-1, 1);
        double lensq = p.length_squared();
        if(1e-160 < lensq && lensq <= 1) 
            return p / std::sqrt(lensq);
    }
}

inline Vec3 randomOnHemiSphere(const Vec3& normal) {
    Vec3 onUnitSphere = randomUnitVector();
    return dot(onUnitSphere, normal) > 0.0 ? onUnitSphere : -onUnitSphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etaiOverEtat) {
    double cosTheta = std::fmin(dot(-uv, n), 1.0);
    Vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);
    Vec3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.length_squared())) * n;
    return rOutPerp + rOutParallel;
}

#endif // VEC3_H