#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

bool hitSphere(const point3& center, double radius, const Ray& ray) {
    Vec3 oc{ray.origin() - center};
    auto a{dot(ray.direction(), ray.direction())};
    auto b{2.0 * dot(oc, ray.direction())};
    auto c{dot(oc, oc) - radius * radius};
    auto discriminant{b * b - 4 * a * c};
    return discriminant > 0;
}

color ray_color(const Ray& ray) {
    if (hitSphere(point3(0, 0, -1), 0.5, ray)) return color(1.0, 1.0, 1.0);

    Vec3 unit_direction{unit_vector(ray.direction())};
    auto t{0.5 * (unit_direction.y() + 1.0)};
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const auto aspect_ratio{16.0 / 9.0};
    const int image_width{400};
    const int image_height{static_cast<int>(image_width / aspect_ratio)};

    // Camera

    auto viewport_height{2.0};
    auto viewport_width{aspect_ratio * viewport_height};
    auto focal_length{1.0};

    point3 origin{0.0, 0.0, 0.0};
    Vec3 horizontal{viewport_width, 0.0, 0.0};
    Vec3 vertical{0.0, viewport_height, 0.0};
    auto lower_left_corner{origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length)};

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u{double(i) / (image_width - 1)};
            auto v{double(j) / (image_height - 1)};
            Ray ray{origin, lower_left_corner + u * horizontal + v * vertical - origin};
            color pixel_color{ray_color(ray)};
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";

    // Image

    // const int image_width = 256;
    // const int image_height = 256;


    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // for (int j = image_height - 1; j >= 0; --j) {
        // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        // for (int i = 0; i < image_width; ++i) {
            // color pixel_color{double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25};
            // // std::cout << "pixel_color: " << pixel_color << '\n';
            // write_color(std::cout, pixel_color);
        // }
    // }
    // std::cerr << "\nDone.\n";

    // for (int j = image_height-1; j >= 0; --j) {
        // for (int i = 0; i < image_width; ++i) {
            // auto r = double(i) / (image_width-1);
            // auto g = double(j) / (image_height-1);
            // auto b = 0.25;

            // int ir = static_cast<int>(255.999 * r);
            // int ig = static_cast<int>(255.999 * g);
            // int ib = static_cast<int>(255.999 * b);

            // std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        // }
    // }
}