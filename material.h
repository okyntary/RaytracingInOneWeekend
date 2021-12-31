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
    double fuzz;

public:
    Metal(color a, double f) : albedo(a), fuzz(f) {}

    virtual bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const override {
        Vec3 reflected{reflect(unit_vector(r_in.direction()), rec.normal)};
        scattered = {rec.p, reflected + fuzz * random_in_unit_sphere()};
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
};

class Dielectric : public Material {
public:
    double ir; // Index of refration
public:
    Dielectric(double ir) : ir(ir) {}

    virtual bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const override {
        attenuation = color{1.0, 1.0, 1.0};
        double refraction_ratio{rec.front_face ? (1.0 / ir) : ir};

        Vec3 unit_direction{unit_vector(r_in.direction())};
        double cos_theta{fmin(dot(-unit_direction, rec.normal), 1.0)};
        double sin_theta{std::sqrt(1.0 - cos_theta * cos_theta)};

        bool cannot_refract{refraction_ratio * sin_theta > 1.0};

        Vec3 direction;
        if (cannot_refract) direction = reflect(unit_direction, rec.normal);
        else direction = refract(unit_direction, rec.normal, refraction_ratio);

        scattered = {rec.p, direction};
        return true;
    }
};