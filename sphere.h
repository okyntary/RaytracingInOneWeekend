#pragma once

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
public:
    point3 center;
    double radius;
    shared_ptr<Material> mat_ptr;

public:
    Sphere() {};
    Sphere(point3 center, double radius, shared_ptr<Material> mat_ptr)
    : center(center), radius(radius), mat_ptr(mat_ptr) {};

    virtual bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const override;
};

bool Sphere::hit(const Ray& ray, double t_min, double t_max, Hit_Record& rec) const {
    Vec3 oc{ray.origin() - center};
    auto a{ray.direction().length_squared()};
    auto half_b{dot(oc, ray.direction())};
    auto c{oc.length_squared() - radius * radius};

    auto discriminant{half_b * half_b - a * c};

    if (discriminant < 0) return false;
    auto sqrtd{sqrt(discriminant)};

    // Find the nearest root that lies within the acceptable range
    auto root{(-half_b - sqrtd) / a};
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max) return false;
    }

    rec.t = root;
    rec.p = ray.at(rec.t);
    Vec3 outward_normal{(rec.p - center) / radius};
    rec.set_face_normal(ray, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}
