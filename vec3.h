#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
public:
    double xyz[3] {0, 0, 0};

public:
    Vec3(double x = 0.0, double y = 0.0, double z = 0.0) : xyz{x, y, z} {}

    // Getter methods
    const double length() const {
        return std::sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
    }

    const double length_squared() const {
        return xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2];
    }

    const double x() const {return xyz[0];}
    const double y() const {return xyz[1];}
    const double z() const {return xyz[2];}

    // Overloaded operators
    Vec3 operator-() const {return {-xyz[0], -xyz[1], -xyz[2]};}
    double operator[](int i) const {return xyz[i];}
    double& operator[](int i) {return xyz[i];}

    Vec3& operator+=(const Vec3& v2) {
        xyz[0] += v2[0];
        xyz[1] += v2[1];
        xyz[2] += v2[2];
        return *this;
    }

    Vec3& operator*=(const double k) {
        xyz[0] *= k;
        xyz[1] *= k;
        xyz[2] *= k;
        return *this;
    }

    Vec3& operator/=(const double k) {
        *this *= 1/k;
        return *this;
    }

    inline static Vec3 random() {
        return {random_double(), random_double(), random_double()};
    }

    inline static Vec3 random(double min, double max) {
        return {random_double(min, max), random_double(min, max), random_double(min, max)};
    }
};

using point3 = Vec3;
using color = Vec3;

// Vec3 utility functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
    return out << vec.xyz[0] << ' ' << vec.xyz[1] << ' ' << vec.xyz[2];
}

inline Vec3 operator+(const Vec3& vec1, const Vec3& vec2) {
    return {vec1.xyz[0] + vec2.xyz[0], vec1.xyz[1] + vec2.xyz[1], vec1.xyz[2] + vec2.xyz[2]};
}

inline Vec3 operator-(const Vec3& vec1, const Vec3& vec2) {
    return {vec1.xyz[0] - vec2.xyz[0], vec1.xyz[1] - vec2.xyz[1], vec1.xyz[2] - vec2.xyz[2]};
}

inline Vec3 operator*(const Vec3& vec1, const Vec3& vec2) {
    return {vec1.xyz[0] * vec2.xyz[0], vec1.xyz[1] * vec2.xyz[1], vec1.xyz[2] * vec2.xyz[2]};
}

inline Vec3 operator*(double k, const Vec3& vec) {
    return {k * vec.xyz[0], k * vec.xyz[1], k * vec.xyz[2]};
}

inline Vec3 operator*(const Vec3& vec, double k) {
    return k * vec;
}

inline Vec3 operator/(const Vec3& vec, double t) {
    return (1/t) * vec;
}

inline double dot(const Vec3& vec1, const Vec3& vec2) {
    return vec1.xyz[0] * vec2.xyz[0] + vec1.xyz[1] * vec2.xyz[1] + vec1.xyz[2] * vec2.xyz[2];
}

inline Vec3 cross(const Vec3& vec1, const Vec3& vec2) {
    return {vec1.xyz[1] * vec2.xyz[2] - vec1.xyz[2] * vec2.xyz[1],
            vec1.xyz[2] * vec2.xyz[0] - vec1.xyz[0] * vec2.xyz[2],
            vec1.xyz[0] * vec2.xyz[1] - vec1.xyz[1] * vec2.xyz[0]};
}

inline Vec3 unit_vector(Vec3 vec) {
    return vec / vec.length();
}

Vec3 random_in_unit_sphere() {
    while (true) {
        auto p{Vec3::random(-1.0, 1.0)};
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_hemisphere(const Vec3 normal) {
    Vec3 in_unit_sphere{random_in_unit_sphere()};
    if (dot(normal, in_unit_sphere) > 0.0) return in_unit_sphere;
    else return -in_unit_sphere;
}