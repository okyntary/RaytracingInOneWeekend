#pragma once

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity{std::numeric_limits<double>::infinity()};
const double pi{3.141592653589793238462};

inline double degrees_to_radians(double degrees) {
    return degrees / 180.0 * pi;
}

#include "ray.h"
#include "vec3.h"