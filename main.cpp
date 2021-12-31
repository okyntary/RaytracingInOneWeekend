#include <iostream>

#include "rtconstants.h"

#include "camera.h"
#include "color.h"

#include "material.h"

#include "hittable_list.h"
#include "sphere.h"

///////////

color ray_color(const Ray& ray, const Hittable& world, int depth) {
    Hit_Record rec;

    // std::cerr << "Depth is " << depth << '\n';
    if (depth <= 0) {
        return {0.0, 0.0, 0.0};
    }

    if (world.hit(ray, 0.001, infinity, rec)) {
        Ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(ray, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return {0.0, 0.0, 0.0};
    }

    Vec3 unit_direction{unit_vector(ray.direction())};
    auto t{0.5 * (unit_direction.y() + 1.0)};
    return (1.0 - t) * color{1.0, 1.0, 1.0} + t * color{0.5, 0.7, 1.0};
}

int main() {
    // Image
    const auto aspect_ratio{16.0 / 9.0};
    const int image_width{400};
    const int image_height{static_cast<int>(image_width / aspect_ratio)};
    const int samples_per_pixel{100};
    const int max_depth{50};

    // World
    Hittable_List world;

    auto material_ground{make_shared<Lambertian>(color(0.8, 0.8, 0.0))};
    auto material_center{make_shared<Lambertian>(color(0.7, 0.3, 0.3))};
    auto material_left{make_shared<Dielectric>(1.5)};
    auto material_right{make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0)};

    world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    Camera cam;

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j{image_height - 1}; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i{0}; i < image_width; ++i) {
            color pixel_color{0, 0, 0};
            for (int s{0}; s < samples_per_pixel; ++s) {
                auto u{(i + random_double()) / (image_width - 1)};
                auto v{(j + random_double()) / (image_height - 1)};
                Ray r{cam.get_ray(u, v)};
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";

    return EXIT_SUCCESS;
}