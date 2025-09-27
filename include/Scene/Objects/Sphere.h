#pragma once

#include "BaseObject.h"

class Sphere : public BaseObject {
    private:
        const double _RADIUS;

    public:
        Sphere(double radius = 0);

        Intersection findIntersection(const double3& start, const double3& dir) const override;
};