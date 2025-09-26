#include "../../../include/Scene/Objects/Sphere.h"

namespace {
    constexpr const char* TYPE = "Sphere";
}

Sphere::Sphere(const double3& pos, double radius, const Reflectance& reflectivity) : BaseObject(TYPE, pos, reflectivity), _RADIUS(radius) {}
Sphere::Sphere(double radius, const Reflectance& reflectivity) : BaseObject(TYPE, reflectivity), _RADIUS(radius) {}
Sphere::Sphere(const double3& pos, double radius) : BaseObject(TYPE, pos), _RADIUS(radius) {}
Sphere::Sphere(double radius) : BaseObject(TYPE), _RADIUS(radius) {}