#pragma once

#include "rtconstants.h"
#include "hittable.h"

struct Hit_Record;

// Abstract class to implement interface for materials
class Material {
public:
    virtual bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
    color albedo;
public:
    Lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const override {
        auto scatter_direction{rec.normal + random_unit_vector()};
        // Catch degenrate scatter dimension
        if (scatter_direction.near_zero()) scatter_direction = rec.normal;

        scattered = {rec.p, scatter_direction};
        attenuation = albedo;
        return true;
    }
};

class Metal : public Material {
public:
    color albedo;
public:
    Metal(color a) : albedo(a) {}

    virtual bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const override {
        Vec3 reflected{reflect(unit_vector(r_in.direction()), rec.normal)};
        scattered = {rec.p, reflected};
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
};