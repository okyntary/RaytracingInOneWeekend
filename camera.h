#pragma once

#include "rtconstants.h"

class Camera {
public:
    point3 origin{};
    point3 lower_left_corner{};
    Vec3 horizontal{};
    Vec3 vertical{};

public:
    Camera() {
        const auto aspect_ratio{16.0 / 9.0};
        auto viewport_height{2.0};
        auto viewport_width{aspect_ratio * viewport_height};
        auto focal_length{1.0};

        origin = {0.0, 0.0, 0.0};
        horizontal = {viewport_width, 0.0, 0.0};
        vertical = {0.0, viewport_height, 0.0};
        lower_left_corner = {origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length)};
    }

    Ray get_ray(double u, double v) {
        return {origin, lower_left_corner + u * horizontal + v * vertical};
    }
};