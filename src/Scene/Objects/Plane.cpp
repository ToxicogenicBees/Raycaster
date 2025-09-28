#include "../../../include/Scene/Objects/Plane.h"
#include <cmath>

namespace {
    constexpr const uint16_t ORIGIN = 0;
    constexpr const uint16_t NORMAL = 1;
}

Plane::Plane(double3 normal, double distance) {
    double3 true_normal = normal.normal();
    points.push_back(true_normal * distance);   // Insert distance "point" for plane
    points.push_back(true_normal);              // Insert normal vector "point" for plane
}

Plane::Plane(double distance) {
    points.push_back(double3(0, 0, distance));  // Insert distance "point" for plane
    points.push_back(double3(0, 0, 1));         // Insert normal vector "point" for plane
}

void Plane::translate(double dx, double dy, double dz) {
    BaseObject::translate(dx, dy, dz);
    points[NORMAL] = points[NORMAL].normal();
}

void Plane::rotate(double rx, double ry, double rz) {
    BaseObject::rotate(rx, ry, rz);
    points[NORMAL] = points[NORMAL].normal();
}

void Plane::scale(double sx, double sy, double sz) {
    BaseObject::scale(sx, sy, sz);
    points[NORMAL] = points[NORMAL].normal();
}

Intersection Plane::findIntersection(const double3& start, const double3& dir) const {
    double n_dot_v = points[NORMAL].dot(dir);

    // If the ray is parallel to the plane (n_dot_v is zero, with some tolerance for f-p error), return invalid intersection
    if (std::fabs(n_dot_v) < 1e-8) return Intersection();

    // Find "time" of intersection
    double t = -points[NORMAL].dot(start - points[ORIGIN]) / n_dot_v;

    // If the intersection is behind the ray, return invalid intersection
    if (t < 0) return Intersection();

    // Return the proper intersection
    double3 intersectionNormal = n_dot_v > 0 ? -points[NORMAL] : points[NORMAL];
    double3 intersection = start + t * dir;

    return Intersection(this, intersection, intersectionNormal);
}