#include "../../../include/Scene/Objects/Sphere.h"
#include <iostream>
#include <cmath>

namespace {
    constexpr const char* TYPE = "Sphere";
}

Sphere::Sphere(const double3& pos, double radius, const Reflectance& reflectivity) : BaseObject(TYPE, pos, reflectivity), _RADIUS(radius) {}
Sphere::Sphere(double radius, const Reflectance& reflectivity) : BaseObject(TYPE, reflectivity), _RADIUS(radius) {}
Sphere::Sphere(const double3& pos, double radius) : BaseObject(TYPE, pos), _RADIUS(radius) {}
Sphere::Sphere(double radius) : BaseObject(TYPE), _RADIUS(radius) {}

Intersection Sphere::findIntersection(const double3& start, const double3& dir) {
    // https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html

    double3 L = _pos - start;
    double tc = dot(L, dir);

    if (tc < 0)
        return Intersection();

    double sqr_rad = _RADIUS * _RADIUS;
    double sqr_d = dot(L, L) - tc * tc;

    if (sqr_d > sqr_rad)
        return Intersection();

    double t1c = sqrt(sqr_rad - sqr_d);
    double t1 = tc - t1c;
    double t2 = tc + t1c;

    double t = (t1 > 0) ? t1 : t2;
    if (t < 0) 
        return Intersection(); // both behind ray
    double3 intersection = start + dir * t;

    std::cout << "Intersection at (" << intersection.x << ", " << intersection.y << ", " << intersection.z <<")\n";

    return Intersection(this, intersection, (intersection - _pos).normal());
}