#pragma once

#include "ray.h"

struct Hit_Record {
    point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vec3& outward_normal) {
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

// Abstract class/interface for anything that might be hit by a Ray
class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const = 0;
};