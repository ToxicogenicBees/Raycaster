#pragma once

#include "BaseObject.h"

class Sphere : BaseObject {
    private:
        const double _RADIUS;

    public:
        Sphere(const double3& pos, double radius, const Reflectance& reflectivity);
        Sphere(double radius, const Reflectance& reflectivity);
        Sphere(const double3& pos, double radius);
        Sphere(double radius = 0);
};