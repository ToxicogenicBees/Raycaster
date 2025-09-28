#pragma once

#include "../../Types/Point.hpp"
#include <stdint.h>
#include <string>
#include <vector>

namespace {
    using double3 = Point<double>;
}

struct Camera {
    double3 look_vec = double3(0, 0, 0);       // Location the camera points at
    double3 position = double3(0, 0, 1);       // Position in units
    double3 up_vec = double3(0, 0, 1);         // Camera's up vector

    double3 rayThroughPixel(uint16_t x, uint16_t y, double fov) const;
};