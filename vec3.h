#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class vec3 {
private:
    double vertices[3];

public:
    vec3();
    vec3(double v1, double v2, double v3);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator+=(const vec3& vec);
    vec3& operator*=(double scalar);
    vec3& operator/=(double scalar);

    double length() const;
    double length_squared() const;

    friend std::ostream& operator<<(std::ostream& out, const vec3& vec);
};

inline vec3 operator+(const vec3& u, const vec3& v);
inline vec3 operator-(const vec3& u, const vec3& v);
inline vec3 operator*(const vec3& u, const vec3& v);
inline vec3 operator*(double scalar, const vec3& v);
inline vec3 operator*(const vec3& v, double scalar);
inline vec3 operator/(const vec3& u, const vec3& v);

inline double dot(const vec3& u, const vec3& v);
inline vec3 cross(const vec3& u, const vec3& v);
inline vec3 unit_vector(const vec3& v);

#endif // VEC3_H