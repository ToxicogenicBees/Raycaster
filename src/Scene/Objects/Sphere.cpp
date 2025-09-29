#include "../../../include/Scene/Objects/Sphere.h"
#include <iostream>

namespace {
    constexpr const uint16_t CENTER = 0;
    constexpr const uint16_t RADIUS = 1;
}

Sphere::Sphere(double radius) {
    // Insert origin point for sphere
    points.push_back(double3(0, 0, 0));

    // Insert radius point for sphere
    points.push_back(double3(0, 0, radius));
}

Intersection Sphere::findIntersection(const double3& start, const double3& view_dir) const {
    // https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html

    double3 L = points[CENTER] - start;
    double tc = L.dot(view_dir);

    double sqr_rad = (points[RADIUS] - points[CENTER]).squaredMagnitude();
    double sqr_d = L.squaredMagnitude() - tc * tc;

    if (sqr_d > sqr_rad) return Intersection();

    double t1c = std::sqrt(sqr_rad - sqr_d);
    double t1 = tc - t1c;
    double t2 = tc + t1c;

    double t = (t1 > 0) ? t1 : t2;

    // Both intersections are behing the ray, return invalid intersection
    if (t < 0) return Intersection();

    double3 intersection = start + view_dir * t;
    return Intersection(this, intersection, (intersection - points[CENTER]).normal());
}