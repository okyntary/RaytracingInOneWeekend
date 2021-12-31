#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
private:
    double xyz[3] {0, 0, 0};

public:
    Vec3(double x, double y, double z) : xyz({x, y, z}) {}

    // Getter methods
    const double getLength() const {
        return std::sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
    }

    const double x() const {return xyz[0];}
    const double y() const {return xyz[1];}
    const double z() const {return xyz[2];}

    // Overloaded operators
    Vec3 operator-() const {
        return {-xyz[0], -xyz[1], -xyz[2]};
    }
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
};

using point3 = Vec3;
using color = Vec3;