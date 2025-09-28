#pragma once

#include "BaseObject.h"

struct Sphere : BaseObject {
    Sphere(double radius = 0);

    Intersection findIntersection(const double3& start, const double3& dir) const override;
};