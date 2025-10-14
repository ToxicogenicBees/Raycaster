#include "../../../include/Scene/Objects/Sphere.h"
#include <stdint.h>

namespace {
    constexpr const uint8_t CENTER = 0;
    constexpr const uint8_t RADIUS = 1;
}

Sphere::Sphere(double radius) {
    // Insert origin point for sphere
    _points.push_back(double3(0, 0, 0));

    // Insert radius point for sphere
    _points.push_back(double3(0, 0, radius));
}

Intersection Sphere::findIntersection(const Ray& ray) const {
    // https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html

    double3 L = _points[CENTER] - ray.origin;
    double tc = L.dot(ray.dir);

    double sqr_rad = (_points[RADIUS] - _points[CENTER]).squaredMagnitude();
    double sqr_d = L.squaredMagnitude() - tc * tc;

    if (sqr_d > sqr_rad) return Intersection();

    // Finding the "times" of intersection (sphere has at most 2 intersections with a ray)
    double t1c = std::sqrt(sqr_rad - sqr_d);
    double t1 = tc - t1c;
    double t2 = tc + t1c;

    double t = (t1 > 0) ? t1 : t2;

    // Both intersections are behing the ray, return invalid intersection
    if (t < 0) return Intersection();

    double3 intersection = ray.origin + ray.dir * t;
    return Intersection(this, intersection, (intersection - _points[CENTER]).normal());
}