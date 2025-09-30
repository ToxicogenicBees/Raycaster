#pragma once

#include "../Types/Point.hpp"

struct Ray {
    double3 origin;
    double3 dir;

    Ray(const double3 origin, const double3 dir): origin(origin), dir(dir.normal()) {}
};