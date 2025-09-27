#include "../../../include/Scene/Objects/Sphere.h"
#include <iostream>
#include <cmath>

namespace {
    constexpr const char* TYPE = "Sphere";
    constexpr const uint16_t CENTER = 0;
    constexpr const uint16_t RADIUS = 1;
}

Sphere::Sphere(double radius) : BaseObject(TYPE) {
    // Insert origin point for sphere
    _points.push_back(double3(0, 0, 0));

    // Insert radius point for sphere
    _points.push_back(double3(0, 0, radius));
}

Intersection Sphere::findIntersection(const double3& start, const double3& dir) const {
    // https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html

    double3 L = _points[CENTER] - start;
    double tc = dot(L, dir);

    if (tc < 0)
        return Intersection();

    double sqr_rad = (_points[RADIUS] - _points[CENTER]).squaredMagnitude();
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

    return Intersection(this, intersection, (intersection - _points[CENTER]).normal());
}