#pragma once

#include "vec3.h"

class Ray {
public:
    point3 ori;
    Vec3 dir;
    
public:
    Ray() {}

    Ray(const point3& origin, const Vec3& direction) : ori(origin), dir(direction) {}

    point3 origin() const {return ori;}

    Vec3 direction() const {return dir;}

    point3 at(double t) const {
        return ori + t * dir;
    }
};